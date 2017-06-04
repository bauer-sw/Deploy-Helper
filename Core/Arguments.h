// ----------------------
//      Jakob Bauer
//       (c) 2016 
//    www.bauer-sw.de
// ----------------------
//    cpp@bauer-sw.de
// ----------------------
#pragma once
#include "StringView.h"

namespace Core {

  /// <summary>Helper class to parse the command line arguments.</summary>  
  class CORE_API Arguments {
  public:
    /// <summary>Constructor.</summary>
    /// <param name="argc">Argument count.</param>
    /// <param name="argv">Command line argument.</param>
    /// <param name="separator">Pre-character of each argument switch.</param>
    Arguments(int argc, char* argv[], const Core::StringView& separator);

    /// <summary>Destructor.</summary>
    ~Arguments();

    /// <summary>Returns the name of the executable.</summary>
    /// <returns>Name of executable.</returns>
    Core::StringView getExecutableName() const {
      return m_arguments[0];
    }

    /// <summary>Test if a specific switch is given.</summary>
    /// <param name="name">Switch name.</param>
    /// <returns>TRUE: Switch exits, FALSE: Otherwise.</returns>
    bool hasSwitch(const char* name) const;

    /// <summary>Test if a specific switch is given.</summary>
    /// <param name="name">Switch name.</param>
    /// <returns>TRUE: Switch exits, FALSE: Otherwise.</returns>
    bool contains(const char* name) const {
      return hasSwitch(name);
    }

    /// <summary>Get value of an argument as string view.</summary>
    /// <param name="name">Switch name.</param>
    /// <param name="ok">[OUT] if pointer valid; TRUE = switch exists, FALSE = otherwise.</param>
    /// <returns>First argument of the given switch.</returns>
    Core::StringView get(const char* name, bool* ok = nullptr) const {
      std::size_t i = findArgument(name);
      if (!isIndexValid(i)) {
        if (ok != nullptr) {
          *ok = false;
        }
        return Core::StringView();
      }

      if (ok != nullptr) {
        *ok = true;
      }
      return m_arguments[i];
    }

    /// <summary>Get argument values from a specifc switch.</summary>
    /// <param name="name">Switch name.</param>
    /// <param name="arguments">Selected arguments.</param>
    /// <returns>TRUE: all arguments correctly converted, FALSE: otherwise.</returns>
    template<typename... ARGS>
    bool get(const char* name, ARGS&... arguments) const {
      std::size_t i = findArgument(name);
      if (!isIndexValid(i)) {
        return false;
      }

      return getPrivate(i + 1, arguments...);
    }

    /// <summary>Test if given argument is valid.</summary>
    /// <param name="i">Index of a specific argument.</param>
    /// <returns>TRUE: index is valid, FALSE: index is out of range.</returns>
    bool isIndexValid(std::size_t i) const {
      return i < m_arguments.size();
    }

    /// <summary>Get the argument count.</summary>
    /// <returns>Size.</returns>
    std::size_t size() const {
      return m_arguments.size();
    }

  private:
    /// <summary>Test if argument at specific position a switch.</summary>
    /// <remarks>Assumption: i < size()</remarks>
    /// <param name="i">Index of the argument.</param>
    /// <returns>TRUE: argument/switch is given, FALSE: otherwise (e.g. argument value).</returns>
    bool isArgument(std::size_t i) const {
      return m_arguments[i].startsWith(m_separator);
    }

    /// <summary>Find argument/switch by name.</summary>
    /// <param name="name">Name.</summary>
    /// <returns>Index of the argument. Index is invalid if argument is not found.</returns>
    std::size_t findArgument(const char* name) const {
      for (std::size_t i = 0; i < m_arguments.size(); ++i) {
        if (isArgument(i) && Core::StringView::isEqual(m_arguments[i].begin() + 1, m_arguments[i].end(), name)) {
          return i;
        }
      }
      return std::size_t(-1);
    }

    /// <summary>Helper to convert argument at specific position to a specific data type.</summary>
    /// <param name="index">Index of the argument.</param>
    /// <param name="head">Target data type and reference to store it.</param>
    /// <returns>TRUE: argument exists and converted, FALSE: otherwise.</returns>
    template<typename HEAD>
    bool getPrivate(std::size_t index, HEAD& head) const {
      if (!isIndexValid(index) || isArgument(index)) {
        return false;
      }

      head = m_arguments[index].as<HEAD>();
      return true;
    }

    /// <summary>Helper to convert argument at specific position to a specific data type.</summary>
    /// <param name="index">Index of the argument.</param>
    /// <param name="head">Target data type and reference to store it.</param>
    /// <param name="tail">Other target data types and references to store it.</param>
    /// <returns>TRUE: argument exists and converted, FALSE: otherwise.</returns>
    template<typename HEAD, typename... TAIL>
    bool getPrivate(std::size_t index, HEAD& head, TAIL&... tail) const {
      if (!getPrivate<HEAD>(index, head)) {
        return false;
      }

      head = m_arguments[index].as<HEAD>();
      getPrivate<TAIL...>(index + 1, tail...);
      return true;
    }

    /// <summary>Store the separator to mark a switch.</summary>
    Core::StringView m_separator;

    /// <summary>Store all arguments.</summary>
    StringView::Vector m_arguments;
  };

}