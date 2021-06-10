//
// Copyright (c) 2015-2020 Microsoft Corporation and Contributors.
// SPDX-License-Identifier: Apache-2.0
//
#ifndef MAT_LEAKY_HPP
#define MAT_LEAKY_HPP

#include "ctmacros.hpp"

namespace MAT_NS_BEGIN
{
    template <typename T>
    class Leaky
    {
       public:
        Leaky()
        {
            new (m_leaked) T();
        }

        ~Leaky() = default;

        T& operator*()
        {
            return *get();
        }

        T* get()
        {
            return reinterpret_cast<T*>(m_leaked);
        }

       private:
        alignas(T) char m_leaked[sizeof(T)];
    };
}
MAT_NS_END

#endif
