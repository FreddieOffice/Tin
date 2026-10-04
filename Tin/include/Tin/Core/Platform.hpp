#ifndef TIN_CORE_PLATFORM_HPP
#define TIN_CORE_PLATFORM_HPP

// Platform detection

#ifdef _WIN32
    // Windows platforms
	#ifdef _WIN64
		// Windows x64
		#define TIN_PLATFORM_WINDOWS
	#elif
		// Windows x86
		#error x86 windows is not supported
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
    // Apple platforms
	#include <TargetConditionals.h>

	// Apple platforms must be checked in this order
	// Since TARGET_OS_MAC is defined on all of them
	#if TARGET_OS_IPHONE == 1 || TARGET_IPHONE_SIMULATOR == 1
	    // iOS
		#define TIN_PLATFORM_IOS
		#error iOS is not supported
	#elif TARGET_OS_MAC == 1
	    // macOS
		#define TIN_PLATFORM_MACOS
		#error macOS is not supported
	#else
		#error Unknown apple platform
	#endif
#elif defined(__unix__)
    // Unix platforms
	// __ANDROID__ must be checked before anything else since it has __linux__ defined
	#ifdef __ANDROID__
		// Android
		#define TIN_PLATFORM_ANDROID
		#error Android is not supported
	#elif defined(__linux__)
	    // Linux
		#define TIN_PLATFORM_LINUX
		#error Linux is not supported
	#elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__DragonFly__)
	    // BSD
		#define TIN_PLATFORM_BSD
		#error BSD platforms are not supported
	#else
		#error Unknown unix platform
	#endif
#else
	#error Unknown platform
#endif

#endif