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
#include "Dap.hpp"
#include <iostream>
#include <iomanip>

template <typename T, typename TwistType, size_t Width, size_t Height, size_t Depth>
std::ostream &operator<<( std::ostream &ostr, Dap::Block<T, TwistType, Width, Height, Depth> const &v )
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
                T a = Dap::get( v, w, h, d );
                std::cout << "[" << w << "," << h << "," << d << "]:";
                std::cout << std::setw( 4 ) << a << ( d < Depth - 1 ? ", " : " " );
            }
            std::cout << ( h < Height - 1 ? "}, " : "} " );
        }
        std::cout << ( w < Width - 1 ? "},\n" : "}\n" );
    }
    std::size_t num = Width * Height * Depth;
    T const *p = &v.content[0][0][0];
    for ( std::size_t i = 0; i < num; ++i, ++p )
    {
        std::cout << *p << "\n";
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
    std::cout << "raw_index0 from 1,2,3: " << TwistType::raw_index0_from( std::make_tuple( 1, 2, 3 ) ) << "\n";
    std::cout << "raw_index1 from 1,2,3: " << TwistType::raw_index1_from( std::make_tuple( 1, 2, 3 ) ) << "\n";
    std::cout << "raw_index2 from 1,2,3: " << TwistType::raw_index2_from( std::make_tuple( 1, 2, 3 ) ) << "\n";
    std::cout << "width from 1,2,3: " << TwistType::width_pos_from( std::make_tuple( 1, 2, 3 ) ) << "\n";
    std::cout << "height from 1,2,3: " << TwistType::height_pos_from( std::make_tuple( 1, 2, 3 ) ) << "\n";
    std::cout << "depth from 1,2,3: " << TwistType::depth_pos_from( std::make_tuple( 1, 2, 3 ) ) << "\n";

    std::cout << "\n";
}

template <typename T>
void do_biquad( double freq, double q )
{
    using namespace Dap;
    typedef T value_type;
    BiQuad<value_type> filter;

    for ( size_t i = 0; i < simd_size<value_type>(); ++i )
    {
        filter.coeffs.calculate_lowpass( i, Constants::recip_96k(), freq, q );
    }

    value_type zero;
    splat( zero, 0.0 );

    auto input_audio = make_block<twist0, 256, 1, 1>( zero );
    auto output_audio = make_block<twist0, 256, 1, 1>( zero );

    value_type one;
    splat( one, 1.0 );
    set( input_audio, one, 0 );

    std::cout << filter.coeffs << std::endl;
    std::cout << filter.state << std::endl;

    for ( size_t w = 0; w < output_audio.width; ++w )
    {
        set( output_audio, filter( get( input_audio, w, 0, 0 ) ), w, 0, 0 );
    }

    std::cout << output_audio << std::endl;
}

int main()
{
    using namespace Dap;

    dissect_twist<twist0>( "twist0" );
    dissect_twist<twist1>( "twist1" );
    dissect_twist<twist2>( "twist2" );
    dissect_twist<twist3>( "twist3" );
    dissect_twist<twist4>( "twist4" );
    dissect_twist<twist5>( "twist5" );

    auto vv4 = make_block<twist0, 4, 3, 2>( Vec<float, 4>{123.0f, 124.0f, 125.0f, 126.0f} );
    std::cout << "vv4:\n" << vv4 << std::endl;
    auto v1 = make_block<twist0, 4, 3, 2>( 1.0f );
    std::cout << "v1:\n" << v1 << std::endl;

    auto vv3 = make_block<twist0, 4, 3, 2>( Vec<float, 3>{0.1f, 0.2f, 0.3f} );
    std::cout << "vv3:\n" << vv3 << std::endl;
    auto v1a = make_block<twist0, 4, 3, 2>( 1.0f );
    std::cout << "v1a:\n" << v1a << std::endl;
    auto v2 = make_block<twist0, 4, 3, 2>( 2.0f );
    std::cout << "v2:\n" << v2 << std::endl;
    auto v3 = make_block<twist0, 4, 3, 2>( 3.0f );
    std::cout << "v3:\n" << v3 << std::endl;
    auto v3_a2 = make_block<twist2, 4, 3, 2>( 3.0f );
    std::cout << "v3_a2:\n" << v3_a2 << std::endl;

    {
        auto v4_a0 = fill_block<float, twist0, 1, 2, 4>([](size_t w, size_t h, size_t d) -> float
        { return static_cast<float>(w * 1.0f + h * 10.0f + d * 100.0f); });
        std::cout << "v4_a0 1,1,4:\n" << v4_a0 << std::endl;
    }
    {
        auto v4_a0 = fill_block<float, twist0, 2, 4, 1>([](size_t w, size_t h, size_t d) -> float
        { return static_cast<float>(w * 1.0f + h * 10.0f + d * 100.0f); });
        std::cout << "v4_a0 1,4,1:\n" << v4_a0 << std::endl;
    }
    {
        auto v4_a0 = fill_block<float, twist0, 4, 1, 2>([](size_t w, size_t h, size_t d) -> float
        { return static_cast<float>(w * 1.0f + h * 10.0f + d * 100.0f); });
        std::cout << "v4_a0 4,1,1:\n" << v4_a0 << std::endl;
    }

    {
        auto v4_a1 = fill_block<float, twist1, 1, 2, 4>([](size_t w, size_t h, size_t d) -> float
        { return static_cast<float>(w * 1.0f + h * 10.0f + d * 100.0f); });
        std::cout << "v4_a1 1,1,4:\n" << v4_a1 << std::endl;
    }
    {
        auto v4_a1 = fill_block<float, twist1, 2, 4, 1>([](size_t w, size_t h, size_t d) -> float
        { return static_cast<float>(w * 1.0f + h * 10.0f + d * 100.0f); });
        std::cout << "v4_a1 1,4,1:\n" << v4_a1 << std::endl;
    }
    {
        auto v4_a1 = fill_block<float, twist1, 4, 1, 2>([](size_t w, size_t h, size_t d) -> float
        { return static_cast<float>(w * 1.0f + h * 10.0f + d * 100.0f); });
        std::cout << "v4_a1 4,1,1:\n" << v4_a1 << std::endl;
    }

    do_biquad<double>( 1e3, 1.0 );
    do_biquad<Vec<float, 4> >( 1e3, 1.0 );

    auto v4_a1 = fill_block<float, twist1, 4, 3, 2>( []( size_t w, size_t h, size_t d ) -> float
    { return static_cast<float>(w * 1.0f + h * 10.0f + d * 100.0f); });
    std::cout << "v4_a1:\n" << v4_a1 << std::endl;

    auto v4_a2 = fill_block<float, twist2, 4, 3, 2>([](size_t w, size_t h, size_t d) -> float
    { return static_cast<float>(w * 1.0f + h * 10.0f + d * 100.0f); });
    std::cout << "v4_a2:\n" << v4_a2 << std::endl;

    auto v4_a3 = fill_block<float, twist3, 4, 3, 2>([](size_t w, size_t h, size_t d) -> float
    { return static_cast<float>(w * 1.0f + h * 10.0f +d * 100.0f); });
    std::cout << "v4_a3:\n" << v4_a3 << std::endl;

    auto v4_a4 = fill_block<float, twist4, 4, 3, 2>([](size_t w, size_t h, size_t d) -> float
    { return static_cast<float>(w * 1.0f + h * 10.0f + d * 100.0f); });
    std::cout << "v4_a4:\n" << v4_a4 << std::endl;

    auto v4_a5 = fill_block<float, twist5, 4, 3, 2>([](size_t w, size_t h, size_t d) -> float
    { return static_cast<float>(w * 1.0f + h * 10.0f + d * 100.0f); });
    std::cout << "v4_a5:\n" << v4_a5 << std::endl;

    auto rv4_0 = twist_block<0>( v4_a1 );
    auto rv4_1 = twist_block<1>( v4_a1 );
    auto rv4_2 = twist_block<2>( v4_a1 );
    auto rv4_3 = twist_block<3>( v4_a1 );
    auto rv4_4 = twist_block<4>( v4_a1 );
    auto rv4_5 = twist_block<5>( v4_a1 );
    std::cout << "rv4_0:\n" << rv4_0 << std::endl;
    std::cout << "rv4_1:\n" << rv4_1 << std::endl;
    std::cout << "rv4_2:\n" << rv4_2 << std::endl;
    std::cout << "rv4_3:\n" << rv4_3 << std::endl;
    std::cout << "rv4_4:\n" << rv4_4 << std::endl;
    std::cout << "rv4_5:\n" << rv4_5 << std::endl;

    for ( size_t w = 0; w < v2.width; ++w )
    {
        for ( size_t h = 0; h < v2.height; ++h )
        {
            for ( size_t d = 0; d < v2.depth; ++d )
            {
                set( v2, 0.0f, w, h, d );
                set( v2, static_cast<float>( w * 1 + h * 10 + d * 1000 ), w, h, d );
                set( v3, 0.0f, w, h, d );
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

    return 0;
}
