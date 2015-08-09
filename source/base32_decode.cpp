/**
 * @copyright 2015 Iceberg YOUNG
 * @license GNU Lesser General Public License version 3
 */

#include "base_decode.hpp"

namespace so {
    namespace {
        uint8_t lookup_hex(char digit) {
            if ('0' <= digit and digit <= '9') {
                return digit - '0';
            }
            if ('A' <= digit and digit <= 'V') {
                return digit - 'A' + 0xA;
            }
            if ('a' <= digit and digit <= 'v') {
                return digit - 'a' + 0Xa;
            }
            throw std::out_of_range{
              std::to_string(digit) + " is not in Base32-HEX alphabet."
            };
        }

        uint8_t lookup(char digit) {
            if ('A' <= digit and digit <= 'Z') {
                return digit - 'A';
            }
            if ('a' <= digit and digit <= 'z') {
                return digit - 'a';
            }
            if ('2' <= digit and digit <= '7') {
                return digit - '2' + 26;
            }
            throw std::out_of_range{
              std::to_string(digit) + " is not in Base32 alphabet."
            };
        }

        class base32_decode :
          public base_decode<base32> {
         public:
            base32_decode(bool hex) :
              hex(hex) {}

         protected:
            bool is_complete(size_t n) const final override {
                return n == 2 or n == 4 or n == 5 or n == 7;
            }

            size_t shrink(uint8_t* tmp, uint8_t* out, size_t length) const final override {
                if (length < 2) return 0;
                out[0] = (tmp[0] << 3) | (tmp[1] >> 2);
                if (length < 4) return 1;
                out[1] = (tmp[1] << 6) | (tmp[2] << 1) | (tmp[3] >> 4);
                if (length < 5) return 2;
                out[2] = (tmp[3] << 4) | (tmp[4] >> 1);
                if (length < 7) return 3;
                out[3] = (tmp[4] << 7) | (tmp[5] << 2) | (tmp[6] >> 3);
                if (length < 8) return 4;
                out[4] = (tmp[6] << 5) | tmp[7];
                return 5;
            }

            uint8_t value(char digit) const final override {
                return this->hex ? lookup_hex(digit) : lookup(digit);
            }

         private:
            const bool hex;
        };
    }

    std::string base32::decode_text(const std::string& text, bool liberal) {
        base32_decode decoder{false};
        return decoder.decode<std::string>(text, liberal);
    }

    std::vector<uint8_t> base32::decode(const std::string& text, bool liberal) {
        base32_decode decoder{false};
        return decoder.decode<std::vector<uint8_t>>(text, liberal);
    }

    std::string base32hex::decode_text(const std::string& text, bool liberal) {
        base32_decode decoder{true};
        return decoder.decode<std::string>(text, liberal);
    }

    std::vector<uint8_t> base32hex::decode(const std::string& text, bool liberal) {
        base32_decode decoder{true};
        return decoder.decode<std::vector<uint8_t>>(text, liberal);
    }
}
