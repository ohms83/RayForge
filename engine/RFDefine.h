#pragma once

#include <memory>

#define RF_API
#define RF_UNUSED(x) (void)(x)
#define RF_DEPRECATED [[deprecated]]
#define RF_DEPRECATED_MSG(msg) [[deprecated(msg)]]
#define RF_MAYBE_UNUSED [[maybe_unused]]
#define RF_NODISCARD [[nodiscard]]

#define RF_STRINGIFY(x) #x
#define RF_CONCAT(a, b) a##b

#define RF_NAMESPACE namespace rf
#define USING_RF using namespace rf

namespace rf
{
    /**
     * Reference counting type. This is just an alias to @c std::shared_ptr.
     */
    template<typename T>
    using Ref = std::shared_ptr<T>;

    /**
     * Auto-release pointer. This is just an alias to @c std::unique_ptr.
     */
    template<typename T>
    using Ptr = std::unique_ptr<T>;

    /**
     * Weak reference type. This is just an alias to @c std::weak_ptr.
     */
    template<typename T>
    using WeakRef = std::weak_ptr<T>;
}