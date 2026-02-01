#pragma once

#ifdef SO_PLATFORM_WINDOWS
    #ifdef SO_DEBUG
        #define SO_ASSERT(x, ...) if (!(x)) { printf("ASSERT: %s", __VA_ARGS__); __debugbreak(); }
    #elif defined(SO_RELEASE)
        #define SO_ASSERT(x, ...)
    #endif
#elif defined(SO_PLATFORM_LINUX)
    #ifdef SO_DEBUG
        #define SO_ASSERT(x, ...) if (!(x)) { printf("ASSERT: %s", __VA_ARGS__); raise(SIGTRAP); }
    #elif defined(SO_RELEASE)
        #define SO_ASSERT(x, ...)
    #endif
#endif

#define BIND_EVENT_FN(fn) [](auto&&... args) -> decltype(auto) { return fn(std::forward<decltype(args)>(args)...); }
