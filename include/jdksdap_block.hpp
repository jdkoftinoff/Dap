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

#include "jdksdap_world.hpp"
#include "jdksdap_vec.hpp"
#include "jdksdap_traits.hpp"

namespace jdksdap
{

/**
 * 3 dimensional array block indexed by Width, Height, and Depth
 */
template <typename T, std::size_t Width, std::size_t Height = 1, std::size_t Depth = 1>
struct block
{
    using array = std::array<std::array<std::array<T, Width>, Height>, Depth>;
    array content;
    static const size_t width = Width;
    static const size_t height = Height;
    static const size_t depth = Depth;
    static const size_t first_size = Depth;
    static const size_t second_size = Height;
    static const size_t third_size = Width;
};

/**
 * 1 dimensional array block indexed by Width
 */
template <typename T, std::size_t Width>
struct block<T, Width, 1, 1>
{
    using array = std::array<T, Width>;
    array content;

    static const size_t width = Width;
    static const size_t height = 1;
    static const size_t depth = 1;
    static const size_t first_size = 1;
    static const size_t second_size = 1;
    static const size_t third_size = Width;
};

/**
 * 2 dimensional array block indexed by Width and Height
 */
template <typename T, std::size_t Width, std::size_t Height>
struct block<T, Width, Height, 1>
{
    using array = std::array<std::array<T, Width>, Height>;
    array content;

    static const size_t width = Width;
    static const size_t height = Height;
    static const size_t depth = 1;
    static const size_t first_size = Height;
    static const size_t second_size = Width;
    static const size_t third_size = 1;
};

/**
 * 3 dimensional array block indexed by Height, Width, and Depth
 */
template <typename T, std::size_t Width, std::size_t Height = 1, std::size_t Depth = 1>
struct rotated_width_block
{
    using array = std::array<std::array<std::array<T, Height>, Width>, Depth>;
    array content;

    using value_type = T;
    static const size_t width = Width;
    static const size_t height = Height;
    static const size_t depth = Depth;
    static const size_t first_size = Depth;
    static const size_t second_size = Width;
    static const size_t third_size = Height;
};

/**
 * 1 dimensional array block indexed by Width
 */
template <typename T, std::size_t Width>
struct rotated_width_block<T, Width, 1, 1>
{
    using array = std::array<T, Width>;
    array content;

    using value_type = T;
    static const size_t width = Width;
    static const size_t height = 1;
    static const size_t depth = 1;
    static const size_t first_size = Width;
    static const size_t second_size = 1;
    static const size_t third_size = 1;
};

/**
 * 2 dimensional rotated array block indexed by Height and Width
 */
template <typename T, std::size_t Width, std::size_t Height>
struct rotated_width_block<T, Width, Height, 1>
{
    using array = std::array<std::array<T, Height>, Width>;
    array content;

    using value_type = T;
    static const size_t width = Width;
    static const size_t height = Height;
    static const size_t depth = 1;
    static const size_t first_size = Width;
    static const size_t second_size = Height;
    static const size_t third_size = 1;
};

/**
 * Traits for unrotated array block
 */
template <typename T, size_t Width, size_t Height, size_t Depth>
struct traits<block<T, Width, Height, Depth> >
{
    using container_type = block<T, Width, Height, Depth>;
    using value_type = T;
    using rotate_width_type = rotated_width_block<T, Width, Height, Depth>;

    using is_unrotated_container_type = container_type;
    using is_unrotated_value_type = value_type;

    using is_3dim_container_type = container_type;
    using is_3dim_value_type = value_type;

    static const size_t width = Width;
    static const size_t height = Height;
    static const size_t depth = Depth;

    static const size_t first_size = Depth;
    static const size_t second_size = Height;
    static const size_t third_size = Width;
};

template <typename T, size_t Width>
struct traits<block<T, Width, 1, 1> >
{
    using container_type = block<T, Width, 1, 1>;
    using value_type = T;
    using rotate_width_type = rotated_width_block<T, Width, 1, 1>;

    using is_unrotated_container_type = container_type;
    using is_unrotated_value_type = value_type;

    using is_1dim_container_type = container_type;
    using is_1dim_value_type = value_type;

    static const size_t width = Width;
    static const size_t height = 1;
    static const size_t depth = 1;

    static const size_t first_size = Width;
    static const size_t second_size = 1;
    static const size_t third_size = 1;
};

template <typename T, size_t Width, size_t Height>
struct traits<block<T, Width, Height, 1> >
{
    using container_type = block<T, Width, Height, 1>;
    using value_type = T;
    using rotate_width_type = rotated_width_block<T, Width, Height, 1>;

    using is_unrotated_container_type = container_type;
    using is_unrotated_value_type = value_type;

    using is_2dim_container_type = container_type;
    using is_2dim_value_type = value_type;

    static const size_t width = Width;
    static const size_t height = Height;
    static const size_t depth = 1;

    static const size_t first_size = Height;
    static const size_t second_size = Width;
    static const size_t third_size = 1;
};

/**
 * Traits for rotated array block
 */
template <typename T, size_t Width, size_t Height, size_t Depth>
struct traits<rotated_width_block<T, Width, Height, Depth> >
{
    using container_type = rotated_width_block<T, Width, Height, Depth>;
    using rotate_width_type = block<T, Width, Height, Depth>;
    using value_type = T;

    using is_rotated_width_container_type = container_type;
    using is_rotated_width_value_type = value_type;

    using is_3dim_container_type = container_type;
    using is_3dim_value_type = value_type;

    static const size_t width = Width;
    static const size_t height = Height;
    static const size_t depth = Depth;

    static const size_t first_size = Depth;
    static const size_t second_size = Width;
    static const size_t third_size = Height;
};

template <typename T, size_t Width>
struct traits<rotated_width_block<T, Width, 1, 1> >
{
    using container_type = rotated_width_block<T, Width, 1, 1>;
    using rotate_width_type = block<T, Width, 1, 1>;
    using value_type = T;

    using is_rotated_width_container_type = container_type;
    using is_rotated_width_value_type = value_type;

    using is_1dim_container_type = container_type;
    using is_1dim_value_type = value_type;

    static const size_t width = Width;
    static const size_t height = 1;
    static const size_t depth = 1;

    static const size_t first_size = Width;
    static const size_t second_size = 1;
    static const size_t third_size = 1;
};

template <typename T, size_t Width, size_t Height>
struct traits<rotated_width_block<T, Width, Height, 1> >
{
    using container_type = rotated_width_block<T, Width, Height, 1>;
    using rotate_width_type = block<T, Width, Height, 1>;
    using value_type = T;

    using is_rotated_width_container_type = container_type;
    using is_rotated_width_value_type = value_type;

    using is_2dim_container_type = container_type;
    using is_2dim_value_type = value_type;

    static const size_t width = Width;
    static const size_t height = Height;
    static const size_t depth = 1;

    static const size_t first_size = Width;
    static const size_t second_size = Height;
    static const size_t third_size = 1;
};

template <typename ContainerT>
auto rawget( ContainerT &c,
             std::size_t i1 = 0,
             std::size_t = 0,
             std::size_t = 0,
             typename traits<ContainerT>::is_1dim_container_type * = 0 ) -> typename traits<ContainerT>::value_type &
{
    return c.content[i1];
}

template <typename ContainerT>
auto rawget( ContainerT &c,
             std::size_t i1 = 0,
             std::size_t i2 = 0,
             std::size_t = 0,
             typename traits<ContainerT>::is_2dim_container_type * = 0 ) -> typename traits<ContainerT>::value_type &
{
    return c.content[i1][i2];
}

template <typename ContainerT>
auto rawget( ContainerT &c,
             std::size_t i1 = 0,
             std::size_t i2 = 0,
             std::size_t i3 = 0,
             typename traits<ContainerT>::is_3dim_container_type * = 0 ) -> typename traits<ContainerT>::value_type &
{
    return c.content[i1][i2][i3];
}

template <typename ContainerT>
auto rawget( ContainerT const &c,
             std::size_t i1 = 0,
             std::size_t = 0,
             std::size_t = 0,
             typename traits<ContainerT>::is_1dim_container_type * = 0 ) -> typename traits<ContainerT>::value_type
{
    return c.content[i1];
}

template <typename ContainerT>
auto rawget( ContainerT const &c,
             std::size_t i1 = 0,
             std::size_t i2 = 0,
             std::size_t = 0,
             typename traits<ContainerT>::is_2dim_container_type * = 0 ) -> typename traits<ContainerT>::value_type
{
    return c.content[i1][i2];
}

template <typename ContainerT>
auto rawget( ContainerT const &c,
             std::size_t i1 = 0,
             std::size_t i2 = 0,
             std::size_t i3 = 0,
             typename traits<ContainerT>::is_3dim_container_type * = 0 ) -> typename traits<ContainerT>::value_type
{
    return c.content[i1][i2][i3];
}

template <typename ContainerT>
auto rawset( typename traits<ContainerT>::is_1dim_value_type v,
             ContainerT &c,
             std::size_t i1 = 0,
             std::size_t = 0,
             std::size_t = 0 ) -> void
{
    c.content[i1] = v;
}

template <typename ContainerT>
auto rawset( typename traits<ContainerT>::is_2dim_value_type v,
             ContainerT &c,
             std::size_t i1 = 0,
             std::size_t i2 = 0,
             std::size_t = 0 ) -> void
{
    c.content[i1][i2] = v;
}

template <typename ContainerT>
auto rawset( typename traits<ContainerT>::is_3dim_value_type v,
             ContainerT &c,
             std::size_t i1 = 0,
             std::size_t i2 = 0,
             std::size_t i3 = 0 ) -> void
{
    c.content[i1][i2][i3] = v;
}

template <typename ContainerT>
auto get( ContainerT const &c,
          std::size_t w = 0,
          std::size_t = 0,
          std::size_t = 0,
          typename traits<ContainerT>::is_1dim_container_type * = 0 ) -> typename traits<ContainerT>::is_unrotated_value_type
{
    return c.content[w];
}

template <typename ContainerT>
auto get( ContainerT const &c,
          std::size_t w = 0,
          std::size_t h = 0,
          std::size_t = 0,
          typename traits<ContainerT>::is_2dim_container_type * = 0 ) -> typename traits<ContainerT>::is_unrotated_value_type
{
    return c.content[h][w];
}

template <typename ContainerT>
auto get( ContainerT const &c,
          std::size_t w = 0,
          std::size_t h = 0,
          std::size_t d = 0,
          typename traits<ContainerT>::is_3dim_container_type * = 0 ) -> typename traits<ContainerT>::is_unrotated_value_type
{
    return c.content[d][h][w];
}

template <typename ContainerT>
auto get( ContainerT const &c,
          std::size_t w = 0,
          std::size_t = 0,
          std::size_t = 0,
          typename traits<ContainerT>::is_1dim_container_type * = 0 ) -> typename traits
    <ContainerT>::is_rotated_width_value_type
{
    return c.content[w];
}

template <typename ContainerT>
auto get( ContainerT const &c,
          std::size_t w = 0,
          std::size_t h = 0,
          std::size_t = 0,
          typename traits<ContainerT>::is_2dim_container_type * = 0 ) -> typename traits
    <ContainerT>::is_rotated_width_value_type
{
    return c.content[w][h];
}

template <typename ContainerT>
auto get( ContainerT const &c,
          std::size_t w = 0,
          std::size_t h = 0,
          std::size_t d = 0,
          typename traits<ContainerT>::is_3dim_container_type * = 0 ) -> typename traits
    <ContainerT>::is_rotated_width_value_type
{
    return c.content[d][w][h];
}

template <typename ContainerT>
auto set( typename traits<ContainerT>::is_1dim_value_type v,
          ContainerT &c,
          std::size_t w = 0,
          std::size_t = 0,
          std::size_t = 0,
          typename traits<ContainerT>::is_unrotated_value_type * = 0 ) -> void
{
    c.content[w] = v;
}

template <typename ContainerT>
auto set( typename traits<ContainerT>::is_2dim_value_type v,
          ContainerT &c,
          std::size_t w = 0,
          std::size_t h = 0,
          std::size_t = 0,
          typename traits<ContainerT>::is_unrotated_value_type * = 0 ) -> void
{
    c.content[h][w] = v;
}

template <typename ContainerT>
auto set( typename traits<ContainerT>::is_3dim_value_type v,
          ContainerT &c,
          std::size_t w = 0,
          std::size_t h = 0,
          std::size_t d = 0,
          typename traits<ContainerT>::is_unrotated_value_type * = 0 ) -> void
{
    c.content[d][h][w] = v;
}

template <typename ContainerT>
auto set( typename traits<ContainerT>::is_1dim_value_type v,
          ContainerT &c,
          std::size_t w = 0,
          std::size_t = 0,
          std::size_t = 0,
          typename traits<ContainerT>::is_rotated_width_value_type * = 0 ) -> void
{
    c.content[w] = v;
}

template <typename ContainerT>
auto set( typename traits<ContainerT>::is_2dim_value_type v,
          ContainerT &c,
          std::size_t w = 0,
          std::size_t h = 0,
          std::size_t = 0,
          typename traits<ContainerT>::is_rotated_width_value_type * = 0 ) -> void
{
    c.content[w][h] = v;
}

template <typename ContainerT>
auto set( typename traits<ContainerT>::is_3dim_value_type v,
          ContainerT &c,
          std::size_t w = 0,
          std::size_t h = 0,
          std::size_t d = 0,
          typename traits<ContainerT>::is_rotated_width_value_type * = 0 ) -> void
{
    c.content[d][w][h] = v;
}

template <typename ContainerT, typename Functor>
void apply( ContainerT &srcdest, Functor f, typename traits<ContainerT>::is_1dim_value_type * = 0 )
{
    using ContainerTraits = traits<ContainerT>;
    using ValueType = typename ContainerTraits::value_type;

    for ( std::size_t a = 0; a < ContainerTraits::first_size; ++a )
    {
        ValueType &v = rawget( srcdest, a );
        v = f( v );
    }
}

template <typename ContainerT, typename Functor>
void apply( ContainerT &srcdest, Functor f, typename traits<ContainerT>::is_2dim_value_type * = 0 )
{
    using ContainerTraits = traits<ContainerT>;
    using ValueType = typename ContainerTraits::value_type;

    for ( std::size_t a = 0; a < ContainerTraits::first_size; ++a )
    {
        for ( std::size_t b = 0; b < ContainerTraits::second_size; ++b )
        {
            ValueType &v = rawget( srcdest, a, b );
            v = f( v );
        }
    }
}

template <typename ContainerT, typename Functor>
void apply( ContainerT &srcdest, Functor f, typename traits<ContainerT>::is_3dim_value_type * = 0 )
{
    using ContainerTraits = traits<ContainerT>;
    using ValueType = typename ContainerTraits::value_type;

    for ( std::size_t a = 0; a < ContainerTraits::first_size; ++a )
    {
        for ( std::size_t b = 0; b < ContainerTraits::second_size; ++b )
        {
            for ( std::size_t c = 0; c < ContainerTraits::third_size; ++c )
            {
                ValueType &v = rawget( srcdest, a, b, c );
                v = f( v );
            }
        }
    }
}

template <typename SourceContainerT, typename DestinationContainerT, typename Functor>
auto apply( SourceContainerT const &src,
            DestinationContainerT &dest,
            Functor f,
            typename traits<SourceContainerT>::value_type * = 0,
            typename traits<DestinationContainerT>::value_type * = 0 ) -> void
{
    using SourceContainerTraits = traits<SourceContainerT>;
    using DestinationContainerTraits = traits<DestinationContainerT>;
    using SourceValueType = typename SourceContainerTraits::value_type;
    using DestinationValueType = typename DestinationContainerTraits::value_type;

    static_assert( SourceContainerTraits::width == DestinationContainerTraits::width,
                   "Width different between Source and Destination" );
    static_assert( SourceContainerTraits::height == DestinationContainerTraits::height,
                   "Height different between Source and Destination" );
    static_assert( SourceContainerTraits::depth == DestinationContainerTraits::depth,
                   "Depth different between Source and Destination" );

    for ( std::size_t w = 0; w < DestinationContainerTraits::width; ++w )
    {
        for ( std::size_t h = 0; h < DestinationContainerTraits::height; ++h )
        {
            for ( std::size_t d = 0; d < DestinationContainerTraits::depth; ++d )
            {
                set( f( get( src, w, h, d ) ), dest, w, h, d );
            }
        }
    }
}

template <typename Container1T, typename Container2T, typename ResultContainerT, typename Functor>
auto apply( Container1T const &c1,
            Container2T const &c2,
            ResultContainerT &r,
            Functor f,
            typename traits<Container1T>::rotate_width_type * = 0,
            typename traits<Container2T>::rotate_width_type * = 0,
            typename traits<ResultContainerT>::rotate_width_type * = 0 ) -> void
{
    using Container1Traits = traits<Container1T>;
    using Container2Traits = traits<Container2T>;
    using ResultContainerTraits = traits<ResultContainerT>;
    using ValueType1 = typename Container1Traits::value_type;
    using ValueType2 = typename Container2Traits::value_type;
    using ValueTypeResult = typename ResultContainerTraits::value_type;

    static_assert( Container1Traits::width == Container2Traits::width, "Width different between Source and Destination" );
    static_assert( Container1Traits::height == Container2Traits::height, "Height different between Source and Destination" );
    static_assert( Container1Traits::depth == Container2Traits::depth, "Depth different between Source and Destination" );

    for ( std::size_t w = 0; w < ResultContainerTraits::width; ++w )
    {
        for ( std::size_t h = 0; h < ResultContainerTraits::height; ++h )
        {
            for ( std::size_t d = 0; d < ResultContainerTraits::depth; ++d )
            {
                set( f( get( c1, w, h, d ), get( c2, w, h, d ) ), r, w, h, d );
            }
        }
    }
}

template <typename OriginalContainerT>
auto rotate( OriginalContainerT const &b ) -> typename traits<OriginalContainerT>::rotate_width_type
{
    using OriginalContainerTraits = traits<OriginalContainerT>;
    using ValueType = typename OriginalContainerTraits::value_type;
    using ResultContainer = typename traits<OriginalContainerT>::rotate_width_type;

    ResultContainer result;

    apply( b,
           result,
           []( ValueType v )
    { return v; } );

    return result;
}

template <std::size_t Width, std::size_t Height, std::size_t Depth, typename T>
auto make_block( T elem ) -> block<T, Width, Height, Depth>
{
    using Container = block<T, Width, Height, Depth>;
    Container r;

    for ( std::size_t a = 0; a < Container::first_size; ++a )
    {
        for ( std::size_t b = 0; b < Container::second_size; ++b )
        {
            for ( std::size_t c = 0; c < Container::third_size; ++c )
            {
                rawset( elem, r, a, b, c );
            }
        }
    }

    return r;
}

template <typename T, std::size_t Width, std::size_t Height, std::size_t Depth, typename Functor>
auto fill_block( Functor f ) -> block<T, Width, Height, Depth>
{
    using Container = block<T, Width, Height, Depth>;
    Container r;

    for ( std::size_t w = 0; w < Container::width; ++w )
    {
        for ( std::size_t h = 0; h < Container::height; ++h )
        {
            for ( std::size_t d = 0; d < Container::depth; ++d )
            {
                set( f( w, h, d ), r, w, h, d );
            }
        }
    }

    return r;
}

template <std::size_t Width, std::size_t Height, std::size_t Depth, typename T>
auto make_rotated_width_block( T elem ) -> rotated_width_block<T, Width, Height, Depth>
{
    using Container = rotated_width_block<T, Width, Height, Depth>;
    Container r;

    for ( std::size_t a = 0; a < Container::first_size; ++a )
    {
        for ( std::size_t b = 0; b < Container::second_size; ++b )
        {
            for ( std::size_t c = 0; c < Container::third_size; ++c )
            {
                rawset( elem, r, a, b, c );
            }
        }
    }

    return r;
}

template <typename T, std::size_t Width, std::size_t Height, std::size_t Depth, typename Functor>
auto fill_rotated_width_block( Functor f ) -> rotated_width_block<T, Width, Height, Depth>
{
    using Container = rotated_width_block<T, Width, Height, Depth>;
    Container r;

    for ( std::size_t h = 0; h < Container::height; ++h )
    {
        for ( std::size_t w = 0; w < Container::width; ++w )
        {
            for ( std::size_t d = 0; d < Container::depth; ++d )
            {
                set( f( w, h, d ), r, w, h, d );
            }
        }
    }

    return r;
}
}
