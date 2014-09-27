#pragma once

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
#include "Dap_Block.hpp"
#include "Dap_Vec.hpp"
#include "Dap_Math.hpp"

namespace Dap
{

template <typename T>
struct BiQuad
{
    typedef T value_type;
    typedef typename simd_flattened_type<T>::type item_type;
    enum
    {
        vector_size = simd_size<T>::value,
        flattened_size = simd_flattened_size<T>::value
    };

    struct Coeffs
    {
        T a0, a1, a2, b1, b2;

        void set( size_t channel, double na0, double na1, double na2, double nb1, double nb2 )
        {
            set_flattened_item( a0, static_cast<item_type>( na0 ), channel );
            set_flattened_item( a1, static_cast<item_type>( na1 ), channel );
            set_flattened_item( a2, static_cast<item_type>( na2 ), channel );
            set_flattened_item( b1, static_cast<item_type>( nb1 ), channel );
            set_flattened_item( b2, static_cast<item_type>( nb2 ), channel );
        }

        void calculate_lowpass( size_t channel, double sample_rate_recip, double freq, double q )
        {
            double k = std::tan( Constants::pi() * freq * sample_rate_recip );
            double norm = 1.0 / ( 1.0 + k / q + k * k );
            double na0 = k * k * norm;
            double na1 = 2.0 * na0;
            double na2 = na0;
            double nb1 = 2.0 * ( k * k - 1.0 ) * norm;
            double nb2 = ( 1.0 - k / q + k * k ) * norm;

            set( channel, na0, na1, na2, nb1, nb2 );
        }

        void calculate_highpass( size_t channel, double sample_rate_recip, double freq, double q )
        {
            double k = std::tan( Constants::pi() * freq * sample_rate_recip );
            double norm = 1.0 / ( 1.0 + k / q + k * k );
            double na0 = 1.0 * norm;
            double na1 = -2.0 * na0;
            double na2 = na0;
            double nb1 = 2.0 * ( k * k - 1.0 ) * norm;
            double nb2 = ( 1.0 - k / q + k * k ) * norm;
            set( channel, na0, na1, na2, nb1, nb2 );
        }

        void calculate_bandpass( size_t channel, double sample_rate_recip, double freq, double q )
        {
            double k = std::tan( Constants::pi() * freq * sample_rate_recip );
            double norm = 1.0 / ( 1.0 + k / q + k * k );
            double na0 = k / q * norm;
            double na1 = 0.0;
            double na2 = -na0;
            double nb1 = 2.0 * ( k * k - 1.0 ) * norm;
            double nb2 = ( 1.0 - k / q + k * k ) * norm;
            set( channel, na0, na1, na2, nb1, nb2 );
        }

        void calculate_notch( size_t channel, double sample_rate_recip, double freq, double q )
        {
            double k = std::tan( Constants::pi() * freq * sample_rate_recip );
            double norm = 1.0 / ( 1.0 + k / 1.0 + k * k );
            double na0 = ( 1.0 + k * k ) * norm;
            double na1 = 2.0 * ( k * k - 1.0 ) * norm;
            double na2 = na0;
            double nb1 = na1;
            double nb2 = ( 1.0 - k / q + k * k ) * norm;
            set( channel, na0, na1, na2, nb1, nb2 );
        }

        void calculate_peak( size_t channel, double sample_rate_recip, double freq, double q, double gain )
        {
            double k = std::tan( Constants::pi() * freq * sample_rate_recip );
            double v = pow( 10.0, std::abs( gain ) / 20.0 );

            if ( gain >= 0 )
            {
                double norm = 1.0 / ( 1.0 + 1.0 / q * k + k * k );
                double na0 = ( 1.0 + v / q * k + k * k ) * norm;
                double na1 = 2.0 * ( k * k - 1.0 ) * norm;
                double na2 = ( 1.0 - v / q * k + k * k ) * norm;
                double nb1 = na1;
                double nb2 = ( 1.0 - 1.0 / q * k + k * k ) * norm;

                set( channel, na0, na1, na2, nb1, nb2 );
            }
            else
            {
                double norm = 1.0 / ( 1.0 + v / q * k + k * k );
                double na0 = ( 1.0 + 1.0 / q * k + k * k ) * norm;
                double na1 = 2.0 * ( k * k - 1.0 ) * norm;
                double na2 = ( 1.0 - 1.0 / q * k + k * k ) * norm;
                double nb1 = na1;
                double nb2 = ( 1.0 - v / q * k + k * k ) * norm;

                set( channel, na0, na1, na2, nb1, nb2 );
            }
        }

        void calculate_lowshelf( size_t channel, double sample_rate_recip, double freq, double gain )
        {
            double k = std::tan( Constants::pi() * freq * sample_rate_recip );
            double v = pow( 10.0, std::abs( gain ) / 20.0 );
            double sqrt2 = Constants::sqrt_2<double>();

            if ( gain >= 0 )
            {
                double norm = 1.0 / ( 1.0 + sqrt2 * k + k * k );
                double na0 = ( 1.0 + sqrt2 * v * k + v * k * k ) * norm;
                double na1 = 2.0 * ( v * k * k - 1.0 ) * norm;
                double na2 = ( 1.0 - sqrt2 * v * k + v * k * k ) * norm;
                double nb1 = 2.0 * ( k * k - 1.0 ) * norm;
                double nb2 = ( 1.0 - sqrt2 * k + k * k ) * norm;

                set( channel, na0, na1, na2, nb1, nb2 );
            }
            else
            {
                double norm = 1.0 / ( 1.0 + sqrt2 * v * k + v * k * k );
                double na0 = ( 1.0 + sqrt2 * k + k * k ) * norm;
                double na1 = 2.0 * ( k * k - 1.0 ) * norm;
                double na2 = ( 1.0 - sqrt2 * k + k * k ) * norm;
                double nb1 = 2.0 * ( v * k * k - 1.0 ) * norm;
                double nb2 = ( 1.0 - sqrt2 * v * k + v * k * k ) * norm;
                set( channel, na0, na1, na2, nb1, nb2 );
            }
        }

        void calculate_highshelf( size_t channel, double sample_rate_recip, double freq, double gain )
        {
            double k = std::tan( Constants::pi() * freq * sample_rate_recip );
            double v = pow( 10.0, std::abs( gain ) / 20.0 );
            double sqrt2 = Constants::sqrt_2();

            if ( gain >= 0 )
            {
                double norm = 1.0 / ( 1.0 + sqrt2 * k + k * k );
                double na0 = ( v + sqrt2 * v * k + k * k ) * norm;
                double na1 = 2.0 * ( k * k - v ) * norm;
                double na2 = ( v - sqrt2 * v * k + k * k ) * norm;
                double nb1 = 2.0 * ( k * k - 1 ) * norm;
                double nb2 = ( 1.0 - sqrt2 * k + k * k ) * norm;
                set( channel, na0, na1, na2, nb1, nb2 );
            }
            else
            {
                double norm = 1.0 / ( v + sqrt2 * v * k + k * k );
                double na0 = ( 1.0 + sqrt2 * k + k * k ) * norm;
                double na1 = 2.0 * ( k * k - 1 ) * norm;
                double na2 = ( 1.0 - sqrt2 * k + k * k ) * norm;
                double nb1 = 2.0 * ( k * k - v ) * norm;
                double nb2 = ( v - sqrt2 * v * k + k * k ) * norm;
                set( channel, na0, na1, na2, nb1, nb2 );
            }
        }

        friend std::ostream &operator<<( std::ostream &o, Coeffs const &v )
        {
            o << "{ "
              << "a0=" << v.a0 << " a1=" << v.a1 << " a2=" << v.a2 << " b1=" << v.b1 << " b2=" << v.b2 << " }";
            return o;
        }
    };

    struct State
    {

        T z1, z2;

        State()
        {
            zero( z1 );
            zero( z2 );
        }

        State( State const &other ) = default;

        State &operator=( State const &other ) = default;

        friend std::ostream &operator<<( std::ostream &o, State const &v )
        {
            o << "{ "
              << "z1=" << v.z1 << " z2=" << v.z2 << " }";
            return o;
        }
    };

    Coeffs coeffs;
    State state;

    BiQuad() : coeffs(), state()
    {
    }

    BiQuad( BiQuad const &other ) : coeffs( other.coeffs ), state( other.state )
    {
    }

    BiQuad &operator=( BiQuad const &other )
    {
        coeffs = other.coeffs;
        state = other.state;
    }

    T operator()( T const &input_value )
    {
        T output_value;

        output_value = ( input_value * coeffs.a0 ) + state.z1;
        state.z1 = ( input_value * coeffs.a1 ) + state.z2 - ( coeffs.b1 * output_value );
        state.z2 = ( input_value * coeffs.a2 ) - ( coeffs.b2 * output_value );

        return output_value;
    }

    friend std::ostream &operator<<( std::ostream &o, BiQuad const &v )
    {
        o << "coeffs: " << v.coeffs << std::endl;
        o << "state : " << v.state << std::endl;
        return o;
    }
};
}
