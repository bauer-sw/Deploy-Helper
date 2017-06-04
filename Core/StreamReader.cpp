#include "StreamReader.h"

namespace Core {

  namespace IO {

    StreamReader::StreamReader(std::istream* stream)
      : m_stream(stream)
    {
    }
    
    StreamReader::~StreamReader()
    {
    }

    void StreamReader::read(bool& v) {
      readFromStream(v);
    }

    void StreamReader::read(char& v) {
      readFromStream(v);
    }

    void StreamReader::read(unsigned char& v) {
      readFromStream(v);
    }

    void StreamReader::read(int& v) {
      readFromStream(v);
    }

    void StreamReader::read(unsigned int& v) {
      readFromStream(v);
    }

    void StreamReader::read(float& v) {
      readFromStream(v);
    }

    void StreamReader::read(double& v) {
      readFromStream(v);
    }

    void StreamReader::read(char*& v) {
      std::size_t size = 0;
      readFromStream(size);

      if (size != 0) {
        v = new char[size];
        m_stream->read(v, size);
      } else {
        v = nullptr;
      }
    }

    void StreamReader::read(std::string& v) {
      std::size_t size = 0;
      readFromStream(size);

      if (size != 0) {
        v.resize(size);
        m_stream->read(&v[0], size);
      } else {
        v.clear();
      }
    }

    std::size_t StreamReader::openArray() {
      std::size_t size = 0;
      readFromStream(size);
      return size;
    }

    void StreamReader::closeArray() {
    }

    void StreamReader::openSequence() {
    }

    void StreamReader::closeSequence() {
    }

    void StreamReader::nextElement() {
    }

  }

}