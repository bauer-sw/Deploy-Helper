// ----------------------
//      Jakob Bauer
//       (c) 2016 
//    www.bauer-sw.de
// ----------------------
//    cpp@bauer-sw.de
// ----------------------
#pragma once
#include <vector>
#include <string>

#include "Core/StringView.h"

#include "Context.h"

#include "chaiscript/chaiscript.hpp"

namespace Dependency {

  /// <summary>Represents a binary file inclusive the dependencies.</summary>
  class DEPENDS_API File {
  public:
    /// <summary>File parsing state.</summary>
    enum class State {
      /// <summary>All success.</summary>
      Valid,
      /// <summary>Error occurs.</summary>
      Error,
      /// <summary>Ignored by context.</summary>
      Ignored,
      /// <summary>No import table exists.</summary>
      NoImportTable,
      /// <summary>File not found.</summary>
      NotFound,
      /// <summary>Cannot read file.</summary>
      NotHandled
    };

    File();

    File(File && other) = default;

    ~File();

    /// <summary>Process given file.</summary>
    /// <param name="moduleName">Module name.</param>
    /// <param name="modulePath">Module path.</param>
    /// <param name="context">Selected context.</param>
    /// <returns>New file instance.</returns>
    static File process(std::string&& moduleName, std::string&& modulePath, const Context& context);

    /// <summary>Get the processing state.</summary>
    /// <returns>Process state.</returns>
    State getState() const {
      return m_state;
    }

    /// <summary>Get the module name of this file.</summary>
    /// <returns>Module name.</returns>
    const std::string& getModuleName() const {
      return m_moduleName;
    }

    /// <summary>Get the file path of this module.</summary>
    /// <returns>File path.</returns>
    const std::string& getFilePath() const {
      return m_filePath;
    }

    /// <summary>Get the module dependencies of this file.</summary>
    /// <returns>Module dependencies.</returns>
    const std::vector<std::string>& getDependencies() const {
      return m_dependsOn;
    }

    static void registerTo(chaiscript::ChaiScript& chai, Context& context, chaiscript::ModulePtr m);

  private:
    /// <summary>State of the file process.</summary>
    State m_state;

    /// <summary>Module name.</summary>
    std::string m_moduleName;

    /// <summary>File path.</summary>
    std::string m_filePath;

    /// <summary>Depends on module.</summary>
    std::vector<std::string> m_dependsOn;
  };

}