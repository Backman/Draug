#pragma once

#ifdef CREO_DYNAMIC_LIB
	#ifdef CREO_PLATFORM_WINDOWS
		#ifdef CREO_BUILD_DLL
			#define CREO_API __declspec(dllexport)
		#else 
			#define CREO_API __declspec(dllimport)
		#endif
	#endif
#else
	#define CREO_API 
#endif
