// ----------------------
//      Jakob Bauer
//       (c) 2016 
//    www.bauer-sw.de
// ----------------------
//    cpp@bauer-sw.de
// ----------------------
#include <stack>

#include "Object.h"

namespace Core {

  namespace RTTI {

    Object::TypeMap Object::m_types;

    void Object::readFrom(void* object, Core::IO::Reader& input) {
      for (std::size_t i = 0, e = getNumOfParents(); i < e; ++i) {
        getParent(i)->readFrom(object, input);
      }

      for (auto& v : m_properties) {
        v.second->readFrom(object, input);
      }
    }

    void Object::writeTo(void* object, Core::IO::Writer& output) const {
      for (std::size_t i = 0, e = getNumOfParents(); i < e; ++i) {
        getParent(i)->writeTo(object, output);
      }

      for (auto& v : m_properties) {
        v.second->writeTo(object, output);
      }
    }

    std::shared_ptr<Property> Object::getProperty(const Core::StringView& name) const {
      auto itr = m_properties.find(name);
      if (itr == m_properties.end()) {
        return nullptr;
      }

      return itr->second;
    }

    bool Object::isBaseOf(const Object& base) const {
      std::stack<const Object*> stack;
      stack.push(&base);

      do {
        const Object* c = stack.top();
        stack.pop();

        if (this == c) {
          return true;
        }

        for (std::size_t i = 0, e = getNumOfParents(); i < e; ++i) {
          stack.push(getParent(i));
        }
      } while (!stack.empty());
      return false;
    }

  }

}