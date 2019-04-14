#pragma once

#ifdef DRAUG_WINDOWS
	#ifdef DRAUG_SHARED_LIB
		#ifdef DRAUG_BUILD_DLL
			#define DRAUG_API __declspec(dllexport)
		#else
			#define DRAUG_API __declspec(dllimport)
		#endif
	#endif
#endif
#ifndef DRAUG_API
#define DRAUG_API 
#endif

