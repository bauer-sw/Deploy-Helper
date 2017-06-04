#pragma once

#include <fstream>

class TextFileWriter {
public:
  TextFileWriter(const std::string& filePath);
  ~TextFileWriter();

  bool isOpen() const {
    return m_stream.is_open();
  }

  void write(const std::string& v);

  void writeln(const std::string& v);

  void close();

private:
  std::ofstream m_stream;
};

