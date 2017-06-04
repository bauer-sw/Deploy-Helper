// ----------------------
//      Jakob Bauer
//       (c) 2016 
//    www.bauer-sw.de
// ----------------------
//    cpp@bauer-sw.de
// ----------------------

#include "Graph.h"

#include <stack>
#include <iostream>

namespace Dependency {

  Graph::Graph()
    : m_numberOfInitialFiles(0)
  {
  }


  Graph::~Graph() {
  }

  Graph Graph::process(const Context& context) {
    if (context.m_initialFiles.empty()) {
      return {};
    }

    // create graph
    Graph graph;

    // add root files to graph
    std::stack<std::string> files;
    for (const auto& v : context.m_initialFiles) {
      std::size_t lastSep = v.findLastOf('\\');
      if (lastSep == std::string::npos) {
        lastSep = v.findLastOf('/');
      }
      if (lastSep == std::string::npos) {
        files.push(std::string(v.begin(), v.size()));
      } else {
        ++lastSep;
        files.push(std::string(v.begin() + lastSep, v.size() - lastSep));
      }      
    }
    graph.m_numberOfInitialFiles = context.m_initialFiles.size();    


    // find dependencies of each file
    do {
      // return head element from the stack
      std::string cur = files.top();

      // pop head element
      files.pop();

      // small performance issue
      auto endItr = graph.m_moduleNameToIndex.end();

      // test if module isn't contains in the current graph
      if (graph.isModuleContains(cur)) {
        continue;
      }

      // looking for the module file path
      std::string modulePath = context.findFile(cur);
      // test if module is excluded by name or file path
      if (context.excludeModule(cur, modulePath)) {
        continue;
      }

      // yeah all tests are passed
      //  1. module doesn't exists in the graph
      //  2. module found on the hard disk
      //  3. module isn't excluded
      //    -> add it to the graph
      graph.m_moduleNameToIndex.insert(std::make_pair(cur, graph.m_files.size()));

      // update performance tweak
      endItr = graph.m_moduleNameToIndex.end();

      // process the file and add it to the graph
      graph.m_files.push_back(File::process(std::move(cur), std::move(modulePath), context));        

      // resolve all dependencies of the current processed file
      const auto& depends = graph.m_files.back().getDependencies();
      for (const auto& f : depends) {
        // add file to queue
        files.push(f);
      }
    } while (!files.empty());

    // return the graph
    return graph;
  }

  std::vector<std::shared_ptr<const Node>> Graph::buildDirectedGraph() const {
    // test if are files exists
    if (m_files.empty()) {
      // nothing to do
      return {};
    }

    // create a temporary vector to handle all nodes/modules
    std::vector<std::shared_ptr<Node>> nodes(m_files.size());

    // create the return value with all available parent nodes
    std::vector<std::shared_ptr<const Node>> parentNodes(m_numberOfInitialFiles);

#if _DEBUG
    auto moduleNameEndItr = m_moduleNameToIndex.end();
#endif

    // process all files
    for (std::size_t i = 0; i < m_files.size(); ++i) {
      // get current file
      const auto& v = m_files[i];

      // looking for node representation
      auto& parentNode = nodes[i];
      if (!parentNode) {
        // node representation doesn't exists, create a new one
        parentNode = std::shared_ptr<Node>(new Node(i, &v));
      }

      // test if current node a initial file
      if (i < m_numberOfInitialFiles) {
        parentNodes[i] = parentNode;
      }

      // solve all dependencies
      for (const auto& d : v.getDependencies()) {
        // looking for the index by module name
        auto itr = m_moduleNameToIndex.find(d);

#if _DEBUG
        if (itr == moduleNameEndItr) {
          std::cerr << "Graph::buildDirectedGraph: Invalid application state!" << std::endl;
          continue;
        }
#endif
        // test if a node exists
        auto& node = nodes[itr->second];
        if (!node) {
          node = std::shared_ptr<Node>(new Node(itr->second, &m_files[itr->second]));
        }

        // add new solved dependency
        node->addChild(node);
      }
    }

    {
      // remove dependencies inside the parent nodes
      // count the removed items for faster processing after this
      std::size_t removedItems = 0;
      // 2D loop to remove depending files
      for (std::size_t i = 0; i < parentNodes.size(); ++i) {
        // test if pointer is valid
        if (parentNodes[i].get() == nullptr) {
          continue;
        }

        // child loop for testing
        for (std::size_t j = 0; j < parentNodes.size(); ++j) {
          // ignore same entry or invalid pointer
          if (i == j || parentNodes[j].get() == nullptr) {
            continue;
          }

          // test if element i is child of element j
          if (parentNodes[i]->isChildOf(*parentNodes[j])) {
            parentNodes[i] = nullptr;
            ++removedItems;

            // test if element j is child of element i
          } else if (parentNodes[j]->isChildOf(*parentNodes[i])) {
            parentNodes[j] = nullptr;
            ++removedItems;
          }

          // test failed -> no dependency between element i and element j
        }
      }

      // removed empty entries
      std::vector<std::shared_ptr<const Node>> parentNodesNew;
      parentNodesNew.reserve(parentNodes.size() - removedItems);
      for (std::size_t i = 0; i < parentNodes.size(); ++i) {
        if (parentNodes[i] != nullptr) {
          parentNodesNew.push_back(std::move(parentNodes[i]));
        }
      }
      parentNodesNew.swap(parentNodes);
    }

    return parentNodes;
  }

}