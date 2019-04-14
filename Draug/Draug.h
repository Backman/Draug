#pragma once

#ifdef DRAUG_DYNAMIC_LIB
	#ifdef DRAUG_PLATFORM_WINDOWS
		#ifdef DRAUG_BUILD_DLL
			#define DRAUG_API __declspec(dllexport)
		#else 
			#define DRAUG_API __declspec(dllimport)
		#endif
	#endif
#else
	#define DRAUG_API 
#endif
