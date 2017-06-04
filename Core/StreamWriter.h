#pragma once

#include <ostream>

#include "Writer.h"
#include "Export.h"

namespace Core {

  namespace IO {

    class CORE_API StreamWriter : public Writer
    {
    public:
      StreamWriter(std::ostream* stream);

      ~StreamWriter();

      virtual void write(bool v) override;

      virtual void write(char v) override;
      virtual void write(unsigned char v) override;

      virtual void write(int v) override;
      virtual void write(unsigned int v) override;

      virtual void write(float v) override;
      virtual void write(double v) override;

      virtual void write(const char* v) override;
      virtual void write(const std::string& v) override;

      virtual void openArray(std::size_t) override;
      virtual void closeArray() override;

      virtual void openSequence() override;
      virtual void closeSequence() override;

      virtual void nextElement() override;

      //void setTextMode(bool b) {
      //  setBinaryMode(!b);
      //}

      //bool isTextMode() const {
      //  return !isBinaryMode();
      //}

      //void setBinaryMode(bool b) {
      //  m_binary = b;
      //}

      //bool isBinaryMode() const {
      //  return m_binary;
      //}

    private:
      template<typename TYPE>
      void writeToStream(const TYPE& v) {
        //if (m_binary) {
          m_stream->write((const char*)&v, sizeof TYPE);
        //} else {
        //  *m_stream << v;
        //}
      }

      bool m_binary;

      std::ostream* m_stream;
    };

  }

}


