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

#include "Dap_SIMD_Vector.hpp"

#if defined( __SSE__ )
#include "xmmintrin.h"

namespace Dap
{

template <>
class DAP_SIMD_ALIGN SIMD_Vector<float, 4>
{
  public:
    typedef SIMD_Vector<float, 4> simd_type;
    typedef __m128 internal_type;
    typedef float value_type;

    typedef value_type *pointer;
    typedef value_type const *const_pointer;
    typedef value_type &reference;
    typedef value_type const &const_reference;
    typedef pointer iterator;
    typedef const_pointer const_iterator;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

    static const size_type vector_size = 4;

    union
    {
        internal_type m_vec;
        value_type m_item[vector_size];
    };

    /// Default constructor does not initialize any values
    SIMD_Vector()
    {
    }

    /// The Initializer list constructor sets the values
    SIMD_Vector( value_type p1, value_type p2, value_type p3, value_type p4 )
    {
        m_item[0] = p1;
        m_item[1] = p2;
        m_item[2] = p3;
        m_item[3] = p4;
    }

    /// Get the vector size
    size_type size() const
    {
        return vector_size;
    }

    /// Get the vector maximum size
    size_type max_size() const
    {
        return vector_size;
    }

    /// Is it empty
    bool empty() const
    {
        return false;
    }

    /// Fill with a specific value
    void fill( value_type const &a )
    {
        for ( size_type i = 0; i < size(); ++i )
        {
            m_item[i] = a;
        }
    }

    /// Swap values in container with the other
    void swap( simd_type &other ) noexcept
    {
        internal_type t = m_vec;
        m_vec = other.m_vec;
        other.m_vec = t;
    }

    /// Get underlying array
    pointer data()
    {
        return m_item;
    }

    /// Get underlying array const
    const_pointer data() const
    {
        return m_item;
    }

    /// array index operator returns a const ref to the item
    value_type const &operator[]( size_t index ) const
    {
        return m_item[index];
    }

    /// at() returns a non-const ref to the item, with range checking
    value_type &at( size_t index )
    {
        if ( index > size() )
        {
            throw std::out_of_range( "SIMD_Vector" );
        }
        return m_item[index];
    }

    /// at() returns a const ref to the item, with range checking
    value_type const &at( size_t index ) const
    {
        if ( index > size() )
        {
            throw std::out_of_range( "SIMD_Vector" );
        }
        return m_item[index];
    }

    /// array index operator returns a non-const ref to the item
    value_type &operator[]( size_t index )
    {
        return m_item[index];
    }

    /// Copy constructor
    SIMD_Vector( simd_type const &other )
    {
        for ( size_t i = 0; i < vector_size; ++i )
        {
            m_item[i] = other.m_item[i];
        }
    }

    /// Assignment operator
    simd_type const &operator=( simd_type const &other )
    {
        for ( size_t i = 0; i < vector_size; ++i )
        {
            m_item[i] = other.m_item[i];
        }
        return *this;
    }

    /// Get the first item
    reference front()
    {
        return m_item[0];
    }

    /// Get the first item (const)
    const_reference front() const
    {
        return m_item[0];
    }

    /// Get the last item
    reference back()
    {
        return m_item[vector_size - 1];
    }

    /// Get the last item (const)
    const_reference back() const
    {
        return m_item[vector_size - 1];
    }

    /// Get the iterator for the beginning
    iterator begin()
    {
        return &m_item[0];
    }

    /// Get the const_iterator for the beginning
    const_iterator begin() const
    {
        return &m_item[0];
    }

    /// Get the const_iterator for the beginning
    const_iterator cbegin() const
    {
        return &m_item[0];
    }

    /// Get the iterator for the end (one item past the last item)
    iterator end()
    {
        return &m_item[vector_size];
    }

    /// Get the const_iterator for the end (one item past the last item)
    const_iterator end() const
    {
        return &m_item[vector_size];
    }

    /// Get the const_iterator for the end (one item past the last item)
    const_iterator cend() const
    {
        return &m_item[vector_size];
    }

    /// Output the vector to the ostream
    template <typename CharT, typename TraitsT>
    friend std::basic_ostream<CharT, TraitsT> &operator<<( std::basic_ostream<CharT, TraitsT> &str, simd_type const &a )
    {
        str << "{ ";
        for ( auto i = std::begin( a ); i != std::end( a ); ++i )
        {
            str << *i << " ";
        }
        str << " }";
        return str;
    }

    friend simd_type splat( simd_type &v, value_type a )
    {
        v.m_vec = _mm_set1_ps( a );
        return v;
    }

    friend simd_type zero( simd_type &v )
    {
        v.m_vec = _mm_setzero_ps();
        return v;
    }

    friend simd_type one( simd_type &v )
    {
        v.m_vec = _mm_set1_ps( 1.0f );
        return v;
    }

    friend simd_type sqrt( simd_type const &a )
    {
        return reciprocal( reciprocal_sqrt( a ) );
    }

    friend simd_type arg( simd_type const &a )
    {
        simd_type r;
        for ( size_t i = 0; i < vector_size; ++i )
        {
            r[i] = arg( a[i] );
        }
        return r;
    }

    friend simd_type abs( simd_type const &a )
    {
        simd_type r;
        r.m_vec = _mm_andnot_ps( _mm_set1_ps( -0.0f ), a.m_vec );
        return r;
    }

    friend simd_type sin( simd_type const &a )
    {
        simd_type r;
        for ( size_t i = 0; i < vector_size; ++i )
        {
            r[i] = sin( a[i] );
        }
        return r;
    }

    friend simd_type cos( simd_type const &a )
    {
        simd_type r;
        for ( size_t i = 0; i < vector_size; ++i )
        {
            r[i] = cos( a[i] );
        }
        return r;
    }

    friend simd_type reciprocal( simd_type const &a )
    {
        simd_type r;
        r.m_vec = _mm_rcp_ps( a.m_vec );
        // (b+b) - a*b*b
        r.m_vec = _mm_sub_ps( _mm_add_ps( r.m_vec, r.m_vec ), _mm_mul_ps( _mm_mul_ps( a.m_vec, r.m_vec ), r.m_vec ) );
        r.m_vec = _mm_sub_ps( _mm_add_ps( r.m_vec, r.m_vec ), _mm_mul_ps( _mm_mul_ps( a.m_vec, r.m_vec ), r.m_vec ) );
        return r;
    }

    friend simd_type reciprocal_sqrt( simd_type const &a )
    {
        internal_type v0_5;
        v0_5 = _mm_set1_ps( 0.5f );

        internal_type v3_0;
        v3_0 = _mm_set1_ps( 3.0f );

        simd_type r;
        r.m_vec = _mm_rsqrt_ps( a.m_vec );

        //   b*b*b*a*-0.5f + b*1.5f
        // = 0.5f*b*(3.0f - a*b*b)

        r.m_vec = _mm_mul_ps( _mm_mul_ps( v0_5, r.m_vec ),
                              _mm_sub_ps( v3_0, _mm_mul_ps( _mm_mul_ps( a.m_vec, r.m_vec ), r.m_vec ) ) );
        r.m_vec = _mm_mul_ps( _mm_mul_ps( v0_5, r.m_vec ),
                              _mm_sub_ps( v3_0, _mm_mul_ps( _mm_mul_ps( a.m_vec, r.m_vec ), r.m_vec ) ) );
        return r;
    }

    friend simd_type operator-( simd_type const &a )
    {
        simd_type r;
        r.m_vec = _mm_xor_ps( _mm_set1_ps( -0.0f ), a.m_vec );
        return r;
    }

    friend simd_type operator+( simd_type const &a )
    {
        simd_type r;
        for ( size_t i = 0; i < vector_size; ++i )
        {
            r[i] = +a[i];
        }
        return r;
    }

    friend simd_type operator+=( simd_type &a, value_type const &b )
    {
        internal_type t = _mm_set1_ps( b );
        a.m_vec = _mm_add_ps( a.m_vec, t );
        return a;
    }

    friend simd_type operator-=( simd_type &a, value_type const &b )
    {
        internal_type t = _mm_set1_ps( b );
        a.m_vec = _mm_sub_ps( a.m_vec, t );
        return a;
    }

    friend simd_type operator*=( simd_type &a, value_type const &b )
    {
        internal_type t = _mm_set1_ps( b );
        a.m_vec = _mm_mul_ps( a.m_vec, t );
        return a;
    }

    friend simd_type operator/=( simd_type &a, value_type const &b )
    {
        internal_type t = _mm_set1_ps( b );
        a.m_vec = _mm_div_ps( a.m_vec, t );
        return a;
    }

    friend simd_type operator+( simd_type const &a, value_type const &b )
    {
        internal_type t = _mm_set1_ps( b );
        simd_type r;
        r.m_vec = _mm_add_ps( a.m_vec, t );
        return r;
    }

    friend simd_type operator-( simd_type const &a, value_type const &b )
    {
        internal_type t = _mm_set1_ps( b );
        simd_type r;
        r.m_vec = _mm_sub_ps( a.m_vec, t );
        return r;
    }

    friend simd_type operator*( simd_type const &a, value_type const &b )
    {
        internal_type t = _mm_set1_ps( b );
        simd_type r;
        r.m_vec = _mm_mul_ps( a.m_vec, t );
        return r;
    }

    friend simd_type operator/( simd_type const &a, value_type const &b )
    {
        internal_type t = _mm_set1_ps( b );
        simd_type r;
        r.m_vec = _mm_div_ps( a.m_vec, t );
        return r;
    }

    friend simd_type operator+=( simd_type &a, simd_type const &b )
    {
        a.m_vec = _mm_add_ps( a.m_vec, b.m_vec );
        return a;
    }

    friend simd_type operator-=( simd_type &a, simd_type const &b )
    {
        a.m_vec = _mm_sub_ps( a.m_vec, b.m_vec );
        return a;
    }

    friend simd_type operator*=( simd_type &a, simd_type const &b )
    {
        a.m_vec = _mm_mul_ps( a.m_vec, b.m_vec );
        return a;
    }

    friend simd_type operator/=( simd_type &a, simd_type const &b )
    {
        a.m_vec = _mm_div_ps( a.m_vec, b.m_vec );
        return a;
    }

    friend simd_type operator+( simd_type const &a, simd_type const &b )
    {
        simd_type r;
        r.m_vec = _mm_add_ps( a.m_vec, b.m_vec );
        return r;
    }

    friend simd_type operator-( simd_type const &a, simd_type const &b )
    {
        simd_type r;
        r.m_vec = _mm_sub_ps( a.m_vec, b.m_vec );
        return r;
    }

    friend simd_type operator*( simd_type const &a, simd_type const &b )
    {
        simd_type r;
        r.m_vec = _mm_mul_ps( a.m_vec, b.m_vec );
        return r;
    }

    friend simd_type operator/( simd_type const &a, simd_type const &b )
    {
        simd_type r;
        r.m_vec = _mm_div_ps( a.m_vec, b.m_vec );
        return r;
    }

    friend simd_type equal_to( simd_type const &a, simd_type const &b )
    {
        simd_type r;
        internal_type t = _mm_set1_ps( 1.0f );
        internal_type f = _mm_setzero_ps();

        internal_type x = _mm_cmpeq_ps( a.m_vec, b.m_vec );
        r.m_vec = _mm_or_ps( _mm_and_ps( x, t ), _mm_andnot_ps( x, f ) );
        return r;
    }

    friend simd_type not_equal_to( simd_type const &a, simd_type const &b )
    {
        simd_type r;
        internal_type t = _mm_set1_ps( 1.0f );
        internal_type f = _mm_setzero_ps();

        internal_type x = _mm_cmpneq_ps( a.m_vec, b.m_vec );
        r.m_vec = _mm_or_ps( _mm_and_ps( x, t ), _mm_andnot_ps( x, f ) );
        return r;
    }

    friend simd_type less( simd_type const &a, simd_type const &b )
    {
        simd_type r;
        internal_type t = _mm_set1_ps( 1.0f );
        internal_type f = _mm_setzero_ps();

        internal_type x = _mm_cmpnlt_ps( a.m_vec, b.m_vec );
        r.m_vec = _mm_or_ps( _mm_and_ps( x, t ), _mm_andnot_ps( x, f ) );
        return r;
    }

    friend simd_type less_equal( simd_type const &a, simd_type const &b )
    {
        simd_type r;
        internal_type t = _mm_set1_ps( 1.0f );
        internal_type f = _mm_setzero_ps();

        internal_type x = _mm_cmpnle_ps( a.m_vec, b.m_vec );
        r.m_vec = _mm_or_ps( _mm_and_ps( x, t ), _mm_andnot_ps( x, f ) );
        return r;
    }

    friend simd_type greater( simd_type const &a, simd_type const &b )
    {
        simd_type r;
        internal_type t = _mm_set1_ps( 1.0f );
        internal_type f = _mm_setzero_ps();

        internal_type x = _mm_cmpngt_ps( a.m_vec, b.m_vec );
        r.m_vec = _mm_or_ps( _mm_and_ps( x, t ), _mm_andnot_ps( x, f ) );
        return r;
    }

    friend simd_type greater_equal( simd_type const &a, simd_type const &b )
    {
        simd_type r;
        internal_type t = _mm_set1_ps( 1.0f );
        internal_type f = _mm_setzero_ps();

        internal_type x = _mm_cmpnge_ps( a.m_vec, b.m_vec );
        r.m_vec = _mm_or_ps( _mm_and_ps( x, t ), _mm_andnot_ps( x, f ) );
        return r;
    }
};
}
#endif
