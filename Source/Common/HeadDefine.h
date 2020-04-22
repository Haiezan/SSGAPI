#pragma once

#ifdef _SSG_DLLEXPORT
#define _SSG_DLLIMPEXP __declspec(dllexport)
#else
#define _SSG_DLLIMPEXP __declspec(dllimport)
#endif