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
    class VirtualProperty : public Property {
    public:
      using ReadFunc = PROPERTY_TYPE(CLASS_TYPE::*)() const;
      using WriteFunc = void(CLASS_TYPE::*)(PROPERTY_TYPE);

      VirtualProperty(Core::StringView name, WriteFunc writeFunc, ReadFunc readFunc)
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
        Core::IO::write(output, (((CLASS_TYPE*)object)->*m_readFunc)());
        output.popPropertyName();
      }

    private:
      ReadFunc m_readFunc;
      WriteFunc m_writeFunc;
    };

  }
}