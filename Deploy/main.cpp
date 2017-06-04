// ----------------------
//      Jakob Bauer
//       (c) 2016 
//    www.bauer-sw.de
// ----------------------
//    cpp@bauer-sw.de
// ----------------------


#include "stdafx.h"

#include <fstream>

#include "chaiscript/chaiscript.hpp"
#include "chaiscript/chaiscript_stdlib.hpp"

//#include <WinBase.h>

#include "Core/StringView.h"

#include "Graph.h"
#include "TextFileWriter.h"
#include "ChaiMacros.h"
#include "CoreLibrary.h"


void writeToConsole(const std::string& value) {
  std::cout << value << std::endl;
}

std::string getValueFromEnvironment(const std::string& name) {
  char* path = nullptr;
  std::size_t pathSize = 0;
  _dupenv_s(&path, &pathSize, name.c_str());
  if (!path || pathSize == 0) {
    return std::string();
  }
  return std::string(path, pathSize-1);
}


int main( int argc, const char* argv[] ) { 
  if (argc < 1) {
    std::cerr << "Chai script is missing as first argument!" << std::endl;
    std::cerr << "Example: deploy.exe dotWriter.chai" << std::endl;
    return EXIT_FAILURE;
  }

  Dependency::Context context;

  chaiscript::ChaiScript chai(chaiscript::Std_Lib::library());

  chai.add(chaiscript::bootstrap::standard_library::vector_type<std::vector<std::string>>("StringVector"));
  chai.add(chaiscript::fun(&getValueFromEnvironment), "getValueFromEnvironment");

#pragma region search path  

  chai.add(chaiscript::fun([argc]() { return argc; }), "getArgumentCount");
  chai.add(chaiscript::fun<std::function<std::string(int)>>([&argv](int i) { return argv[i]; }), "getArgument");

  chaiscript::ModulePtr coreModule = chaiscript::ModulePtr(new chaiscript::Module());
  Dependency::CoreLibrary::registerTo(chai, context, coreModule);
  chai.add(coreModule);

  chai.add(chaiscript::fun(&writeToConsole), "writeToConsole");

  //
  //
  //
  chaiscript::ModulePtr m = chaiscript::ModulePtr(new chaiscript::Module());
  chaiscript::utility::add_class<Dependency::Graph>(*m,
    "Graph",
    { },
    { 
      { chaiscript::fun(&Dependency::Graph::getNumOfDependecyFiles), "getNumOfFiles" },
      { chaiscript::fun(&Dependency::Graph::getDepedencyFileByIndex), "getFile" },
      { chaiscript::fun(&Dependency::Graph::getModuleState), "getFileState" },
      { chaiscript::fun(&Dependency::Graph::getFilePath), "getFilePath" },
      { chaiscript::fun(&Dependency::Graph::getDependencies), "getFileDependencies" }
    }
  );

  Dependency::Context::registerTo(chai, context, m);
  Dependency::File::registerTo(chai, context, m);

  chai.add(chaiscript::fun([&context]() { return Dependency::Graph::process(context); }), "buildGraph");

  chaiscript::utility::add_class<TextFileWriter>(*m,
    "TextFileWriter",
    {
      { chaiscript::constructor<TextFileWriter(const std::string&)>() }
    },       
    {
      { chaiscript::fun(&TextFileWriter::isOpen), "isOpen"},
      { chaiscript::fun(&TextFileWriter::write), "write" },
      { chaiscript::fun(&TextFileWriter::writeln), "writeln" }
    });

  chai.add(m);

  try {
    //chai.eval("addSearchPath(\"hello world\", AddAllSubDirectories);");
    //chai.eval_file(R"(C:\Users\jb\Documents\Visual Studio 2015\Projects\Depends\test.chai)");
    chai.eval_file(argv[1]);
  } catch (const std::exception& exp) {
    std::cerr << std::endl << exp.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
