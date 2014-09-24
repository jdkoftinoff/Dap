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
#include <array>

namespace JDKSDap
{

template <std::size_t WidthIndex, std::size_t HeightIndex, std::size_t DepthIndex>
struct twist
{
    /// the self referring twist type for SFINAI
    using twist_type = twist<WidthIndex, HeightIndex, DepthIndex>;

    /// The raw index of the width parameter
    static const std::size_t width_index = WidthIndex;

    /// The raw index of the height parameter
    static const std::size_t height_index = HeightIndex;

    /// The raw index of the depth parameter
    static const std::size_t depth_index = DepthIndex;

    /// The (width,height,depth) item that the raw index0 maps to
    static const std::size_t raw_index0_map = ( WidthIndex == 0 ? 0 : ( HeightIndex == 0 ? 1 : ( DepthIndex == 0 ? 2 : 0 ) ) );

    /// The (width,height,depth) item that the raw index1 maps to
    static const std::size_t raw_index1_map = ( WidthIndex == 1 ? 0 : ( HeightIndex == 1 ? 1 : ( DepthIndex == 1 ? 2 : 0 ) ) );

    /// The (width,height,depth) item that the raw index2 maps to
    static const std::size_t raw_index2_map = ( WidthIndex == 2 ? 0 : ( HeightIndex == 2 ? 1 : ( DepthIndex == 2 ? 2 : 0 ) ) );

    /// Helper template to map Width,Height,Depth dimensions to raw_index0_size, raw_index1_size, raw_index2_size
    template <std::size_t Width, std::size_t Height, std::size_t Depth>
    struct dimensions
    {
        static const std::size_t raw_index0_size
            = ( WidthIndex == 0 ? Width : ( HeightIndex == 0 ? Height : ( DepthIndex == 0 ? Depth : 0 ) ) );
        static const std::size_t raw_index1_size
            = ( WidthIndex == 1 ? Width : ( HeightIndex == 1 ? Height : ( DepthIndex == 1 ? Depth : 0 ) ) );
        static const std::size_t raw_index2_size
            = ( WidthIndex == 2 ? Width : ( HeightIndex == 2 ? Height : ( DepthIndex == 2 ? Depth : 0 ) ) );
    };

    /// Helper function to get the width position from a raw_index tuple
    static inline std::size_t width_pos_from( std::tuple<std::size_t, std::size_t, std::size_t> raw_indexes )
    {
        return std::get<width_index>( raw_indexes );
    }

    /// Helper function to get the height position from a raw_index tuple
    static inline std::size_t height_pos_from( std::tuple<std::size_t, std::size_t, std::size_t> raw_indexes )
    {
        return std::get<height_index>( raw_indexes );
    }

    /// Helper function to get the depth position from a raw_index tuple
    static inline std::size_t depth_pos_from( std::tuple<std::size_t, std::size_t, std::size_t> raw_indexes )
    {
        return std::get<depth_index>( raw_indexes );
    }

    /// Helper function to get the raw_index0 from a (width,height,depth) tuple
    static inline std::size_t raw_index0_from( std::tuple<std::size_t, std::size_t, std::size_t> indexes )
    {
        return std::get<raw_index0_map>( indexes );
    }

    /// Helper function to get the raw_index1 from a (width,height,depth) tuple
    static inline std::size_t raw_index1_from( std::tuple<std::size_t, std::size_t, std::size_t> indexes )
    {
        return std::get<raw_index1_map>( indexes );
    }

    /// Helper function to get the raw_index2 from a (width,height,depth) tuple
    static inline std::size_t raw_index2_from( std::tuple<std::size_t, std::size_t, std::size_t> indexes )
    {
        return std::get<raw_index0_map>( indexes );
    }
};

template <typename InputTwist, std::size_t AdditionalTwist>
struct twister
{
};

template <typename InputTwist>
struct twister<InputTwist, 0>
{
    using input_twist = twist<InputTwist::width_index, InputTwist::height_index, InputTwist::depth_index>;
    using output_twist = twist<InputTwist::width_index, InputTwist::height_index, InputTwist::depth_index>;
};

using twist0 = typename twister<twist<0, 1, 2>, 0>::output_twist;

template <typename InputTwist>
struct twister<InputTwist, 1>
{
    using input_twist = twist<InputTwist::width_index, InputTwist::height_index, InputTwist::depth_index>;
    using output_twist = twist<InputTwist::height_index, InputTwist::width_index, InputTwist::depth_index>;
};

using twist1 = typename twister<twist<0, 1, 2>, 1>::output_twist;

template <typename InputTwist>
struct twister<InputTwist, 2>
{
    using input_twist = twist<InputTwist::width_index, InputTwist::height_index, InputTwist::depth_index>;
    using output_twist = twist<InputTwist::height_index, InputTwist::depth_index, InputTwist::width_index>;
};

using twist2 = typename twister<twist<0, 1, 2>, 2>::output_twist;

template <typename InputTwist>
struct twister<InputTwist, 3>
{
    using input_twist = twist<InputTwist::width_index, InputTwist::height_index, InputTwist::depth_index>;
    using output_twist = twist<InputTwist::depth_index, InputTwist::height_index, InputTwist::width_index>;
};

using twist3 = typename twister<twist<0, 1, 2>, 3>::output_twist;

template <typename InputTwist>
struct twister<InputTwist, 4>
{
    using input_twist = twist<InputTwist::width_index, InputTwist::height_index, InputTwist::depth_index>;
    using output_twist = twist<InputTwist::depth_index, InputTwist::width_index, InputTwist::height_index>;
};

using twist4 = typename twister<twist<0, 1, 2>, 4>::output_twist;

template <typename InputTwist>
struct twister<InputTwist, 5>
{
    using input_twist = twist<InputTwist::width_index, InputTwist::height_index, InputTwist::depth_index>;
    using output_twist = twist<InputTwist::width_index, InputTwist::depth_index, InputTwist::height_index>;
};

using twist5 = typename twister<twist<0, 1, 2>, 5>::output_twist;

template <typename T, typename TwistType, std::size_t Width, std::size_t Height = 1, std::size_t Depth = 1>
struct twist_array
{
    using twist_type = TwistType;
    using dimensions_type = typename twist_type::template dimensions<Width, Height, Depth>;
    static const std::size_t raw_index0_size = dimensions_type::raw_index0_size;
    static const std::size_t raw_index1_size = dimensions_type::raw_index1_size;
    static const std::size_t raw_index2_size = dimensions_type::raw_index2_size;
    const std::size_t depth_size = Depth;
    const std::size_t height_size = Height;
    const std::size_t width_size = Width;
    using value_type = T;

    using type = std::array<std::array<std::array<value_type, raw_index2_size>, raw_index1_size>, raw_index0_size>;

    static value_type &rawget( type &a, std::size_t index0, std::size_t index1, std::size_t index2 )
    {
        return a[index0][index1][index2];
    }

    static value_type rawget( type const &a, std::size_t index0, std::size_t index1, std::size_t index2 )
    {
        return a[index0][index1][index2];
    }

    static void rawset( type &a, value_type v, std::size_t index0, std::size_t index1, std::size_t index2 )
    {
        a[index0][index1][index2] = v;
    }

    static inline T &get( type &a, std::size_t width_pos, std::size_t height_pos, std::size_t depth_pos )
    {
        auto pos = std::make_tuple( width_pos, height_pos, depth_pos );
        std::size_t index0 = twist_type::width_pos_from( pos );
        std::size_t index1 = twist_type::height_pos_from( pos );
        std::size_t index2 = twist_type::depth_pos_from( pos );

        return a[index0][index1][index2];
    }

    static inline T get( type const &a, std::size_t width_pos, std::size_t height_pos, std::size_t depth_pos )
    {
        auto pos = std::make_tuple( width_pos, height_pos, depth_pos );
        std::size_t index0 = twist_type::width_pos_from( pos );
        std::size_t index1 = twist_type::height_pos_from( pos );
        std::size_t index2 = twist_type::depth_pos_from( pos );

        return a[index0][index1][index2];
    }

    static inline void set( type &a, value_type v, std::size_t width_pos, std::size_t height_pos, std::size_t depth_pos )
    {
        auto pos = std::make_tuple( width_pos, height_pos, depth_pos );
        std::size_t index0 = twist_type::width_pos_from( pos );
        std::size_t index1 = twist_type::height_pos_from( pos );
        std::size_t index2 = twist_type::depth_pos_from( pos );

        a[index0][index1][index2] = v;
    }
};
}
