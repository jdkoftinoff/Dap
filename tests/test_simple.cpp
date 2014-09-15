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

#include "jdksdap_world.hpp"
#include "jdksdap.hpp"
#include <iostream>

template <typename T, size_t Width, size_t Height, size_t Depth>
std::ostream &operator<<( std::ostream &ostr, jdksdap::block<T, Width, Height, Depth> const &v )
{
    ostr << "{ ";
    for ( size_t w = 0; w < Width; ++w )
    {
        ostr << " {";
        for ( size_t h = 0; h < Height; ++h )
        {
            ostr << " {";
            for ( size_t d = 0; d < Depth; ++d )
            {
                T a = get( v, w, h, d );
                std::cout << a << " ";
            }
            std::cout << "},";
        }
        std::cout << "}\n";
    }
    return ostr;
}

template <typename T, size_t Width, size_t Height, size_t Depth>
std::ostream &operator<<( std::ostream &ostr, jdksdap::rotated_width_block<T, Width, Height, Depth> const &v )
{
    ostr << "{ ";
    for ( size_t w = 0; w < Width; ++w )
    {
        ostr << " {";
        for ( size_t h = 0; h < Height; ++h )
        {
            ostr << " {";
            for ( size_t d = 0; d < Depth; ++d )
            {
                T a = get( v, w, h, d );
                std::cout << a << " ";
            }
            std::cout << "},";
        }
        std::cout << "}\n";
    }
    return ostr;
}

int main()
{
    using namespace jdksdap;

    auto v1 = make_block<4, 2, 3>( 1.0f );
    auto v2 = make_block<4, 2, 3>( 2.0f );
    auto v3 = make_block<4, 2, 3>( 3.0f );
    auto rv4 = make_rotated_width_block<4,2,3>(1.0f);
    auto rv5 = fill_rotated_width_block<float,4,2,3>( [](size_t w,size_t h,size_t d){ return (w * 1.0f) + (h * 10.0f) + (d * 1000.0f); } );

    std::cout << v1 << std::endl;
    std::cout << v2 << std::endl;
    std::cout << rv4 << std::endl;
    std::cout << rv5 << std::endl;

    for ( size_t w = 0; w < v1.width; ++w )
    {
        for ( size_t h = 0; h < v1.height; ++h )
        {
            for ( size_t d = 0; d < v1.depth; ++d )
            {
                set( 0.0f, v1, w, h, d );
                set( static_cast<float>( w * 1 + h * 10 + d * 1000 ), v2, w, h, d );
                set( 0.0f, v3, w, h, d );
            }
        }
    }
    std::cout << v2 << std::endl << std::endl;

    {
        float *p = &rawget( v2 );
        for ( size_t i = 0; i < 4 * 2 * 16; ++i )
        {
            std::cout << *p++ << std::endl;
        }
    }

    auto rv2 = rotate( v2 );
    std::cout << rv2 << std::endl;
    {
        float *p = &rawget( rv2 );
        for ( size_t i = 0; i < 4 * 2 * 16; ++i )
        {
            std::cout << *p++ << std::endl;
        }
    }

    apply( v2,
           rv2,
           v1,
           []( float a, float b )
    { return a + b + 1.0f; } );

    std::cout << v1 << std::endl;

#if 0
    apply_in_place( v1, [&](float ){ return c+=1.0f; } );
    apply_in_place( v2, [](float ){ return 1.0f; } );
    apply_in_place( v3, [](float ){ return 0.0f; } );
    apply( v1, v3, [](float f){return f*100.0;});
    apply_in_place( v3, [](float f){ std::cout << f << std::endl; return f; } );
#endif
    return 0;
}
