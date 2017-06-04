#include "TextFileWriter.h"



TextFileWriter::TextFileWriter(const std::string& filePath)
  : m_stream(filePath.c_str())
{
}


TextFileWriter::~TextFileWriter()
{
  m_stream.close();
}

void TextFileWriter::write(const std::string& v) {
  m_stream << v.c_str();
}

void TextFileWriter::writeln(const std::string& v) {
  m_stream << v.c_str() << std::endl;
}

void TextFileWriter::close() {
  m_stream.close();
}
