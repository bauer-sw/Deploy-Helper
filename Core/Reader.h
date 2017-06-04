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

    class CORE_API Reader : public IO {
    public:
      Reader();
      virtual ~Reader();

      virtual void read(bool&) = 0;

      virtual void read(char&) = 0;
      virtual void read(unsigned char&) = 0;

      virtual void read(int&) = 0;
      virtual void read(unsigned int&) = 0;

      virtual void read(float&) = 0;
      virtual void read(double&) = 0;

      virtual void read(char*&) = 0;
      virtual void read(std::string&) = 0;

      virtual std::size_t openArray() = 0;
      virtual void closeArray() = 0;

      virtual void openSequence() = 0;
      virtual void closeSequence() = 0;

      virtual void nextElement() = 0;
    };

    template<typename VALUE_TYPE>
    static void read(Core::IO::Reader& reader, VALUE_TYPE& v) {
      reader.read(v);
    }

    static void read(Core::IO::Reader& reader, std::string& v) {
      reader.read(v);
    }

    template<typename VALUE_TYPE>
    static void read(Core::IO::Reader& reader, std::vector<VALUE_TYPE>& values) {
      values.resize(reader.openArray());

      for (std::size_t i = 0; i < values.size(); ++i) {
        Core::IO::read(reader, values[i]);
        reader.nextElement();
      }
      reader.closeArray();
    }

    template<typename VALUE_TYPE>
    static void read(Core::IO::Reader& reader, std::list<VALUE_TYPE>& values) {
      for (std::size_t i = 0, e = reader.openArray(); i < e; ++i) {
        VALUE_TYPE tmp;
        Core::IO::read(reader, tmp);
        values.push_back(std::move(tmp));
        reader.nextElement();
      }
      reader.closeArray();
    }

    template<typename VALUE_TYPE>
    static void read(Core::IO::Reader& reader, std::set<VALUE_TYPE>& values) {
      for (std::size_t i = 0, e = reader.openArray(); i < e; ++i) {
        VALUE_TYPE tmp;
        Core::IO::read(reader, tmp);
        values.push_back(std::move(tmp));
        reader.nextElement();
      }
      reader.closeArray();
    }

    template<typename VALUE_TYPE>
    static void read(Core::IO::Reader& reader, std::unordered_set<VALUE_TYPE>& values) {
      for (std::size_t i = 0, e = reader.openArray(); i < e; ++i) {
        VALUE_TYPE tmp;
        Core::IO::read(reader, tmp);        
        values.insert(std::move(tmp));
        reader.nextElement();
      }
      reader.closeArray();
    }

    template<typename KEY_TYPE, typename VALUE_TYPE>
    static void read(Core::IO::Reader& reader, std::map<KEY_TYPE, VALUE_TYPE>& values) {
      for (std::size_t i = 0, e = reader.openArray(); i < e; ++i) {
        typename std::map<KEY_TYPE, VALUE_TYPE>::value_type tmp;
        Core::IO::read(reader, tmp);
        values.insert(std::move(tmp));
        reader.nextElement();
      }
      reader.closeArray();
    }

    template<typename KEY_TYPE, typename VALUE_TYPE>
    static void read(Core::IO::Reader& reader, std::unordered_map<KEY_TYPE, VALUE_TYPE>& values) {
      for (std::size_t i = 0, e = reader.openArray(); i < e; ++i) {
        typename std::map<KEY_TYPE, VALUE_TYPE>::value_type tmp;
        Core::IO::read(reader, tmp);
        values.insert(std::move(tmp));
        reader.nextElement();
      }
      reader.closeArray();
    }

    template<typename VALUE_TYPE0, typename VALUE_TYPE1>
    static void read(Core::IO::Reader& reader, std::pair<VALUE_TYPE0, VALUE_TYPE1>& pair) {
      reader.openSequence();
      Core::IO::read(reader, pair.first);
      reader.nextElement();
      Core::IO::read(reader, pair.second);
      reader.closeSequence();
    }

    template<typename... VALUE_TYPES>
    static void read(Core::IO::Reader& reader, std::tuple<VALUE_TYPES...>& values) {
      reader.openSequence();
      TupleReaderWriter::readFrom(&reader, values);
      reader.closeSequence();
    }

  }
}
