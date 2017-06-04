#pragma once

#include "StreamWriter.h"

namespace Core {

  namespace IO {

    template<typename TYPE>
    class StreamWriterT : public StreamWriter {
    public:
      StreamWriterT()
        : StreamWriter(&m_myStream)
      {
      }

      virtual ~StreamWriterT() {
      }

    private:
      TYPE m_myStream;
    };

  }

}
