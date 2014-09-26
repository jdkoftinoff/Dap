#pragma once

/*
Copyright (c) 2014, Jeff Koftinoff <jeffk@jdkoftinoff.com> and J.D. Koftinoff Software, Ltd.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

* Neither the name of the {organization} nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "Dap_World.hpp"
#include "Dap_Traits.hpp"
#include "Dap_Vec.hpp"

namespace Dap
{
namespace Constants
{

template <typename T = double>
static constexpr T pi()
{
    return static_cast<T>( 3.14159265358979323846264338327950288419716939937510 );
}

template <typename T = double>
static constexpr T pi_recip()
{
    return static_cast<T>( 1.0 / 3.14159265358979323846264338327950288419716939937510 );
}

template <typename T = double>
static constexpr T pi_over_two()
{
    return static_cast<T>( 3.14159265358979323846264338327950288419716939937510 / 2.0 );
}

template <typename T = double>
static constexpr T two_pi()
{
    return static_cast<T>( 2.0 * 3.14159265358979323846264338327950288419716939937510 );
}

template <typename T = double>
static constexpr T two_pi_recip()
{
    return static_cast<T>( 1.0 / ( 2.0 * 3.14159265358979323846264338327950288419716939937510 ) );
}

template <typename T = double>
static constexpr T e()
{
    return static_cast<T>( 2.7182818284590452353602874713526624977572470936999595749669676277240766 );
}

template <typename T = double>
static constexpr T e_recip()
{
    return static_cast<T>( 1.0 / 2.7182818284590452353602874713526624977572470936999595749669676277240766 );
}

template <typename T = double>
static constexpr T sqrt_2()
{
    return static_cast<T>( 1.4142135623730950488016887242096980785696718753769480 );
}

template <typename T = double>
static constexpr T sqrt_2_recip()
{
    return static_cast<T>( 1.0 / 1.4142135623730950488016887242096980785696718753769480 );
}

template <typename T = double>
static constexpr T log2_e()
{
    return static_cast<T>( 1.442695040888963407359924681001892137427 );
}

template <typename T = double>
static constexpr T log2_ten()
{
    return static_cast<T>( 3.321928094887362347870319429489390175865 );
}

template <typename T = double>
static constexpr T ln2()
{
    return static_cast<T>( 0.69314718055994529 );
}

template <typename T = double>
static constexpr T ln2_recip()
{
    return static_cast<T>( 1.442695040888963407359924681001892137427 );
}

template <typename T = double>
static constexpr T log10_2()
{
    return static_cast<T>( 0.301029995663981195213738894724493026768 );
}

template <typename T = double>
static constexpr T log10_2_recip()
{
    return static_cast<T>( 1.0 / 0.301029995663981195213738894724493026768 );
}

template <typename T = double>
static constexpr T ln10()
{
    return static_cast<T>( 2.30258509299404568402 );
}

template <typename T = double>
static constexpr T ln10_recip()
{
    return static_cast<T>( 1.0 / 2.30258509299404568402 );
}

template <typename T = double>
static constexpr T ten()
{
    return static_cast<T>( 10.0 );
}

template <typename T = double>
static constexpr T twenty_recip()
{
    return static_cast<T>( 1.0 / 20.0 );
}

template <typename T = double>
static constexpr T twenty_div_ln10()
{
    return static_cast<T>( 20.0 / 2.30258509299404568402 );
}

template <typename T = double>
static constexpr T two_gigi()
{
    return static_cast<T>( 2.0 * 1024.0 * 1024.0 * 1024.0 );
}

template <typename T = double>
static constexpr T two_gigi_recip()
{
    return static_cast<T>( 1 / ( 2.0 * 1024.0 * 1024.0 * 1024.0 ) );
}

template <typename T = double>
static constexpr T recip_48k()
{
    return static_cast<T>( 1.0 / ( 48e3 ) );
}

template <typename T = double>
static constexpr T recip_96k()
{
    return static_cast<T>( 1.0 / ( 96e3 ) );
}

template <typename T = double>
static constexpr T recip_192k()
{
    return static_cast<T>( 1.0 / ( 192e3 ) );
}
}
}
