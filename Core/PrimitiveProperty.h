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
    class PrimitiveProperty : public Property {
    public:
      using ReadWriteFunc = PROPERTY_TYPE CLASS_TYPE::*;

      PrimitiveProperty(Core::StringView name, ReadWriteFunc readWriteFunc)
        : Property(name)
        , m_readWriteFunc(readWriteFunc)
      {
      }

      virtual void readFrom(void* object, Core::IO::Reader& input) override {
        input.pushPropertyName(getName());
        Core::IO::read(input, ((CLASS_TYPE*)object)->*m_readWriteFunc);
        input.popPropertyName();
      }

      virtual void writeTo(void* object, Core::IO::Writer& output) const override {   
        output.pushPropertyName(getName());
        Core::IO::write(output, ((CLASS_TYPE*)object)->*m_readWriteFunc);
        output.popPropertyName();
      }

    private:
      ReadWriteFunc m_readWriteFunc;
    };

  }
}
