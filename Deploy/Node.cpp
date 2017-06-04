// ----------------------
//      Jakob Bauer
//       (c) 2016 
//    www.bauer-sw.de
// ----------------------
//    cpp@bauer-sw.de
// ----------------------

#include <stack>

#include "Node.h"

namespace Dependency {

  Node::Node(std::size_t index, const File* file)
    : m_index(index)
    , m_file(file)
    , m_childs()
  {
  }


  Node::~Node() {
  }

  bool Node::isChildOf(const Node& parent) const {
    std::stack<const Node*> parents;
    parents.push(&parent);

    do {
      const Node* n = parents.top();

      for (const auto& v : n->getChilds()) {
        if (this == v.get()) {
          return true;
        }

        parents.push(v.get());
      }
    } while (!parents.empty());

    return false;
  }
}