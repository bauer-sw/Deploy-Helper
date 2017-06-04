// ----------------------
//      Jakob Bauer
//       (c) 2016 
//    www.bauer-sw.de
// ----------------------
//    cpp@bauer-sw.de
// ----------------------
#include "Context.h"

#include <regex>
#include <iostream>
#include <windows.h>
#include <stack>

#include "ChaiMacros.h"
#include "chaiscript/chaiscript_stdlib.hpp"

namespace Dependency {

  Context::Context() {
    m_findFileCache.insert(std::make_pair(std::string(), std::string()));
    m_memoryBlock.reserve(1024);
  }

  Context::~Context() {
  }

  bool Context::addSearchPathsFromEnvironment(const char* name) {
    char* path = nullptr;
    std::size_t pathSize = 0;
    _dupenv_s(&path, &pathSize, name);
    if (!path || pathSize == 0) {
      return false;
    }

    Core::StringView::splitBy(path, ';', m_searchPaths);
    return true;
  }

  const std::string& Context::findFile(const std::string& file) const {
    // test if file already exists in cache
    auto itr = m_findFileCache.find(file);
    if (itr != m_findFileCache.end()) {
      return itr->second;
    }

    // test current file
    struct _stat64i32 buffer;
    if (_stat(file.c_str(), &buffer) == 0) {
      return m_findFileCache.insert(std::make_pair(file, file)).first->second;
    }

    // if path a absolute path, nothing to test
    // X:
    if (file.size() > 2 && file[1] == ':' && (file[2] == '/' || file[2] == '\\')) {
      return m_findFileCache.insert(std::make_pair(file, std::string())).first->second;
    }

    // allocate memory on the stack (performance)
    char tmpPath[_MAX_PATH];

    // use all search paths
    for (Core::StringView::Vector::size_type i = 0; i < m_searchPaths.size(); ++i) {
      const Core::StringView& view = m_searchPaths[i];

      // test against maximum allowed path
      if (view.size() + file.size() + 2 >= _MAX_PATH) {
        std::cerr << "File path " << std::string(view.begin()) << "\\" << file << " is too long for searching.";
        continue;
      }

      // copy search path as first part to temp memory (stack)
      std::memcpy(&tmpPath[0], view.begin(), sizeof(char) * view.size());

      // add path separator
      tmpPath[view.size()] = '\\';

      // copy file to find as second path to temp memory
      std::memcpy(&tmpPath[view.size() + 1], file.c_str(), sizeof(char) * file.size());

      // set null string terminator
      tmpPath[view.size() + file.size() + 1] = '\0';

      // test path
      if (_stat(&tmpPath[0], &buffer) == 0) {
        // insert to cache and return the entry
        return m_findFileCache.insert(std::make_pair(file, &tmpPath[0])).first->second;
      }
    }

    // insert dummy to cache and return it
    return m_findFileCache.insert(std::make_pair(file, std::string())).first->second;
  }

  void Context::addSearchPath(const char* path, DirectoryExpandBehavior behavior) {
    // add search path to all
    m_searchPaths.push_back(createView(path));

    // insert path
    std::stack<Core::StringView> paths;
    paths.push(m_searchPaths.back());

    // allocate memory on the stack (performance)
    char tmpPath[_MAX_PATH];
    WIN32_FIND_DATAA ffd;

    do {
      {
        const Core::StringView& c = paths.top();
        if ((c.size()+1) >= _MAX_PATH) {
          // TODO: write error
          paths.pop();
          continue;
        }

        // copy to own temporary memory to use the Win API
        std::memcpy(&tmpPath[0], c.begin(), c.size());
        if (tmpPath[c.size() - 1] != '\\') {
          if (c.size() + 2 >= _MAX_PATH) {
            // TODO: write error
            paths.pop();
            continue;
          }
          // add separator and search pattern
          tmpPath[c.size()] = '\\';
          tmpPath[c.size() + 1] = '*';
          tmpPath[c.size() + 2] = '\0';
        } else {
          // add search pattern
          tmpPath[c.size()] = '*';
          tmpPath[c.size() + 1] = '\0';
        }        
        paths.pop();
      }

      // get the first file of the selected path
      HANDLE h = FindFirstFileA(&tmpPath[0], &ffd);
      if (INVALID_HANDLE_VALUE == h) {
        // write error case
        continue;
      }

      // iterate over all entries
      do {
        if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY
          && strcmp(ffd.cFileName, "..") != 0 
          && strcmp(ffd.cFileName, ".")) {
          m_searchPaths.push_back(createView(ffd.cFileName));

          if (behavior == DirectoryExpandBehavior::AddAllSubDirectoriesRecursivly) {
            paths.push(m_searchPaths.back());
          }
        }
      } while (FindNextFileA(h, &ffd) != 0);
      
      // close the find handler
      FindClose(h);     
    } while (!paths.empty());    
  }

  Core::StringView Context::createView(const char* path) {
    // copy the path to own memory block and create a string view
    std::size_t length = strlen(path);
    std::size_t old = m_memoryBlock.size();
    m_memoryBlock.resize(old + length);
    std::memcpy(&m_memoryBlock[old], path, length);
    return Core::StringView(&m_memoryBlock[old], &m_memoryBlock.back());
  }

  Core::StringView Context::createView(const char* path, std::size_t start, std::size_t end) {
    // copy the path to own memory block and create a string view
    std::size_t length = end - start;
    std::size_t old = m_memoryBlock.size();
    m_memoryBlock.resize(old + length);
    std::memcpy(&m_memoryBlock[old], &path[start], length);
    return Core::StringView(&m_memoryBlock[old], &m_memoryBlock.back());
  }

  bool Context::ignoreModule(const std::string& moduleName, const std::string& modulePath) const {
    if (!moduleName.empty()) {
      for (const auto& regex : m_moduleNamesToIgnore) {
        if (std::regex_match(moduleName, std::regex(regex))) {
          return true;
        }
      }
    }

    if (!modulePath.empty()) {
      for (const auto& regex : m_modulePathsToIgnore) {
        if (std::regex_match(modulePath, std::regex(regex))) {
          return true;
        }
      }
    }
    return false;
  }

  bool Context::excludeModule(const std::string& moduleName, const std::string& modulePath) const {
    if (!moduleName.empty()) {
      for (const auto& regex : m_moduleNamesToExclude) {
        if (std::regex_match(moduleName, std::regex(regex))) {
          return true;
        }
      }
    }

    if (!modulePath.empty()) {
      for (const auto& regex : m_modulePathsToExclude) {
        if (std::regex_match(modulePath, std::regex(regex))) {
          return true;
        }
      }
    }
    return false;
  }

  const char* findLastOfPathSeparator(const char* str) {
    const char* end = nullptr;
    for (const char* i = str; *i != '\0'; ++i) {
      if (*i == '\\' || *i == '/') {
        end = i;
      }
    }
    return end;
  }

  void Context::registerTo(chaiscript::ChaiScript& chai, Context& context, chaiscript::ModulePtr m) {
    // add search path
    chai.add(chaiscript::fun([&context](const std::string& path, Dependency::Context::DirectoryExpandBehavior behaviour) { context.addSearchPath(path.c_str(), behaviour); }), "addSearchPath");

    REGISTER_ENUM_LITERAL(chai, Dependency::Context::DirectoryExpandBehavior::OnlyAddDirectory, "OnlyAddDirectory");
    REGISTER_ENUM_LITERAL(chai, Dependency::Context::DirectoryExpandBehavior::AddAllSubDirectories, "AddAllSubDirectories");
    REGISTER_ENUM_LITERAL(chai, Dependency::Context::DirectoryExpandBehavior::AddAllSubDirectoriesRecursivly, "AddAllSubDirectoriesRecursivly");
    REGISTER_ENUM_OPERATORS(chai, Dependency::Context::DirectoryExpandBehavior);

    // add search path from environment
    chai.add(chaiscript::fun([&context](const std::string& path) { 
      context.addSearchPathsFromEnvironment(path.c_str()); 
    }), "addSearchPathsFromEnvironment");

    // escape for reg exp
    chai.add(chaiscript::fun([&context](const std::string& path) {
      std::string temp;
      temp.reserve(path.size() + 16);
      for (std::size_t i = 0; i < path.size(); ++i) {
        if (path[i] == '\\') {
          temp.push_back('\\');
        } 
        temp.push_back(path[i]);
      }
      return temp;
    }), "escapeForRegExp");

    // add file to search path
    chai.add(chaiscript::fun([&context](const std::string& path) {
      const char* end = findLastOfPathSeparator(path.c_str());
      if (end) {
        context.m_searchPaths.push_back(context.createView(path.c_str(), 0, end - path.c_str()));
      }
    }), "addFileToSearchPath");
#pragma endregion 

    chai.add(chaiscript::fun([&context](const std::string& file) { 
      Core::StringView view = context.createView(file.c_str(), 0, file.size());
      char* c = const_cast<char*>(view.begin());
      while (c <= view.end()) {
        *c = toupper(*c);
        ++c;
      }
      context.m_initialFiles.push_back(view); 
    }), "addInitialFile");

    chai.add(chaiscript::fun([&context](const std::string& name) { 
       context.m_moduleNamesToExclude.push_back(name); 
    }), "excludeModuleName");
    chai.add(chaiscript::fun([&context](const std::string& path) { 
      context.m_modulePathsToExclude.push_back(path); 
    }), "excludeModulePath");
    chai.add(chaiscript::fun([&context](const std::string& name) { 
      context.m_moduleNamesToIgnore.push_back(name); 
    }), "ignoreModuleName");
    chai.add(chaiscript::fun([&context](const std::string& path) { 
      context.m_modulePathsToIgnore.push_back(path); 
    }), "ignoreModulePath");

    chai.add(chaiscript::fun([&context](const std::string& moduleName) {
      return context.findFile(moduleName);
    }), "findFile");

    chai.add(chaiscript::fun([&context](const std::string& moduleName, const std::string& modulePath) {
      return context.excludeModule(moduleName, modulePath);
    }), "isExcluded");
    chai.add(chaiscript::fun([&context](const std::string& moduleName, const std::string& modulePath) {
      return context.ignoreModule(moduleName, modulePath);
    }), "isIgnored");

  }

}