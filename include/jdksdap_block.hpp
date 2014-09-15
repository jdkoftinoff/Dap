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
};

/**
 * 1 dimensional array block indexed by Width
 */
template <typename T, std::size_t Width>
struct block<T, Width, 1, 1>
{
    using array = std::array<T, Width>;
    array content;
};

/**
 * 2 dimensional array block indexed by Width and Height
 */
template <typename T, std::size_t Width, std::size_t Height>
struct block<T, Width, Height, 1>
{
    using array = std::array<std::array<T, Width>, Height>;
    array content;
};

/**
 * 3 dimensional array block indexed by Height, Width, and Depth
 */
template <typename T, std::size_t Width, std::size_t Height = 1, std::size_t Depth = 1>
struct rotated_width_block
{
    using array = std::array<std::array<std::array<T, Height>, Width>, Depth>;
    array content;
};

/**
 * 1 dimensional array block indexed by Width
 */
template <typename T, std::size_t Width>
struct rotated_width_block<T, Width, 1, 1>
{
    using array = std::array<T, Width>;
    array content;
};

/**
 * 2 dimensional array block indexed by Height and Width
 */
template <typename T, std::size_t Width, std::size_t Height>
struct rotated_width_block<T, Width, Height, 1>
{
    using array = std::array<std::array<T, Height>, Width>;
    array content;
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
auto rawget( ContainerT  &c,
             std::size_t i1 = 0,
             std::size_t i2 = 0,
             std::size_t = 0,
             typename traits<ContainerT>::is_2dim_container_type * = 0 ) -> typename traits<ContainerT>::value_type &
{
    return c.content[i2][i1];
}

template <typename ContainerT>
auto rawget( ContainerT &c,
             std::size_t i1 = 0,
             std::size_t i2 = 0,
             std::size_t i3 = 0,
             typename traits<ContainerT>::is_3dim_container_type * = 0 ) -> typename traits<ContainerT>::value_type &
{
    return c.content[i3][i2][i1];
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
    return c.content[i2][i1];
}

template <typename ContainerT>
auto rawget( ContainerT const &c,
             std::size_t i1 = 0,
             std::size_t i2 = 0,
             std::size_t i3 = 0,
             typename traits<ContainerT>::is_3dim_container_type * = 0 ) -> typename traits<ContainerT>::value_type
{
    return c.content[i3][i2][i1];
}

template <typename ContainerT>
auto rawset( typename traits<ContainerT>::is_1dim_value_type const &v,
             ContainerT const &c,
             std::size_t i1 = 0,
             std::size_t = 0,
             std::size_t = 0 ) -> void
{
    c.content[i1] = v;
}

template <typename ContainerT>
auto rawset( typename traits<ContainerT>::is_2dim_value_type const &v,
             ContainerT const &c,
             std::size_t i1 = 0,
             std::size_t i2 = 0,
             std::size_t = 0 ) -> void
{
    c.content[i2][i1] = v;
}

template <typename ContainerT>
auto rawset( typename traits<ContainerT>::is_3dim_value_type const &v,
             ContainerT const &c,
             std::size_t i1 = 0,
             std::size_t i2 = 0,
             std::size_t i3 = 0 ) -> void
{
    c.content[i3][i2][i1] = v;
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
auto set( typename traits<ContainerT>::is_1dim_value_type const &v,
          ContainerT const &c,
          std::size_t w = 0,
          std::size_t = 0,
          std::size_t = 0,
          typename traits<ContainerT>::is_unrotated_value_type * = 0 ) -> void
{
    c.content[w] = v;
}

template <typename ContainerT>
auto set( typename traits<ContainerT>::is_2dim_value_type const &v,
          ContainerT const &c,
          std::size_t w = 0,
          std::size_t h = 0,
          std::size_t = 0,
          typename traits<ContainerT>::is_unrotated_value_type * = 0 ) -> void
{
    c.content[h][w] = v;
}

template <typename ContainerT>
auto set( typename traits<ContainerT>::is_3dim_value_type const &v,
          ContainerT &c,
          std::size_t w = 0,
          std::size_t h = 0,
          std::size_t d = 0,
          typename traits<ContainerT>::is_unrotated_value_type * = 0 ) -> void
{
    c.content[d][h][w] = v;
}

template <typename ContainerT>
auto set( typename traits<ContainerT>::is_1dim_value_type const &v,
          ContainerT &c,
          std::size_t w = 0,
          std::size_t = 0,
          std::size_t = 0,
          typename traits<ContainerT>::is_rotated_width_type * = 0 ) -> void
{
    c.content[w] = v;
}

template <typename ContainerT>
auto set( typename traits<ContainerT>::is_2dim_value_type const &v,
          ContainerT  &c,
          std::size_t w = 0,
          std::size_t h = 0,
          std::size_t = 0,
          typename traits<ContainerT>::is_rotated_width_type * = 0 ) -> void
{
    c.content[w][h] = v;
}

template <typename ContainerT>
auto set( typename traits<ContainerT>::is_3dim_value_type const &v,
          ContainerT  &c,
          std::size_t w = 0,
          std::size_t h = 0,
          std::size_t d = 0,
          typename traits<ContainerT>::is_rotated_width_type * = 0 ) -> void
{
    c.content[d][w][h] = v;
}

template <typename SourceContainerT, typename DestinationContainerT, typename Functor>
void apply( SourceContainerT const &src,
            DestinationContainerT &dest,
            Functor f,
            typename traits<SourceContainerT>::value_type * = 0,
            typename traits<DestinationContainerT>::value_type * = 0 )
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

template <typename ContainerT, typename Functor>
void apply_in_place( ContainerT &srcdest, Functor f, typename traits<ContainerT>::is_1dim_value_type * = 0 )
{
    using ContainerTraits = traits<ContainerT>;
    using ValueType = typename ContainerTraits::value_type;

    for ( std::size_t a = 0; a < ContainerTraits::first_size; ++a )
    {
        ValueType &v = rawget(srcdest,a);
        v = f(v);
    }
}

template <typename ContainerT, typename Functor>
void apply_in_place( ContainerT &srcdest, Functor f, typename traits<ContainerT>::is_2dim_value_type * = 0 )
{
    using ContainerTraits = traits<ContainerT>;
    using ValueType = typename ContainerTraits::value_type;

    for ( std::size_t a = 0; a < ContainerTraits::first_size; ++a )
    {
        for ( std::size_t b = 0; b < ContainerTraits::second_size; ++b )
        {
            ValueType &v = rawget(srcdest,a,b);
            v = f(v);
        }
    }
}


template <typename ContainerT, typename Functor>
void apply_in_place( ContainerT &srcdest, Functor f, typename traits<ContainerT>::is_3dim_value_type * = 0 )
{
    using ContainerTraits = traits<ContainerT>;
    using ValueType = typename ContainerTraits::value_type;

    for ( std::size_t a = 0; a < ContainerTraits::first_size; ++a )
    {
        for ( std::size_t b = 0; b < ContainerTraits::second_size; ++b )
        {
            for ( std::size_t c = 0; c < ContainerTraits::third_size; ++c )
            {
                ValueType &v = rawget(srcdest,a,b,c);
                v = f(v);
            }
        }
    }
}

template <typename OriginalContainerT>
auto rotate( OriginalContainerT const &b ) -> typename traits<OriginalContainerT>::rotate_width_type
{
    typename traits<OriginalContainerT>::rotate_width_type result;
    apply( b,
           result,
           []( typename OriginalContainerT::value_type v )
    { return v; } );
}
}
