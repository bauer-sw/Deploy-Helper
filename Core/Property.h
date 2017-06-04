// ----------------------
//      Jakob Bauer
//       (c) 2016
//    www.bauer-sw.de
// ----------------------
//    cpp@bauer-sw.de
// ----------------------

#pragma once

#include "StringView.h"
#include "Reader.h"
#include "Writer.h"

namespace Core {

  namespace RTTI {

    class Property {
    public:
      Property(Core::StringView name)
        : m_name(name)
      {
      }

      virtual void readFrom(void* object, Core::IO::Reader& input) = 0;

      virtual void writeTo(void* object, Core::IO::Writer& output) const = 0;

      const Core::StringView& getName() const { return m_name; }

    private:
      Core::StringView m_name;
    };

  }

}