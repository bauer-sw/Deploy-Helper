// ----------------------
//      Jakob Bauer
//       (c) 2016 
//    www.bauer-sw.de
// ----------------------
//    cpp@bauer-sw.de
// ----------------------
#pragma once

#include <functional>
#include <memory>
#include <cstdarg>
#include <array>


#include "Export.h"
#include "StringView.h"
#include "Property.h"

#include "Object.h"

#include "PrimitiveProperty.h"
#include "VirtualProperty.h"
#include "ReferencedProperty.h"

namespace Core { 

  namespace RTTI {

    // Helper class to solve the parent dependency
    template<typename... TYPES>
    class ParentDependencySolver;

    template<>
    class ParentDependencySolver<> {
    public:
      template<std::size_t SIZE>
      static void assign(std::array<Object*, SIZE>& parents, std::size_t i) {
      }
    };

    template<typename FIRST_PARENT_TYPE, typename... OTHER_PARENT_TYPES>
    class ParentDependencySolver< FIRST_PARENT_TYPE, OTHER_PARENT_TYPES...>
     : private ParentDependencySolver<OTHER_PARENT_TYPES...>{
    public:
      template<std::size_t SIZE>
      static void assign(std::array<Object*, SIZE>& parents, std::size_t i) {
        parents[i] = Object::getClassInfo<FIRST_PARENT_TYPE>();
        ParentDependencySolver<OTHER_PARENT_TYPES...>::assign(parents, i + 1);
      }
    };

    // Template class type to register generic class type at the RTTI system.
    template<typename CLASS_TYPE, std::size_t NUM_PARENTS = 0>
    class Class : public Object {
    public:
      // Helper method to create a class without any parents.
      static Class<CLASS_TYPE> create(const Core::StringView& typeName)
      {
        return Class<CLASS_TYPE>(typeName);
      }

      // Helper method to create a class with any parents.
      template<typename... PARENT_TYPES>
      static Class<CLASS_TYPE, sizeof...(PARENT_TYPES)> create(const Core::StringView& typeName)
      {
        Class<CLASS_TYPE, sizeof...(PARENT_TYPES)> c(typeName);
        ParentDependencySolver<PARENT_TYPES...>::assign<sizeof...(PARENT_TYPES)>(c.m_parents, 0);
        return c;
      }

      // Destructor
      ~Class() {
      }

      // Implemented the interface of the abstract Object class.
      virtual std::size_t getNumOfParents() const override {
        return NUM_PARENTS;
      }

      virtual Object* getParent(std::size_t i) const override {
        return m_parents[i];
      }

      // Register a primitive property.
      template<typename PROPERTY_TYPE>
      Class<CLASS_TYPE, NUM_PARENTS>& registerProperty(const Core::StringView& propertyName, typename PrimitiveProperty<CLASS_TYPE, PROPERTY_TYPE>::ReadWriteFunc readWriteFunc) {
        m_properties.insert(std::make_pair(propertyName, new PrimitiveProperty<CLASS_TYPE, PROPERTY_TYPE>(propertyName, readWriteFunc)));
        return *this;
      }

      // Register a virtual property.
      template<typename PROPERTY_TYPE>
      Class<CLASS_TYPE, NUM_PARENTS>& registerProperty(const Core::StringView& propertyName, typename VirtualProperty<CLASS_TYPE, PROPERTY_TYPE>::WriteFunc writeFunc, typename VirtualProperty<CLASS_TYPE, PROPERTY_TYPE>::ReadFunc readFunc) {
        m_properties.insert(std::make_pair(propertyName, new VirtualProperty<CLASS_TYPE, PROPERTY_TYPE>(propertyName, writeFunc, readFunc)));
        return *this;
      }

      // Register a referenced property.
      template<typename PROPERTY_TYPE>
      Class<CLASS_TYPE, NUM_PARENTS>& registerReferencedProperty(const Core::StringView& propertyName, typename ReferencedProperty<CLASS_TYPE, PROPERTY_TYPE>::WriteFunc writeFunc, typename ReferencedProperty<CLASS_TYPE, PROPERTY_TYPE>::ReadFunc readFunc) {
        m_properties.insert(std::make_pair(propertyName, new ReferencedProperty<CLASS_TYPE, PROPERTY_TYPE>(propertyName, writeFunc, readFunc)));
        return *this;
      }

   // protected:
      Class(const Core::StringView& typeName)
        : Object(typeName)
      {
        // add type to global registration
        m_types[typeid(CLASS_TYPE)] = const_cast<Class*>(this);
      }

      // store the parents
      std::array< Object*, NUM_PARENTS > m_parents;
    };

  }

}