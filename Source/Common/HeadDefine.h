#pragma once

#ifdef _SSG_DLLEXPORT
#define _SSG_DLLIMPEXP __declspec(dllexport)
#else
#define _SSG_DLLIMPEXP __declspec(dllimport)
#endif

#ifdef _POST_DLL
#define _POST_DLLIMPEXP __declspec(dllexport)
#else
#define _POST_DLLIMPEXP __declspec(dllimport)
#endif

#ifdef _MESH_DLL
#define _MESH_DLLIMPEXP __declspec(dllexport)
#else
#define _MESH_DLLIMPEXP __declspec(dllimport)
#endif

#ifdef _SSG_OPENGLDLLEXPORT   //不能与SSGAPI中的相同
#define _SSG_OPENGLDLL __declspec(dllexport)
#else
#define _SSG_OPENGLDLL __declspec(dllimport)
#endif

#define _POST_FUN extern "C" _POST_DLLIMPEXP