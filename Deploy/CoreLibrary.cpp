// ----------------------
//      Jakob Bauer
//       (c) 2016 
//    www.bauer-sw.de
// ----------------------
//    cpp@bauer-sw.de
// ----------------------
#pragma once

#include "CoreLibrary.h"

namespace Dependency {
  
  void CoreLibrary::registerTo(chaiscript::ChaiScript& chai, Context& context, chaiscript::ModulePtr m) {
    registerArgumentsTo(chai, context, m);
  }

  void CoreLibrary::registerArgumentsTo(chaiscript::ChaiScript& chai, Context& context, chaiscript::ModulePtr m) {

  }

}