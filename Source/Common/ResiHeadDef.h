#pragma once

#ifdef _RESI_DLL
#define _RESI_DLLIMPEXP __declspec(dllexport)
#else
#define _RESI_DLLIMPEXP __declspec(dllimport)
#endif

#define _RESI_FUN extern "C" _RESI_DLLIMPEXP