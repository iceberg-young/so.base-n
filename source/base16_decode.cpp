/**
 * @copyright 2015 Iceberg YOUNG
 * @license GNU Lesser General Public License version 3
 */

#include "base_decode.hpp"

namespace so {
    namespace {
        class base16_decode :
          public base_decode<base16> {
         protected:
            bool is_complete(size_t) const final override {
                return false; // Base16 does not need padding.
            }

            size_t shrink(uint8_t* tmp, uint8_t* out, size_t length) const final override {
                if (length < 2) return 0;
                *out = (tmp[0] << 4) | tmp[1];
                return 1;
            }

            uint8_t value(char digit) const final override {
                if ('0' <= digit and digit <= '9') {
                    return digit - '0';
                }
                if ('A' <= digit and digit <= 'F') {
                    return digit - 'A' + 0xA;
                }
                if ('a' <= digit and digit <= 'f') {
                    return digit - 'a' + 0Xa;
                }
                throw std::out_of_range{
                  std::to_string(digit) + " is not in Base16 alphabet."
                };
            }
        };
    }

    std::string base16::decode_text(const std::string& text, bool liberal) {
        base16_decode decoder;
        return decoder.decode<std::string>(text, liberal);
    }

    std::vector<uint8_t> base16::decode(const std::string& text, bool liberal) {
        base16_decode decoder;
        return decoder.decode<std::vector<uint8_t>>(text, liberal);
    }
}
