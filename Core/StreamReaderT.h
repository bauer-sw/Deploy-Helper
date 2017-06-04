#pragma once

#include "StreamReader.h"

namespace Core {

  namespace IO {

    template<typename TYPE>
    class StreamReaderT : public StreamReader {
    public:
      StreamReaderT() 
        : StreamReader(&m_myStream)
      {
      }

      virtual ~StreamReaderT() {
      }

    private:
      TYPE m_myStream;
    };

  }

}
