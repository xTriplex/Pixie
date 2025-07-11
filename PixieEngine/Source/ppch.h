#pragma once

// Standard Library
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <unordered_map>

// Engine Core
#include "Core/Core.h"

// Platform Detection
#if defined(_WIN32) || defined(_WIN64)
	#ifndef PX_PLATFORM_WINDOWS
		#define PX_PLATFORM_WINDOWS
	#endif
#elif defined(__APPLE__)
	#ifndef PX_PLATFORM_MAC
		#define PX_PLATFORM_MAC
	#endif
#elif defined(__linux__)
	#ifndef PX_PLATFORM_LINUX
		#define PX_PLATFORM_LINUX
	#endif
#else
	#error "Unknown platform!"
#endif

// Windows-specific includes
#ifdef PX_PLATFORM_WINDOWS
	#ifndef WIN32_LEAN_AND_MEAN
		#define WIN32_LEAN_AND_MEAN
	#endif
	#include <Windows.h>
#endif
