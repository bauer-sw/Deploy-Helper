// ----------------------
//      Jakob Bauer
//       (c) 2016 
//    www.bauer-sw.de
// ----------------------
//    cpp@bauer-sw.de
// ----------------------
#pragma once

#ifndef __WSTRINGVIEW
#define __WSTRINGVIEW

#include <string>
#include <vector>
#include <cstdlib>

#include "Export.h"
#include "Hash.h"

namespace Core {

  /// <summary>View on a specific memory range.</summary>
  class CORE_API StringView {
  public:
    // helper
    using Vector = std::vector<StringView>;
    using size_type = std::string::size_type;

    /// <summary>Constructs a string view on an empty value.</summary>
    StringView();

    /// <summary>Constructs a string view on the selected memory c-string style value.</summary>
    /// <param name="str">Start address of the c-style string.</param>
    StringView(const char* str);

    /// <summary>Constructs a string view on the selected memory range.</summary>
    /// <param name="begin">Start address of the string value.</param>
    /// <param name="end">End address of the string value (points to the last character).</param>
    StringView(const char* begin, const char* end);

    /// <summary>Constructs a string view on the source string.</summary>
    /// <param name="src">Source string value.</param>
    /// <param name="offset">Data offset inside the string value.</param>
    explicit StringView(const std::string& src, std::string::size_type offset = 0);

    /// <summary>Constructs a string view on the source string.</summary>
    /// <param name="src">Source string value.</param>
    /// <param name="offset">Data offset inside the string value.</param>
    /// <param name="count">Number of characters (end address = offset + count).</param>
    StringView(const std::string& src, std::string::size_type offset, std::string::size_type count);
       
    /// <summary>Destructor.</summary>
    ~StringView();

    /// <summary>Start address of the view.</summary>
    /// <remarks>If value is null, no valid pointer is stored -> nullptr.</remarks>
    const char* begin() const {
      return m_begin;
    }

    /// <summary>End address of the view.</summary>
    /// <remarks>If value is null, no valid pointer is stored -> nullptr.</remarks>
    const char* end() const {
      return m_end;
    }

    /// <summary>Test if the string view starts with a specific c-style string value.</summary>
    /// <param name="v">Value to test.</param>
    /// <returns>TRUE: Value from v compares with the start of the string view value. FALSE: Otherwise.</returns>
    bool startsWith(const char* v) const;

    /// <summary>Test if the string view starts with a specific string view value.</summary>
    /// <param name="v">Value to test.</param>
    /// <returns>TRUE: Value from v compares with the start of the string view value. FALSE: Otherwise.</returns>
    bool startsWith(const Core::StringView& v) const;

    /// <summary>Test if the c-style string value starts with a specific c-style string value.</summary>
    /// <param name="str">Value to test.</param>
    /// <param name="v">Value to compare.</param>
    /// <returns>TRUE: Value from v compares with the start of the str value. FALSE: Otherwise.</returns>
    static bool startsWith(const char* str, const char* v);

    /// <summary>Split a c-style string value in separate values by the specific separator.</summary>
    /// <param name="str">String value.</param>
    /// <param name="sep">Separator for splitting.</param>
    /// <returns>Split values as each vector element.</returns>
    static Vector splitBy(const char* str, char sep);

    /// <summary>Split a c-style string value in separate values by the specific separator and append it to a existing vector.</summary>
    /// <param name="str">String value.</param>
    /// <param name="sep">Separator for splitting.</param>
    /// <param name="out">[OUT] Append split values as each vector element.</returns>
    static void splitBy(const char* str, char sep, Vector& out);

    /// <summary>Size of the string view.</summary>
    /// <returns>Size.</returns>
    size_type size() const {
      return m_end - m_begin + 1;
    }

    /// <summary>Find character in the string view.</summary>
    /// <param name="c">Character to find.</param>
    /// <param name="off">Offset for search.</param>
    /// <returns>Index of the character, if not found returns npos.</returns>
    size_type find(char c, size_type off) const {
      if (isEmptyOrNull() || off >= size()) {
        return std::string::npos;
      }

      for (const char* b = (m_begin+off); b <= m_end; ++b) {
        if (*b == c) {
          return b - m_begin;
        }
      }
      return std::string::npos;
    }

    /// <summary>Find last character in the string view.</summary>
    /// <param name="c">Character to find.</param>
    /// <returns>Index of the character, if not found returns npos.</returns>
    size_type findLastOf(char c) const {
      if (isEmptyOrNull()) {
        return std::string::npos;
      }

      for (const char* b = m_end; b >= m_begin; --b) {
        if (*b == c) {
          return b - m_begin;
        }
      }
      return std::string::npos;
    }

    /// <summary>Test if string view content is equal to another character range.</summary>
    /// <remarks>Assumption: begin is lower than end and both are valid pointers</remarks>
    /// <param name="begin">Start of the range.</param>
    /// <param name="end">End of the range.</param>
    /// <returns>TRUE: Content is equal, FALSE: otherwise.</returns>
    bool isEqual(const char* begin, const char* end) const;

    /// <summary>Test if string view content is equal to another character range.</summary>
    /// <remarks>Assumption: begin is lower than end and both are valid pointers</remarks>
    /// <param name="begin">Start of the range.</param>
    /// <param name="end">End of the range.</param>
    /// <returns>TRUE: Content is equal, FALSE: otherwise.</returns>
    static bool isEqual(const char* b0, const char* e0, const char* b1, const char* e1 = nullptr);

    bool operator==(const Core::StringView& other) const {
      return isEqual(other.m_begin, other.m_end);
    }

    bool operator==(const std::string& other) const {
      return isEqual(other.c_str(), &other.back());
    }

    bool operator==(const char* other) const {
      return isEqual(m_begin, m_end, other);
    }

    bool operator!=(const Core::StringView& other) const {
      return !isEqual(other.m_begin, other.m_end);
    }

    bool operator!=(const std::string& other) const {
      return !isEqual(other.c_str(), &other.back());
    }

    bool operator!=(const char* other) const {
      return !isEqual(m_begin, m_end, other);
    }

    bool isNull() const {
      return m_begin == nullptr;
    }

#if 0
    bool isEmpty() const {
      return m_begin != nullptr && m_size == 0;
    }
#endif

    bool isEmptyOrNull() const {
      return m_begin == nullptr;
    }

    template<typename T>
    T as(T defaultValue = T()) const {
      if (isEmptyOrNull()) {
        return defaultValue;
      }

      return convertToPrivate(m_begin, T());
    }

  private:
    template<typename T>
    static T convertToPrivate(const char* src, T defaultValue) {
      throw std::runtime_error();
      return defaultValue;
    }

    template<>
    static float convertToPrivate(const char* src, float defaultValue) {
      return std::strtof(src, nullptr);
    }

    template<>
    static double convertToPrivate(const char* src, double defaultValue) {
      return std::strtod(src, nullptr);
    }

    template<>
    static int convertToPrivate(const char* src, int defaultValue) {
      return std::strtol(src, nullptr, 10);
    }

    template<>
    static unsigned int convertToPrivate(const char* src, unsigned int defaultValue) {
      return std::strtoul(src, nullptr, 10);
    }

  private:
    /// <summary>Start of the string view.</summary>
    const char* m_begin;

    /// <summary>End of the string view (last character are inclusive).</summary>
    const char* m_end;
  };

}

namespace std {

  template<>
  class hash<Core::StringView> {
  public:
    size_t operator()(const Core::StringView& val) const {
      if (val.isEmptyOrNull()) {
        return 0;
      }

      std::size_t seed = 0;
      for (auto begin = val.begin(), end = val.end(); begin <= end; ++begin) {
        Core::hash_combine(seed, *begin);
      }
      return seed;
    }
  };

}

#endif