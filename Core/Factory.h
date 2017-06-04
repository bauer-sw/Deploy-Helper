// ----------------------
//      Jakob Bauer
//       (c) 2016 
//    www.bauer-sw.de
// ----------------------
//    cpp@bauer-sw.de
// ----------------------
#pragma once

#include <unordered_map>
#include <functional>
#include <cassert>

namespace Core {

  template<typename BASE, typename KEY = std::string>
  class Factory {
  public:
    using CreatorFunc = std::function<BASE*(void)>;

    using Map = std::unordered_map< KEY, CreatorFunc >;
    using iterator = typename Map::iterator;
    using const_iterator = typename Map::const_iterator;

    iterator begin() {
      return m_creators.begin();
    }

    iterator end() {
      return m_creators.end();
    }

    const_iterator begin() const {
      return m_creators.begin();
    }

    const_iterator end() const {
      return m_creators.end();
    }

    const_iterator cbegin() const {
      return m_creators.begin();
    }

    const_iterator cend() const {
      return m_creators.end();
    }

    template<typename TYPE>
    void registerType(const KEY& key) {
      registerType(key, []() { return new TYPE(); })
    }

    void registerType(const KEY& key, const CreatorFunc& func) {
      assert(!hasKey(key));
      m_creators[key] = func;
    }

    bool hasType(const KEY& key) const {
      return m_creators.find(key) != m_creators.end();
    }

    BASE* createInstance(const KEY& key) const {
      auto itr = m_creators.find(key);
      if (itr == m_creators.end()) {
        return nullptr;
      }
      return itr->second();
    }

  private:
    Map m_creators;
  };

}