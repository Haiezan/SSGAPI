#pragma once

#ifdef _PUB_DLL
#define _PUB_DLLIMPEXP __declspec(dllexport)
#else
#define _PUB_DLLIMPEXP __declspec(dllimport)
#endif


extern _PUB_DLLIMPEXP int global_language;