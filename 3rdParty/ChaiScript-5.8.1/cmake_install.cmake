# Install script for directory: C:/Users/jb/Documents/Visual Studio 2015/Projects/Depends/3rdParty/ChaiScript-5.8.1

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Users/jb/Documents/Visual Studio 2015/Projects/Depends/3rdParty/ChaiScript-5.8.1")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "C:/Users/jb/Documents/Visual Studio 2015/Projects/Depends/3rdParty/ChaiScript-5.8.1/Debug/chai.exe")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "C:/Users/jb/Documents/Visual Studio 2015/Projects/Depends/3rdParty/ChaiScript-5.8.1/Release/chai.exe")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "C:/Users/jb/Documents/Visual Studio 2015/Projects/Depends/3rdParty/ChaiScript-5.8.1/MinSizeRel/chai.exe")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "C:/Users/jb/Documents/Visual Studio 2015/Projects/Depends/3rdParty/ChaiScript-5.8.1/RelWithDebInfo/chai.exe")
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/chaiscript" TYPE MODULE FILES "C:/Users/jb/Documents/Visual Studio 2015/Projects/Depends/3rdParty/ChaiScript-5.8.1/Debug/chaiscript_stdlib-5.8.1.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/chaiscript" TYPE MODULE FILES "C:/Users/jb/Documents/Visual Studio 2015/Projects/Depends/3rdParty/ChaiScript-5.8.1/Release/chaiscript_stdlib-5.8.1.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/chaiscript" TYPE MODULE FILES "C:/Users/jb/Documents/Visual Studio 2015/Projects/Depends/3rdParty/ChaiScript-5.8.1/MinSizeRel/chaiscript_stdlib-5.8.1.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/chaiscript" TYPE MODULE FILES "C:/Users/jb/Documents/Visual Studio 2015/Projects/Depends/3rdParty/ChaiScript-5.8.1/RelWithDebInfo/chaiscript_stdlib-5.8.1.dll")
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/chaiscript" TYPE MODULE FILES "C:/Users/jb/Documents/Visual Studio 2015/Projects/Depends/3rdParty/ChaiScript-5.8.1/Debug/stl_extra.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/chaiscript" TYPE MODULE FILES "C:/Users/jb/Documents/Visual Studio 2015/Projects/Depends/3rdParty/ChaiScript-5.8.1/Release/stl_extra.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/chaiscript" TYPE MODULE FILES "C:/Users/jb/Documents/Visual Studio 2015/Projects/Depends/3rdParty/ChaiScript-5.8.1/MinSizeRel/stl_extra.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/chaiscript" TYPE MODULE FILES "C:/Users/jb/Documents/Visual Studio 2015/Projects/Depends/3rdParty/ChaiScript-5.8.1/RelWithDebInfo/stl_extra.dll")
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "C:/Users/jb/Documents/Visual Studio 2015/Projects/Depends/3rdParty/ChaiScript-5.8.1/include/chaiscript" REGEX "/[^/]*\\.hpp$" REGEX "/[^/]*\\/\\.svn[^/]*$" EXCLUDE REGEX "/[^/]*\\/\\.git[^/]*$" EXCLUDE REGEX "/[^/]*\\~$" EXCLUDE)
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/chaiscript" TYPE DIRECTORY FILES "C:/Users/jb/Documents/Visual Studio 2015/Projects/Depends/3rdParty/ChaiScript-5.8.1/unittests" REGEX "/[^/]*\\.chai$" REGEX "/[^/]*\\.inc$" REGEX "/[^/]*\\/\\.svn[^/]*$" EXCLUDE REGEX "/[^/]*\\/\\.git[^/]*$" EXCLUDE REGEX "/[^/]*\\~$" EXCLUDE)
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/chaiscript" TYPE DIRECTORY FILES "C:/Users/jb/Documents/Visual Studio 2015/Projects/Depends/3rdParty/ChaiScript-5.8.1/samples" REGEX "/[^/]*\\.chai$" REGEX "/[^/]*\\/\\.svn[^/]*$" EXCLUDE REGEX "/[^/]*\\/\\.git[^/]*$" EXCLUDE REGEX "/[^/]*\\~$" EXCLUDE)
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/jb/Documents/Visual Studio 2015/Projects/Depends/3rdParty/ChaiScript-5.8.1/lib/pkgconfig/chaiscript.pc")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "C:/Users/jb/Documents/Visual Studio 2015/Projects/Depends/3rdParty/ChaiScript-5.8.1/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
