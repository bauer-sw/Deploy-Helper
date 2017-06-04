#include "StreamWriter.h"

namespace Core {

  namespace IO {

    StreamWriter::StreamWriter(std::ostream* stream)
      : m_stream(stream)
    {
    }
    
    StreamWriter::~StreamWriter()
    {
    }

    void StreamWriter::write(bool v) {
      writeToStream(v);
    }

    void StreamWriter::write(char v) {
      writeToStream(v);
    }

    void StreamWriter::write(unsigned char v) {
      writeToStream(v);
    }

    void StreamWriter::write(int v) {
      writeToStream(v);
    }

    void StreamWriter::write(unsigned int v) {
      writeToStream(v);
    }

    void StreamWriter::write(float v) {
      writeToStream(v);
    }

    void StreamWriter::write(double v) {
      writeToStream(v);
    }

    void StreamWriter::write(const char* v) {
      if (v == nullptr) {
        writeToStream((std::size_t)0);
        return;
      }

      std::size_t size = strlen(v);
      writeToStream(size);

      if (size != 0) {
        m_stream->write(v, size);
      }
    }

    void StreamWriter::write(const std::string& v) {
      std::string::size_type s = v.size();
      writeToStream(s);

      if (s != 0) {
        m_stream->write(&v[0], s);
      }
    }

    void StreamWriter::openArray(std::size_t size) {
      writeToStream(size);
    }

    void StreamWriter::closeArray() {
    }

    void StreamWriter::openSequence() {
    }

    void StreamWriter::closeSequence() {
    }

    void StreamWriter::nextElement() {
    }

  }

}