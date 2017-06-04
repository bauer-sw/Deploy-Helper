// ----------------------
//      Jakob Bauer
//       (c) 2016
//    www.bauer-sw.de
// ----------------------
//    cpp@bauer-sw.de
// ----------------------

#pragma once

#include <string>
#include <vector>
#include <list>

#include <set>
#include <unordered_set>

#include <map>
#include <unordered_map>

#include "Export.h"
#include "TupleReaderWriter.h"
#include "IO.h"

namespace Core {

  namespace IO {

    class CORE_API Writer : public IO {
    public:
      Writer();
      virtual ~Writer();

      virtual void write(bool) = 0;

      virtual void write(char) = 0;
      virtual void write(unsigned char) = 0;
      
      virtual void write(int) = 0;
      virtual void write(unsigned int) = 0;

      virtual void write(float) = 0;
      virtual void write(double) = 0;

      virtual void write(const char*) = 0;
      virtual void write(const std::string&) = 0;

      virtual void openArray(std::size_t) = 0;      
      virtual void closeArray() = 0; 

      virtual void openSequence() = 0;
      virtual void closeSequence() = 0;

      virtual void nextElement() = 0;
    };

    template<typename VALUE_TYPE>
    static void write(Core::IO::Writer& writer, VALUE_TYPE v) {
      writer.write(v);
    }

    static void write(Core::IO::Writer& writer, const std::string& v) {
      writer.write(v);
    }

    template<typename VALUE_TYPE>
    static void write(Core::IO::Writer& writer, const std::vector<VALUE_TYPE>& values) {
      writer.openArray(values.size());
      for (const VALUE_TYPE& v : values) {
        Core::IO::write(writer, v);
        writer.nextElement();
      }
      writer.closeArray();
    }

    template<typename VALUE_TYPE>
    static void write(Core::IO::Writer& writer, const std::list<VALUE_TYPE>& values) {
      writer.openArray(values.size());
      for (const VALUE_TYPE& v : values) {
        Core::IO::write(writer, v);
        writer.nextElement();
      }
      writer.closeArray();
    }
    
    template<typename VALUE_TYPE>
    static void write(Core::IO::Writer& writer, const std::set<VALUE_TYPE>& values) {
      writer.openArray(values.size());
      for (const VALUE_TYPE& v : values) {
        Core::IO::write(writer, v);
        writer.nextElement();
      }
      writer.closeArray();
    }

    template<typename VALUE_TYPE>
    static void write(Core::IO::Writer& writer, const std::unordered_set<VALUE_TYPE>& values) {
      writer.openArray(values.size());
      for (const VALUE_TYPE& v : values) {
        Core::IO::write(writer, v);
        writer.nextElement();
      }
      writer.closeArray();
    }

    template<typename KEY_TYPE, typename VALUE_TYPE>
    static void write(Core::IO::Writer& writer, const std::map<KEY_TYPE, VALUE_TYPE>& values) {
      writer.openArray(values.size());
      for (const auto& v : values) {
        Core::IO::write(writer, v);
        writer.nextElement();
      }
      writer.closeArray();
    }

    template<typename KEY_TYPE, typename VALUE_TYPE>
    static void write(Core::IO::Writer& writer, const std::unordered_map<KEY_TYPE, VALUE_TYPE>& values) {
      writer.openArray(values.size());
      for (const auto& v : values) {
        Core::IO::write(writer, v);
        writer.nextElement();
      }
      writer.closeArray();
    }

    template<typename VALUE_TYPE0, typename VALUE_TYPE1>
    static void write(Core::IO::Writer& writer, const std::pair<VALUE_TYPE0, VALUE_TYPE1>& pair) {
      writer.openSequence();
      Core::IO::write(writer, pair.first);
      writer.nextElement();
      Core::IO::write(writer, pair.second);
      writer.closeSequence();
    }

    template<typename... VALUE_TYPES>
    static void write(Core::IO::Writer& writer, const std::tuple<VALUE_TYPES...>& values) {
      writer.openSequence();
      TupleReaderWriter::writeTo(&writer, values);
      writer.closeSequence();
    }

  }
}
