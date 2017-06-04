// ----------------------
//      Jakob Bauer
//       (c) 2016 
//    www.bauer-sw.de
// ----------------------
//    cpp@bauer-sw.de
// ----------------------
#pragma once

#ifdef CORE_EXPORTS
  #define CORE_API __declspec(dllexport)
#else
  #define CORE_API __declspec(dllimport)
#endif // !CORE_EXPORTS