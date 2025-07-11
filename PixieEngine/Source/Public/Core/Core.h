#pragma once

#include <cassert>

namespace Pixie
{
	//--------------------------------------------------------------
	// Versioning
	//--------------------------------------------------------------
	#define PX_VERSION_MAJOR 0
	#define PX_VERSION_MINOR 1
	#define PX_VERSION_PATCH 2

	#define PX_STR_HELPER(x) #x
	#define PX_STR(x)        PX_STR_HELPER(x)
	#define PIXIE_VERSION    PX_STR(PX_VERSION_MAJOR) "." \
							 PX_STR(PX_VERSION_MINOR) "." \
							 PX_STR(PX_VERSION_PATCH)

	//--------------------------------------------------------------
	// Assertions
	//--------------------------------------------------------------
	#ifdef PX_DEBUG
		#define PX_ENABLE_ASSERTS
	#endif

	#ifdef PX_ENABLE_ASSERTS
		#define PX_CORE_ASSERT(x, msg) \
			{ if (!(x)) { assert((x) && msg); } }
	#else
		#define PX_CORE_ASSERT(x, msg)
	#endif

	//--------------------------------------------------------------
	// Common aliases
	//--------------------------------------------------------------
	using byte = uint8_t;
	using uint = unsigned int;

	//--------------------------------------------------------------
	// Smart-pointer helpers
	//--------------------------------------------------------------
	template<typename T, typename... Args>
	constexpr std::unique_ptr<T> CreateUnique(Args&&... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T, typename... Args>
	constexpr std::shared_ptr<T> CreateShared(Args&&... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}