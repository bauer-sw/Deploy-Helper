// ----------------------
//      Jakob Bauer
//       (c) 2016 
//    www.bauer-sw.de
// ----------------------
//    cpp@bauer-sw.de
// ----------------------
#pragma once

#include <memory>

#include "File.h"

namespace Dependency {

  class DEPENDS_API Node {
  public:
    Node(std::size_t index, const File* file);

    Node(Node && other) = default;

    ~Node();

    void addChild(std::shared_ptr<const Node> child) {
      m_childs.push_back(child);
    }

    std::size_t getIndex() const {
      return m_index;
    }

    const File& getFile() const {
      return *m_file;
    }

    const std::vector<std::shared_ptr<const Node>>& getChilds() const {
      return m_childs;
    }

    bool isChildOf(const Node& node) const;

  private:
    std::size_t m_index;
    const File* m_file;

    std::vector<std::shared_ptr<const Node>> m_childs;
  };

}