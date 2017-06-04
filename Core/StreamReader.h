#pragma once


#include <istream>

#include "Reader.h"
#include "Export.h"

namespace Core {

  namespace IO {

    class CORE_API StreamReader : public Reader
    {
    public:
      StreamReader(std::istream* stream);

      ~StreamReader();

      virtual void read(bool& v) override;

      virtual void read(char& v) override;
      virtual void read(unsigned char& v) override;

      virtual void read(int& v) override;
      virtual void read(unsigned int& v) override;

      virtual void read(float& v) override;
      virtual void read(double& v) override;

      virtual void read(char*& v) override;
      virtual void read(std::string& v) override;

      virtual std::size_t openArray() override;
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
      void readFromStream(TYPE& v) {
        /*if (m_binary) {*/
          m_stream->read((char*)&v, sizeof TYPE);
        //} else {
        //  *m_stream >> v;
        //}
      }

      //bool m_binary;

      std::istream* m_stream;
    };

  }

}


