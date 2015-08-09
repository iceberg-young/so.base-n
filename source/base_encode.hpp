/**
 * @copyright 2015 Iceberg YOUNG
 * @license GNU Lesser General Public License version 3
 */

#pragma once

#include "base_codec.hpp"

namespace so {
    template<class base_t>
    class base_encode {
     public:
        base_encode(const char* alphabet, bool padding) :
          alphabet(alphabet),
          padding(padding) {}

     public:
        char digit(uint8_t value) const {
            return this->alphabet[value & per_digit<base_t>::mask];
        }

        size_t estimate(size_t data) const {
            return this->padding
              ? (data + per_unit<base_t>::bytes - 1)
                / per_unit<base_t>::bytes * per_unit<base_t>::digits
              : (data * per_unit<base_t>::digits + per_unit<base_t>::bytes - 1)
                / per_unit<base_t>::bytes;
        }

     public:
        template<typename data_t>
        std::string encode(const data_t& data) {
            auto end = reinterpret_cast<const uint8_t*>(&*data.end());
            uint8_t tmp[per_unit<base_t>::digits];
            char out[per_unit<base_t>::digits];

            std::string text;
            text.reserve(this->estimate(data.size()));
            auto in = reinterpret_cast<const uint8_t*>(data.data());
            size_t n = 0;
            while (in < end) {
                n = this->stretch(in, tmp, end);
                for (size_t i = 0; i < n; ++i) {
                    out[i] = this->digit(tmp[i]);
                }
                text.append(out, n);
            }
            if (this->padding and n != 0 and n != sizeof(out)) {
                text.append(sizeof(out) - n, '=');
            }
            return text;
        }

     protected:
        virtual size_t stretch(const uint8_t*& in, uint8_t* tmp, const uint8_t* end) const = 0;

     protected:
        const char* alphabet;
        const bool padding;
    };
}
