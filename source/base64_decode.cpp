/**
 * @copyright 2015 Iceberg YOUNG
 * @license GNU Lesser General Public License version 3
 */

#include "base_decode.hpp"

namespace so {
    namespace {
        class base64_decode :
          public base_decode<base64> {
         protected:
            bool is_complete(size_t n) const final override {
                return n == 2 or n == 3;
            }

            size_t shrink(uint8_t* tmp, uint8_t* out, size_t length) const final override {
                if (length < 2) return 0;
                out[0] = (tmp[0] << 2) | (tmp[1] >> 4);
                if (length < 3) return 1;
                out[1] = (tmp[1] << 4) | (tmp[2] >> 2);
                if (length < 4) return 2;
                out[2] = (tmp[2] << 6) | tmp[3];
                return 3;
            }

            uint8_t value(char digit) const final override {
                if ('A' <= digit and digit <= 'Z') {
                    return digit - 'A';
                }
                if ('a' <= digit and digit <= 'z') {
                    return digit - 'a' + 26;
                }
                if ('0' <= digit and digit <= '9') {
                    return digit - '0' + 52;
                }
                if (digit == '+' or digit == '-') return 62;
                if (digit == '/' or digit == '_') return 63;
                throw std::out_of_range{
                  std::to_string(digit) + " is not in Base64 alphabet."
                };
            }
        };
    }

    std::string base64::decode_text(const std::string& text, bool liberal) {
        base64_decode decoder;
        return decoder.decode<std::string>(text, liberal);
    }

    std::vector<uint8_t> base64::decode(const std::string& text, bool liberal) {
        base64_decode decoder;
        return decoder.decode<std::vector<uint8_t>>(text, liberal);
    }

    std::string base64url::decode_text(const std::string& text, bool liberal) {
        base64_decode decoder;
        return decoder.decode<std::string>(text, liberal);
    }

    std::vector<uint8_t> base64url::decode(const std::string& text, bool liberal) {
        base64_decode decoder;
        return decoder.decode<std::vector<uint8_t>>(text, liberal);
    }
}
