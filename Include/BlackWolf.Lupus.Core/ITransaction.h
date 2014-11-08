﻿#pragma once

#include <boost/noncopyable.hpp>

#include "Utility.h"

namespace Lupus {
    namespace Data {
        class LUPUSCORE_API ITransaction : public boost::noncopyable
        {
        public:

            virtual ~ITransaction() = default;

            virtual void Commit() throw(sql_error) = 0;
            virtual void Rollback() throw(sql_error) = 0;
        };
    }
}
