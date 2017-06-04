#pragma once

#ifdef DEPENDS_EXPORTS
  #define DEPENDS_API __declspec(dllexport)
#else
  #define DEPENDS_API //__declspec(dllimport)
#endif // !DEPENDS_EXPORT