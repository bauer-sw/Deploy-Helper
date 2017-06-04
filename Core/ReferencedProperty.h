// ----------------------
//      Jakob Bauer
//       (c) 2016
//    www.bauer-sw.de
// ----------------------
//    cpp@bauer-sw.de
// ----------------------

#pragma once

#include "Property.h"

namespace Core {

  namespace RTTI {

    template<typename CLASS_TYPE, typename PROPERTY_TYPE>
    class ReferencedProperty : public Property {
    public:
      // function pointer
      // do not use std::function -> return value will be copy!
      using ReadFunc = const PROPERTY_TYPE&(CLASS_TYPE::*)() const;
      using WriteFunc = void(CLASS_TYPE::*)(const PROPERTY_TYPE&);

      ReferencedProperty(Core::StringView name, WriteFunc writeFunc, ReadFunc readFunc)
        : Property(name)
        , m_readFunc(readFunc)
        , m_writeFunc(writeFunc)
      {
      }

      virtual void readFrom(void* object, Core::IO::Reader& input) override {
        input.pushPropertyName(getName());
        PROPERTY_TYPE tmp;        
        Core::IO::read(input, tmp);        
        (((CLASS_TYPE*)object)->*m_writeFunc)(tmp);
        input.popPropertyName();
      }

      virtual void writeTo(void* object, Core::IO::Writer& output) const override {   
        output.pushPropertyName(getName());
        const PROPERTY_TYPE& tmp = (((CLASS_TYPE*)object)->*m_readFunc)();
        Core::IO::write(output, tmp);
        output.popPropertyName();
      }

    private:
      ReadFunc m_readFunc;
      WriteFunc m_writeFunc;
    };

  }
}