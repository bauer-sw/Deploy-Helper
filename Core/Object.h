// ----------------------
//      Jakob Bauer
//       (c) 2016 
//    www.bauer-sw.de
// ----------------------
//    cpp@bauer-sw.de
// ----------------------
#pragma once

#include <unordered_map>
#include <memory>
#include <typeinfo>
#include <typeindex>

#include "Export.h"
#include "StringView.h"
#include "Property.h"
#include "Reader.h"
#include "Writer.h"

namespace Core {

  namespace RTTI {

    // The base Object class of the RTTI system.
    // This class holds all properties of a generic class.
    class CORE_API Object {
    public:
      // Some helpers for better understanding.
      using PropertyMap = std::unordered_map<Core::StringView, std::shared_ptr<Property>>;
      using property_iterator = PropertyMap::iterator;
      using property_const_iterator = PropertyMap::const_iterator;

      using TypeMap = std::unordered_map< std::type_index, Object* >;
      using type_iterator = TypeMap::iterator;
      using type_const_iterator = TypeMap::const_iterator;

      // Construct the object with the typename.
      Object(const Core::StringView& typeName)
        : m_name(typeName)
      {
      }

      // Read object state from a reader implementation.
      void readFrom(void* object, Core::IO::Reader& input);

      // Write object state to a writer implementation.
      void writeTo(void* object, Core::IO::Writer& output) const;

      // Test if any property exists.
      bool hasProperty(const Core::StringView& name) const {
        return m_properties.find(name) != m_properties.end();
      }

      // Get a property.
      std::shared_ptr<Property> getProperty(const Core::StringView& name) const;

      // Test if class BASE is base of the DERIVED class.
      template<typename BASE, typename DERIVED>
      static bool isBaseOf() {
        return std::is_base_of<BASE, DERIVED>();
      }

      bool isBaseOf(const Object& other) const;

      template<typename DERIVED, typename BASE>
      static bool isDerivedFrom() {
        return std::is_base_of<BASE, DERIVED>();
      }

      bool isDerivedFrom(const Object& other) const {
        return other.isBaseOf(*this);
      }

      template<typename TYPE>
      static Object* getClassInfo() {
        auto itr = m_types.find(typeid(TYPE));
        if (itr == m_types.end()) {
          return nullptr;
        }

        return itr->second;
      }

      // Interface methods.
      virtual std::size_t getNumOfParents() const = 0;

      virtual Object* getParent(std::size_t i) const = 0;

    protected:
      Core::StringView m_name;

      PropertyMap m_properties;

      static TypeMap m_types;
    };

  }

}
