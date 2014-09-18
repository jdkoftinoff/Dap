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
#include <iomanip>

template <typename T, typename TwistType, size_t Width, size_t Height, size_t Depth>
std::ostream &operator<<( std::ostream &ostr, jdksdap::block<T, TwistType, Width, Height, Depth> const &v )
{
    ostr << "{\n";
    for ( size_t w = 0; w < Width; ++w )
    {
        ostr << " {";
        for ( size_t h = 0; h < Height; ++h )
        {
            ostr << " {";
            for ( size_t d = 0; d < Depth; ++d )
            {
                T a = jdksdap::get( v, w, h, d );
                std::cout << "(" << w << "," << h << "," << d << "):";
                std::cout << std::setw( 4 ) << a << ( d < Depth - 1 ? ", " : " " );
            }
            std::cout << ( h < Height - 1 ? "}, " : "} " );
        }
        std::cout << ( w < Width - 1 ? "},\n" : "}\n" );
    }
    std::size_t num = Width * Height * Depth;
    T const *p = &v.content[0][0][0];
    for ( std::size_t i = 0; i < num; ++i )
    {
        std::cout << *++p << "\n";
    }
    return ostr;
}

template <typename TwistType>
void dissect_twist( std::string const &name )
{
    std::cout << name << ":\n";
    std::cout << "width_index: " << TwistType::width_index << "\n";
    std::cout << "height_index: " << TwistType::height_index << "\n";
    std::cout << "depth_index: " << TwistType::depth_index << "\n";
    std::cout << "raw_index0_map: " << TwistType::raw_index0_map << "\n";
    std::cout << "raw_index1_map: " << TwistType::raw_index1_map << "\n";
    std::cout << "raw_index2_map: " << TwistType::raw_index2_map << "\n";

    std::cout << "\n";
}

int main()
{
    using namespace jdksdap;

    dissect_twist<twist0>( "twist0" );
    dissect_twist<twist1>( "twist1" );
    dissect_twist<twist2>( "twist2" );
    dissect_twist<twist3>( "twist3" );
    dissect_twist<twist4>( "twist4" );
    dissect_twist<twist5>( "twist5" );

    auto v1 = make_block<twist0, 4, 3, 2>( 1.0f );
    std::cout << "v1:\n" << v1 << std::endl;
    auto v2 = make_block<twist0, 4, 3, 2>( 2.0f );
    std::cout << "v2:\n" << v2 << std::endl;
    auto v3 = make_block<twist0, 4, 3, 2>( 3.0f );
    std::cout << "v3:\n" << v3 << std::endl;
    auto v3_a2 = make_block<twist2, 4, 3, 2>( 3.0f );
    std::cout << "v3_a2:\n" << v3_a2 << std::endl;

    auto v4_a0 = fill_block<float, twist0, 4, 3, 2>( []( size_t w, size_t h, size_t d )
    { return w * 1 + h * 10 + d * 100; } );
    std::cout << "v4_a0:\n" << v4_a0 << std::endl;

    auto v4_a1 = fill_block<float, twist1, 4, 3, 2>( []( size_t w, size_t h, size_t d )
    { return w * 1 + h * 10 + d * 100; } );
    std::cout << "v4_a1:\n" << v4_a1 << std::endl;

    auto v4_a2 = fill_block<float, twist2, 4, 3, 2>( []( size_t w, size_t h, size_t d )
    { return w * 1 + h * 10 + d * 100; } );
    std::cout << "v4_a2:\n" << v4_a2 << std::endl;

    auto v4_a3 = fill_block<float, twist3, 4, 3, 2>( []( size_t w, size_t h, size_t d )
    { return w * 1 + h * 10 + d * 100; } );
    std::cout << "v4_a3:\n" << v4_a3 << std::endl;

    auto v4_a4 = fill_block<float, twist4, 4, 3, 2>( []( size_t w, size_t h, size_t d )
    { return w * 1 + h * 10 + d * 100; } );
    std::cout << "v4_a4:\n" << v4_a4 << std::endl;

    auto v4_a5 = fill_block<float, twist5, 4, 3, 2>( []( size_t w, size_t h, size_t d )
    { return w * 1 + h * 10 + d * 100; } );
    std::cout << "v4_a5:\n" << v4_a5 << std::endl;

    auto rv4_0 = twist_block<0>( v4_a0 );
    auto rv4_1 = twist_block<1>( v4_a0 );
    auto rv4_2 = twist_block<2>( v4_a0 );
    auto rv4_3 = twist_block<3>( v4_a0 );
    auto rv4_4 = twist_block<4>( v4_a0 );
    auto rv4_5 = twist_block<5>( v4_a0 );
    std::cout << "rv4_0:\n" << rv4_0 << std::endl;
    std::cout << "rv4_1:\n" << rv4_1 << std::endl;
    std::cout << "rv4_2:\n" << rv4_2 << std::endl;
    std::cout << "rv4_3:\n" << rv4_3 << std::endl;
    std::cout << "rv4_4:\n" << rv4_4 << std::endl;
    std::cout << "rv4_5:\n" << rv4_5 << std::endl;

#if 0
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
#endif

#if 0
    apply_in_place( v1, [&](float ){ return c+=1.0f; } );
    apply_in_place( v2, [](float ){ return 1.0f; } );
    apply_in_place( v3, [](float ){ return 0.0f; } );
    apply( v1, v3, [](float f){return f*100.0;});
    apply_in_place( v3, [](float f){ std::cout << f << std::endl; return f; } );
#endif
    return 0;
}
