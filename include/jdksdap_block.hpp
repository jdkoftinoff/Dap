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
#include "jdksdap_twist.hpp"

namespace jdksdap
{

/**
 * 3 dimensional array block indexed by Width, Height, and Depth
 */
template <typename T, typename TwistType, std::size_t Width, std::size_t Height = 1, std::size_t Depth = 1>
struct block
{
    using twist_type = TwistType;
    using value_type = T;
    using twist_array_type = twist_array<value_type, twist_type, Width, Height, Depth>;
    using array_type = typename twist_array_type::type;

    array_type content;
};

/**
 * Traits for unrotated array block
 */
template <typename T, typename TwistType, size_t Width, size_t Height, size_t Depth>
struct traits<block<T, TwistType, Width, Height, Depth> >
{
    using value_type = T;
    using twist_type = TwistType;
    using container_type = block<T, twist_type, Width, Height, Depth>;
    using twist_array_type = typename container_type::twist_array_type;
    using array_type = typename container_type::array_type;

    static const size_t width = Width;
    static const size_t height = Height;
    static const size_t depth = Depth;

    static const size_t raw_index0_size = twist_array_type::raw_index0_size;
    static const size_t raw_index1_size = twist_array_type::raw_index1_size;
    static const size_t raw_index2_size = twist_array_type::raw_index2_size;
};

template <typename ContainerT>
auto get( ContainerT &c,
          std::size_t width_pos = 0,
          std::size_t height_pos = 0,
          std::size_t depth_pos = 0,
          typename traits<ContainerT>::twist_array_type * = 0 ) -> typename traits<ContainerT>::value_type &
{
    using twist_array_type = typename traits<ContainerT>::twist_array_type;
    return twist_array_type::get( c.content, width_pos, height_pos, depth_pos );
}

template <typename ContainerT>
auto get( ContainerT const &c,
          std::size_t width_pos = 0,
          std::size_t height_pos = 0,
          std::size_t depth_pos = 0,
          typename traits<ContainerT>::twist_array_type * = 0 ) -> typename traits<ContainerT>::value_type
{
    using twist_array_type = typename traits<ContainerT>::twist_array_type;
    return twist_array_type::get( c.content, width_pos, height_pos, depth_pos );
}

template <typename ContainerT>
auto set( ContainerT &c,
          typename traits<ContainerT>::value_type v,
          std::size_t width_pos = 0,
          std::size_t height_pos = 0,
          std::size_t depth_pos = 0,
          typename traits<ContainerT>::twist_array_type * = 0 ) -> void
{
    using twist_array_type = typename traits<ContainerT>::twist_array_type;
    twist_array_type::set( c.content, v, width_pos, height_pos, depth_pos );
}

template <typename ContainerT>
auto rawget( ContainerT &c,
             std::size_t i0 = 0,
             std::size_t i1 = 0,
             std::size_t i2 = 0,
             typename traits<ContainerT>::twist_array_type * = 0 ) -> typename traits<ContainerT>::value_type &
{
    using twist_array_type = typename traits<ContainerT>::twist_array_type;
    return twist_array_type::rawget( c.content, i0, i1, i2 );
}

template <typename ContainerT>
auto rawget( ContainerT const &c,
             std::size_t i0 = 0,
             std::size_t i1 = 0,
             std::size_t i2 = 0,
             typename traits<ContainerT>::twist_array_type * = 0 ) -> typename traits<ContainerT>::value_type &
{
    using twist_array_type = typename traits<ContainerT>::twist_array_type;
    return twist_array_type::rawget( c.content, i0, i1, i2 );
}

template <typename ContainerT>
auto rawset( ContainerT &c,
             typename traits<ContainerT>::value_type v,
             std::size_t i0 = 0,
             std::size_t i1 = 0,
             std::size_t i2 = 0,
             typename traits<ContainerT>::twist_array_type * = 0 ) -> void
{
    using twist_array_type = typename traits<ContainerT>::twist_array_type;
    twist_array_type::rawset( c.content, v, i0, i1, i2 );
}

template <typename ContainerT, typename Functor>
void apply( ContainerT &srcdest, Functor f, typename traits<ContainerT>::twist_array_type * = 0 )
{
    using ContainerTraits = traits<ContainerT>;
    using ContainerTwistType = typename ContainerTraits::twist_type;
    using ValueType = typename ContainerTraits::value_type;

    for ( std::size_t a = 0; a < ContainerTraits::raw_index0_size; ++a )
    {
        for ( std::size_t b = 0; b < ContainerTraits::raw_index1_size; ++b )
        {
            for ( std::size_t c = 0; c < ContainerTraits::raw_index2_size; ++c )
            {
                auto pos = std::make_tuple( a, b, c );
                std::size_t w = ContainerTwistType::width_pos_from( pos );
                std::size_t h = ContainerTwistType::height_pos_from( pos );
                std::size_t d = ContainerTwistType::depth_pos_from( pos );

                ValueType &v = rawget( srcdest.content, w, h, d );
                v = f( v, w, h, d );
            }
        }
    }
}

template <typename SourceContainerT, typename DestinationContainerT, typename Functor>
auto apply( SourceContainerT const &src,
            DestinationContainerT &dest,
            Functor f,
            typename traits<SourceContainerT>::twist_array_type * = 0,
            typename traits<DestinationContainerT>::twist_array_type * = 0 ) -> void
{
    using SourceContainerTraits = traits<SourceContainerT>;
    using DestinationContainerTraits = traits<DestinationContainerT>;
    using DestinationContainerTwistType = typename DestinationContainerTraits::twist_type;
    using SourceValueType = typename SourceContainerTraits::value_type;
    using DestinationValueType = typename DestinationContainerTraits::value_type;

    static_assert( SourceContainerTraits::width == DestinationContainerTraits::width,
                   "Width different between Source and Destination" );
    static_assert( SourceContainerTraits::height == DestinationContainerTraits::height,
                   "Height different between Source and Destination" );
    static_assert( SourceContainerTraits::depth == DestinationContainerTraits::depth,
                   "Depth different between Source and Destination" );

    for ( std::size_t a = 0; a < DestinationContainerTraits::raw_index0_size; ++a )
    {
        for ( std::size_t b = 0; b < DestinationContainerTraits::raw_index1_size; ++b )
        {
            for ( std::size_t c = 0; c < DestinationContainerTraits::raw_index2_size; ++c )
            {
                auto pos = std::make_tuple( a, b, c );
                std::size_t w = DestinationContainerTwistType::width_pos_from( pos );
                std::size_t h = DestinationContainerTwistType::height_pos_from( pos );
                std::size_t d = DestinationContainerTwistType::depth_pos_from( pos );

                DestinationValueType v = f( get( src.content, w, h, d ), w, h, d );
                rawset( dest.content, v, w, h, d );
            }
        }
    }
}

template <typename Container1T, typename Container2T, typename ResultContainerT, typename Functor>
auto apply( Container1T const &c1,
            Container2T const &c2,
            ResultContainerT &r,
            Functor f,
            typename traits<Container1T>::twist_array_type * = 0,
            typename traits<Container2T>::twist_array_type * = 0,
            typename traits<ResultContainerT>::twist_array_type * = 0 ) -> void
{
    using Container1Traits = traits<Container1T>;
    using Container2Traits = traits<Container2T>;
    using ResultContainerTraits = traits<ResultContainerT>;
    using ResultContainerTwistType = typename ResultContainerTraits::twist_type;
    using ValueType1 = typename Container1Traits::value_type;
    using ValueType2 = typename Container2Traits::value_type;
    using ValueTypeResult = typename ResultContainerTraits::value_type;

    static_assert( Container1Traits::width == Container2Traits::width, "Width different between Source and Destination" );
    static_assert( Container1Traits::height == Container2Traits::height, "Height different between Source and Destination" );
    static_assert( Container1Traits::depth == Container2Traits::depth, "Depth different between Source and Destination" );

    for ( std::size_t a = 0; a < ResultContainerTraits::raw_index0_size; ++a )
    {
        for ( std::size_t b = 0; b < ResultContainerTraits::raw_index1_size; ++b )
        {
            for ( std::size_t c = 0; c < ResultContainerTraits::raw_index2_size; ++c )
            {
                auto pos = std::make_tuple( a, b, c );
                std::size_t w = ResultContainerTwistType::width_pos_from( pos );
                std::size_t h = ResultContainerTwistType::height_pos_from( pos );
                std::size_t d = ResultContainerTwistType::depth_pos_from( pos );

                ValueTypeResult v = f( get( c1.content, w, h, d ), get( c2.content, w, h, d ), w, h, d );
                rawset( r.content, v, w, h, d );
            }
        }
    }
}

template <typename TwistType, std::size_t Width, std::size_t Height, std::size_t Depth, typename T>
auto make_block( T elem ) -> block<T, TwistType, Width, Height, Depth>
{
    using Container = block<T, TwistType, Width, Height, Depth>;
    using ContainerTraits = traits<Container>;
    Container r;

    for ( std::size_t a = 0; a < ContainerTraits::raw_index0_size; ++a )
    {
        for ( std::size_t b = 0; b < ContainerTraits::raw_index1_size; ++b )
        {
            for ( std::size_t c = 0; c < ContainerTraits::raw_index2_size; ++c )
            {
                rawset( r, elem, a, b, c );
            }
        }
    }

    return r;
}

template <typename T, typename TwistType, std::size_t Width, std::size_t Height, std::size_t Depth, typename Functor>
auto fill_block( Functor f ) -> block<T, TwistType, Width, Height, Depth>
{
    using Container = block<T, TwistType, Width, Height, Depth>;
    using ContainerTraits = traits<Container>;
    using ContainerTwistType = typename Container::twist_type;
    Container r;

    for ( std::size_t a = 0; a < ContainerTraits::raw_index0_size; ++a )
    {
        for ( std::size_t b = 0; b < ContainerTraits::raw_index1_size; ++b )
        {
            for ( std::size_t c = 0; c < ContainerTraits::raw_index2_size; ++c )
            {
                auto pos = std::make_tuple( a, b, c );
                std::size_t w = ContainerTwistType::width_pos_from( pos );
                std::size_t h = ContainerTwistType::height_pos_from( pos );
                std::size_t d = ContainerTwistType::depth_pos_from( pos );

                rawset( r, f( w, h, d ), a, b, c );
            }
        }
    }

    return r;
}

template <int TwistAmount, typename InputContainerType>
auto twist_block( InputContainerType const &input )
    -> block<typename traits<InputContainerType>::value_type,
             typename twister<typename InputContainerType::twist_type, TwistAmount>::output_twist,
             traits<InputContainerType>::width,
             traits<InputContainerType>::height,
             traits<InputContainerType>::depth>
{
    using InputContainerTwistType = typename InputContainerType::twist_type;
    using InputContainerTraits = traits<InputContainerType>;
    using OutputContainerType = block<typename traits<InputContainerType>::value_type,
                                      typename twister<typename InputContainerType::twist_type, TwistAmount>::output_twist,
                                      InputContainerTraits::width,
                                      InputContainerTraits::height,
                                      InputContainerTraits::depth>;
    using OutputContainerTraits = traits<OutputContainerType>;
    using OutputContainerTwistType = typename OutputContainerType::twist_type;

    OutputContainerType r;

    for ( std::size_t a = 0; a < OutputContainerTraits::raw_index0_size; ++a )
    {
        for ( std::size_t b = 0; b < OutputContainerTraits::raw_index1_size; ++b )
        {
            for ( std::size_t c = 0; c < OutputContainerTraits::raw_index2_size; ++c )
            {
                auto pos = std::make_tuple( a, b, c );
                std::size_t w = InputContainerTwistType::width_pos_from( pos );
                std::size_t h = InputContainerTwistType::height_pos_from( pos );
                std::size_t d = InputContainerTwistType::depth_pos_from( pos );

                rawset( r, get( input, w, h, d ), a, b, c );
            }
        }
    }

    return r;
}
}
