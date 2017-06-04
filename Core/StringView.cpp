// ----------------------
//      Jakob Bauer
//       (c) 2016 
//    www.bauer-sw.de
// ----------------------
//    cpp@bauer-sw.de
// ----------------------
#include "StringView.h"

namespace Core {

  StringView::StringView()
    : m_begin(nullptr)
    , m_end(nullptr)
  {
  }

  StringView::StringView(const char* str)
    : m_begin(str)
  {
    for (; *str != '\0'; ++str);
    m_end = str-1;
  }

  StringView::StringView(const char* begin, const char* end)
    : m_begin(begin)
    , m_end(end)
  {
  }

  StringView::StringView(const std::string& src, std::string::size_type offset)
    : StringView::StringView(src.c_str() + offset, &src.back()) {

  }

  StringView::StringView(const std::string& src, std::string::size_type offset, std::string::size_type count)
    : StringView::StringView(src.c_str() + offset, src.c_str() + offset + count) {

  }

  StringView::~StringView() {
  }

  bool StringView::startsWith(const char* v) const {
    if (v[0] == L'\0') {
      v = nullptr;
    }

    if (m_begin == nullptr || v == nullptr) {
      return m_begin == v;
    }

    std::size_t i = 0;
    for (; i < size() && v[i] != L'\0'; ++i) {
      if (m_begin[i] != v[i]) {
        return false;
      }
    }
    return i <= size();
  }

  bool StringView::startsWith(const Core::StringView& v) const {
    if (size() < v.size()) {
      return false;
    }

    return isEqual(m_begin, m_begin + v.size(), v.m_begin, v.m_end);
  }

  bool StringView::startsWith(const char* str, const char* v) {
    for (std::size_t i = 0; str[i] != '\0' && v[i] != '\0'; ++i) {
      if (str[i] != v[i]) {
        return false;
      }
    }
    return true;
  }

  StringView::Vector StringView::splitBy(const char* str, char sep) {
    Vector vector;

    splitBy(str, sep, vector);

    return vector;
  }

  void StringView::splitBy(const char* str, char sep, Vector& vector) {
    const char* begin = str;
    for (; *str != '\0'; ++str) {
      if (*str == sep) {
        vector.emplace_back(Core::StringView(begin, str - 1));
        begin = str + 1;
      }
    }

    if (vector.empty() || vector.back().m_begin != begin) {
      vector.emplace_back(Core::StringView(begin, str - 1));
    }
  }

  bool StringView::isEqual(const char* begin, const char* end) const {
    if (begin == nullptr && m_begin == nullptr) {
      return true;
    }

    std::string::size_type s = size();
    if (s != size_t(end - begin + 1)) {
      return false;
    }

    return isEqual(m_begin, m_end, begin, end);
  }

  bool StringView::isEqual(const char* b0, const char* e0, const char* b1, const char* e1) {
    if (b0 == b1 && e0 == e1) {
      return true;
    }

    if (e0 == nullptr) {
      e0 = std::numeric_limits<char*>::max();
    }

    if (e1 == nullptr) {
      e1 = std::numeric_limits<char*>::max();
    }

    for (; b0 < e0 && b1 < e1 && *b0 != '\0' && *b1 != '\0'; ++b0, ++b1) {
      if (*b0 != *b1) {
        return false;
      }
    }

    return *b0 == *b1;
  }

}