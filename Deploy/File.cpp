// ----------------------
//      Jakob Bauer
//       (c) 2016 
//    www.bauer-sw.de
// ----------------------
//    cpp@bauer-sw.de
// ----------------------
#include "File.h"

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <sstream>
#include <sys/stat.h>
#include <shellapi.h>

#include "Core/File.h"

#include "ChaiMacros.h"
#include "chaiscript/chaiscript_stdlib.hpp"

namespace Dependency {

  // Convert Virtual Address to File Offset
  DWORD Rva2Offset(DWORD rva, PIMAGE_SECTION_HEADER psh, PIMAGE_NT_HEADERS pnt) {
    if (rva == 0) {
      return 0;
    }

    for (size_t i = 0; i < pnt->FileHeader.NumberOfSections; ++i) {
      if (rva >= psh->VirtualAddress && rva < psh->VirtualAddress + psh->Misc.VirtualSize) {
        break;
      }
      ++psh;
    }
    return rva - psh->VirtualAddress + psh->PointerToRawData;
  }

  std::size_t find(const std::vector<char>& content, std::size_t offset, char pre) {
    for (; offset < content.size(); ++offset) {
      if (content[offset] == pre) {
        return offset;
      }
    }
    return std::size_t(-1);
  }

  File::File()
    : m_state(State::NotHandled)
  {
  }

  File File::process(std::string&& name, std::string&& modulePath, const Context& context) {    
    // create a new dummy file
    File file;
    // moving arguments
    file.m_moduleName = std::move(name);
    file.m_filePath = std::move(modulePath);

    // should be the file to ignore? e.g. windows API files
    if (context.ignoreModule(file.getModuleName(), file.m_filePath)) {
      file.m_state = State::Ignored;
      return file;
    }

    // test if the file path is valid
    if (file.m_filePath.empty()) {
      file.m_state = State::NotFound;
      return file;
    }

#if 1
    std::string tempfile(L_tmpnam, '\0');
    if (tmpnam_s(&tempfile.front(), tempfile.size())) {
      file.m_state = State::NotHandled;
      return file;
    }
    tempfile.resize(tempfile.find('\0'));

    {
      std::string params = std::string("/c /f:0 /a:0 /oc:\"") + tempfile + std::string("\" \"") + file.getFilePath() + std::string("\"");

      SHELLEXECUTEINFO ShExecInfo = { 0 };
      ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
      ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
      ShExecInfo.hwnd = NULL;
      ShExecInfo.lpVerb = NULL;
      ShExecInfo.lpFile = "depends.exe";
      ShExecInfo.lpParameters = params.c_str();
      ShExecInfo.lpDirectory = NULL;
      ShExecInfo.nShow = SW_SHOW;
      ShExecInfo.hInstApp = NULL;

      ShellExecuteEx(&ShExecInfo);
      WaitForSingleObject(ShExecInfo.hProcess, INFINITE);
    }

    static std::vector<char> cache;    

    Core::IO::File::readContent(tempfile, cache);

    std::size_t offset = 0;
    std::size_t end = 0;
    while ((offset = find(cache, offset, '\n')) != std::size_t(-1)) {
      offset = find(cache, offset, '\"');
      end = find(cache, offset + 1, '\"');

      if (offset == std::size_t(-1) || end == std::size_t(-1)) {
        break;
      }

      // build string from cache
      std::string mn = std::string(&cache[offset + 1], end - offset - 1);

      if (mn == file.m_moduleName) {
        // ignore my own
        continue;
      }      

      // add module name to depends
      file.m_dependsOn.push_back(std::move(mn));
    }

    remove(tempfile.c_str());
#else
    // create a new memory handle
    HANDLE handle = CreateFileA(file.m_filePath.c_str(), GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if (handle == INVALID_HANDLE_VALUE) {
      // cannot handle this file
      file.m_state = State::NotHandled;
      return file;
    }

    DWORD byteread, size = GetFileSize(handle, NULL);
    PVOID virtualpointer = VirtualAlloc(NULL, size, MEM_COMMIT, PAGE_READWRITE);
    if (virtualpointer == nullptr || !ReadFile(handle, virtualpointer, size, &byteread, NULL)) {
      // any error occurs - maybe a misleading read permission?
      file.m_state = State::Error;
      CloseHandle(handle);
      return file;
    }

    // get the handle free
    CloseHandle(handle);

    // Get pointer to NT header
    PIMAGE_NT_HEADERS           ntheaders = (PIMAGE_NT_HEADERS)(PCHAR(virtualpointer) + PIMAGE_DOS_HEADER(virtualpointer)->e_lfanew);
    PIMAGE_SECTION_HEADER       pSech = IMAGE_FIRST_SECTION(ntheaders);//Pointer to first section header
    PIMAGE_IMPORT_DESCRIPTOR    pImportDescriptor; //Pointer to import descriptor 

    // if size of the table is 0 - Import Table does not exist
    if (ntheaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size != 0) {
      pImportDescriptor = (PIMAGE_IMPORT_DESCRIPTOR)((DWORD_PTR)virtualpointer + Rva2Offset(ntheaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress, pSech, ntheaders));

      // Walk until you reached an empty IMAGE_IMPORT_DESCRIPTOR
      while (pImportDescriptor->Name != NULL) {
        //Get the name of each DLL
        const PCHAR moduleName = (PCHAR)((DWORD_PTR)virtualpointer + Rva2Offset(pImportDescriptor->Name, pSech, ntheaders));
        // add module name to depends
        file.m_dependsOn.push_back(moduleName);
        //advance to next IMAGE_IMPORT_DESCRIPTOR
        ++pImportDescriptor; 
      }

      file.m_state = State::Valid;
    } else {
      // no import table found
      file.m_state = State::NoImportTable;
    }

    VirtualFree(virtualpointer, size, MEM_DECOMMIT | MEM_RELEASE);
#endif
    return file;
  }

  File::~File() {
  }

  void File::registerTo(chaiscript::ChaiScript& chai, Context& context, chaiscript::ModulePtr m) {
    REGISTER_ENUM_LITERAL(chai, Dependency::File::State::Error, "Error");
    REGISTER_ENUM_LITERAL(chai, Dependency::File::State::Ignored, "Ignored");
    REGISTER_ENUM_LITERAL(chai, Dependency::File::State::NoImportTable, "NoImportTable");
    REGISTER_ENUM_LITERAL(chai, Dependency::File::State::NotFound, "NotFound");
    REGISTER_ENUM_LITERAL(chai, Dependency::File::State::NotHandled, "NotHandled");
    REGISTER_ENUM_LITERAL(chai, Dependency::File::State::Valid, "Valid");
    REGISTER_ENUM_OPERATORS(chai, Dependency::File::State);

    chaiscript::utility::add_class<Dependency::File>(*m,
      "File",
      {},
      { { chaiscript::fun(&Dependency::File::getModuleName), "getModuleName" },
      { chaiscript::fun(&Dependency::File::getFilePath), "getFilePath" },
      { chaiscript::fun(&Dependency::File::getState), "getState" },
      { chaiscript::fun(&Dependency::File::getDependencies), "getDependencies" }
      }
    );
  }

}