// ----------------------
//      Jakob Bauer
//       (c) 2016 
//    www.bauer-sw.de
// ----------------------
//    cpp@bauer-sw.de
// ----------------------
#pragma once

#include <unordered_map>

#include "Core/StringView.h"

#include "Node.h"
#include "Context.h"

namespace Dependency {

  /// <summary>Dependency graph of the selected context.</summary>
  class DEPENDS_API Graph {
  public:
    Graph(Graph&& other) = default;

    ~Graph();

    /// <summary>Creates an dependency graph based on the given context.</summary>
    /// <param name="context">Context.</summary>
    /// <returns>Dependency Graph.</returns>
    static Graph process(const Context& context);

    /// <summary>Build an directed graph based on the dependency graph.</summary>
    /// <returns>The root nodes.</returns>
    std::vector<std::shared_ptr<const Node>> buildDirectedGraph() const;

    std::size_t getIndexForModule(const std::string& str) const {
      auto itr = m_moduleNameToIndex.find(str);
      if (itr == m_moduleNameToIndex.end()) {
        return (std::size_t) - 1;
      }
      return itr->second;
    }

    bool isModuleContains(const std::string& str) const {
      return getIndexForModule(str) < m_files.size();
    }

    const File& getDepedencyFileByIndex(std::size_t index) const {
      return m_files[index];
    }

    std::size_t getNumOfDependecyFiles() const {
      return m_files.size();
    }

    File::State getModuleState(const std::string& str) const {
      auto index = getIndexForModule(str);
      if (index >= m_files.size()) {
        return File::State::NotHandled;
      }
      return m_files[index].getState();
    }

    std::string getFilePath(const std::string& str) const {
      auto index = getIndexForModule(str);
      if (index >= m_files.size()) {
        return std::string();
      }
      return m_files[index].getFilePath();
    }

    const std::vector<std::string>& getDependencies(const std::string& str) const {
      auto index = getIndexForModule(str);
      if (index >= m_files.size()) {
        static std::vector<std::string> tmp;
        return tmp;
      }
      return m_files[index].getDependencies();
    }


  private:
    Graph();

    std::vector<File> m_files;
    std::size_t m_numberOfInitialFiles;

    std::unordered_map<std::string, std::size_t> m_moduleNameToIndex;
  };

}