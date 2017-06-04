// ----------------------
//      Jakob Bauer
//       (c) 2016 
//    www.bauer-sw.de
// ----------------------
//    cpp@bauer-sw.de
// ----------------------
#pragma once

#include <unordered_map>
#include <chaiscript/chaiscript.hpp>

#include "Core/StringView.h"

namespace Dependency {

  class DEPENDS_API Context {
  public:
    enum class DirectoryExpandBehavior {
      OnlyAddDirectory,
      AddAllSubDirectories,
      AddAllSubDirectoriesRecursivly
    };

    Context();
    ~Context();

    const std::string& findFile(const std::string& file) const;

    const std::string& findFile(const Core::StringView& file) const {
      return findFile(std::string(file.begin(), file.size()));
    }

    bool ignoreModule(const std::string& moduleName, const std::string& modulePath) const;

    bool excludeModule(const std::string& moduleName, const std::string& modulePath) const;

    bool addSearchPathsFromEnvironment(const char* name);

    void addSearchPath(const char* path, DirectoryExpandBehavior behavior = DirectoryExpandBehavior::OnlyAddDirectory);

    Core::StringView createView(const char* path);

    Core::StringView createView(const char* path, std::size_t start, std::size_t end);

    Core::StringView::Vector m_searchPaths;

    Core::StringView::Vector m_initialFiles;

    std::vector<std::string> m_moduleNamesToIgnore;
    std::vector<std::string> m_modulePathsToIgnore;

    std::vector<std::string> m_moduleNamesToExclude;
    std::vector<std::string> m_modulePathsToExclude;

    static void registerTo(chaiscript::ChaiScript& chai, Context& context, chaiscript::ModulePtr m);

  private:
    std::vector<char> m_memoryBlock;

    mutable std::unordered_map<std::string, std::string> m_findFileCache;
  };

}