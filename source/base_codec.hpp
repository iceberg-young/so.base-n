/**
 * @copyright 2015 Iceberg YOUNG
 * @license GNU Lesser General Public License version 3
 */

#pragma once

#include "base-n.hpp"

namespace so {
    template<typename base_t>
    struct per_unit;

    template<>
    struct per_unit<base64> {
        using value_t = uint32_t;
        static constexpr int bytes = 3;
        static constexpr int digits = 4;
    };

    template<>
    struct per_unit<base32> {
        using value_t = uint64_t;
        static constexpr int bytes = 5;
        static constexpr int digits = 8;
    };

    template<>
    struct per_unit<base16> {
        using value_t = uint8_t;
        static constexpr int bytes = 1;
        static constexpr int digits = 2;
    };

    template<typename base_t>
    struct per_digit;

    template<>
    struct per_digit<base64> {
        static constexpr int bits = 6;
        static constexpr uint8_t mask = 0x3F;
    };

    template<>
    struct per_digit<base32> {
        static constexpr int bits = 5;
        static constexpr uint8_t mask = 0x1F;
    };

    template<>
    struct per_digit<base16> {
        static constexpr int bits = 4;
        static constexpr uint8_t mask = 0x0F;
    };
}
