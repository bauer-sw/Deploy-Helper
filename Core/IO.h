#pragma once

#include <stack>

#include "Export.h"
#include "StringView.h"

namespace Core {

  namespace IO {

    class CORE_API IO {
    public:
      IO() {}

      virtual ~IO() {}

      void pushPropertyName(const Core::StringView& n) { m_propertyNameStack.push(n); }

      void popPropertyName() { m_propertyNameStack.pop(); }

      bool isPropertyNameAvailable() const { return !m_propertyNameStack.empty(); }

      const Core::StringView& getCurrentPropertyName() const { return m_propertyNameStack.top(); }

    private:
      std::stack<Core::StringView> m_propertyNameStack;
    };

  }

}