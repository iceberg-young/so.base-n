/**
 * @copyright 2015 Iceberg YOUNG
 * @license GNU Lesser General Public License version 3
 */

#pragma once

#include "base-n.hpp"
#include <stdexcept>

namespace so {
    template<class base_t>
    class base_decode {
     public:
        constexpr size_t estimate(size_t text) const {
            return text
              * base_t::per_unit.bytes
              / base_t::per_unit.digits;
        }

     public:
        template<typename data_t>
        data_t decode(const std::string& text, bool liberal) const {
            const auto end = &*text.end();
            uint8_t tmp[base_t::per_unit.digits];
            uint8_t out[base_t::per_unit.bytes];

            data_t data;
            data.reserve(this->estimate(text.size()));
            auto in = text.data();
            while (in < end) {
                size_t n = this->translate(in, tmp, end, liberal);
                size_t m = this->shrink(tmp, out, n);
                data.insert(data.end(), out, out + m);
            }
            return data;
        }

     protected:
        size_t translate(const char*& in, uint8_t* tmp, const char* end, bool liberal) const {
            size_t n = 0;
            while (in < end and n < base_t::per_unit.digits) {
                try {
                    char c = *in++;
                    if (c == '=') {
                        this->skip_padding(in, n);
                        break;
                    }
                    tmp[n] = this->value(c);
                    ++n;
                }
                catch (const std::out_of_range& e) {
                    if (!liberal) throw;
                }
            }
            return n;
        }

        void skip_padding(const char*& in, size_t n) const {
            if (!this->is_complete(n)) {
                throw std::out_of_range{
                  "Incomplete data (" + std::to_string(n) + " digits)."
                };
            }
            size_t r = base_t::per_unit.digits - n - 1; // -already skipped.
            while (r--) {
                if (*in++ != '=') {
                    throw std::out_of_range{"Incomplete padding."};
                }
            }
        }

     protected:
        virtual bool is_complete(size_t n) const = 0;

        virtual size_t shrink(uint8_t* tmp, uint8_t* out, size_t length) const = 0;

        virtual uint8_t value(char digit) const = 0;
    };
}
