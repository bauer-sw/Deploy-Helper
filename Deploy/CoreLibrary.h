// ----------------------
//      Jakob Bauer
//       (c) 2016 
//    www.bauer-sw.de
// ----------------------
//    cpp@bauer-sw.de
// ----------------------
#pragma once

#include <chaiscript/chaiscript.hpp>

#include "Context.h"

namespace Dependency {

  class CoreLibrary {
  public:
    static void registerTo(chaiscript::ChaiScript& chai, Context& context, chaiscript::ModulePtr m);

  private:
    static void registerArgumentsTo(chaiscript::ChaiScript& chai, Context& context, chaiscript::ModulePtr m);

  protected:
    CoreLibrary() {}
    ~CoreLibrary() {}
  };

}