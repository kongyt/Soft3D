#ifndef _Dll_Api_H__
#define _Dll_Api_H__

#ifdef GEN_DLL
#define DLLAPI   __declspec( dllexport )
#else
#define DLLAPI   __declspec( dllimport )
#endif

#endif