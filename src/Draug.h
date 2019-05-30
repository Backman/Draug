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

#ifdef DRAUG_WINDOWS
	#include <Windows.h>
#endif

#include <stdint.h>
#include <string>

#include <algorithm>
#include <functional>

#include <vector>
#include <set>
#include <bitset>
#include <tuple>
#include <unordered_map>

#include <bgfx/bgfx.h>
#include <bx/file.h>
#include <bx/allocator.h>
