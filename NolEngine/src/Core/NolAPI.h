#pragma once

#ifdef NOL_BUILD_DLL
	#define NOL_API __declspec(dllexport)
#else
	#define NOL_API __declspec(dllimport)
#endif
