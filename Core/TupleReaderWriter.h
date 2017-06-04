#pragma once

namespace Core {

  namespace IO {

    class Reader;
    class Writer;

    template<class... TAIL>
    class TupleReaderWriter;

    template<>
    class TupleReaderWriter<> {
    public:
      template<typename... T>
      static void writeTo(Writer* writer, const std::tuple<T...>& values) {
      }

      template<typename... T>
      static void readFrom(Reader* reader, std::tuple<T...>& values) {
      }
    };

    template<class HEAD, class... TAIL>
    class TupleReaderWriter<HEAD, TAIL...>
      : private TupleReaderWriter<TAIL...>
    {
    public:
      template<typename... T>
      static void writeTo(Writer* writer, const std::tuple<T...>& values) {
        TupleReaderWriter<TAIL...>::writeTo(writer, value);

        writer->nextElement();
        Core::IO::write(*writer, std::get<sizeof...(TAIL)>(value));        
      }

      template<typename... T>
      static void readFrom(Reader* reader, std::tuple<T...>& values) {
        TupleReaderWriter<TAIL...>::readFrom(reader, value);

        reader->nextElement();
        Core::IO::read(*reader, std::get<sizeof...(TAIL)>(value));
      }
    };

  }
}


