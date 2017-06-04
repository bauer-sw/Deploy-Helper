// ----------------------
//      Jakob Bauer
//       (c) 2016 
//    www.bauer-sw.de
// ----------------------
//    cpp@bauer-sw.de
// ----------------------
#include "Arguments.h"

namespace Core {

  Arguments::Arguments(int argc, char* argv[], const Core::StringView& separator)
    : m_arguments(argc)
    , m_separator(separator)
  {
    for (int i = 0; i < argc; ++i) {
      m_arguments[i] = argv[i];
    }
  }

  Arguments::~Arguments() {
  }

  bool Arguments::hasSwitch(const char* name) const {
    for (const auto& v : m_arguments) {
      if (v.startsWith(m_separator)) {
        if (StringView::isEqual(v.begin() + m_separator.size(), v.end(), name)) {
          return true;
        }
      }
    }
    return false;
  }

}