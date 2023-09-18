#ifdef _WIN32
    #define PLATFORM_WINDOWS
#elif defined(__LINUX__)
    #define PLATFORM_LINUX
#endif

#include <memory>
#include <cstdint>

template<class T>
using Scope = std::unique_ptr<T>;

template<class T, class ...Args>
inline Scope<T> create_scope(Args&&... args) {
    return std::make_unique<T>(std::forward<Args>(args)...); 
}