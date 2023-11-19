#pragma once
#ifdef _WIN32
    #define PLATFORM_WINDOWS
#elif defined(__LINUX__)
    #define PLATFORM_LINUX
#endif

#include <memory>
#include <cstdint>
#include <cmath>

#include "SAssert.h"


template<class T>
using Ref = std::shared_ptr<T>;