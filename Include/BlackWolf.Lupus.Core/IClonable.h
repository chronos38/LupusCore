﻿#pragma once

#include "Utility.h"
#include <memory>

namespace Lupus {
    template <typename T>
    class IClonable
    {
    public:
        virtual ~IClonable() = default;
        virtual std::shared_ptr<T> Clone() const NOEXCEPT = 0;
    };
}