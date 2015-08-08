/**
 * @copyright 2015 Iceberg YOUNG
 * @license GNU Lesser General Public License version 3
 */

#include "base-n.hpp"
#include "base_codec.hpp"
#include <stdexcept>

namespace so {
    namespace {
        uint8_t value(char digit) {
            if ('0' <= digit and digit <= '9') {
                return digit - '0';
            }
            if ('A' <= digit and digit <= 'F') {
                return digit - 'A' + 0xA;
            }
            if ('a' <= digit and digit <= 'f') {
                return digit - 'a' + 0Xa;
            }
            throw new std::out_of_range{
              std::to_string(digit) + " is not in Base16 alphabet."
            };
        }

        class base16_decode :
          public base_decode {
         public:
            base16_decode() :
              half(0),
              step(1) {}

         protected:
            size_t estimate(size_t text) const final override {
                return text / 2;
            }

            bool pop(char c, uint8_t& v) final override {
                if (++this->step %= 2) {
                    v = this->half | value(c);
                    return true;
                }
                else {
                    this->half = value(c) << 4;
                    return false;
                }
            }

         private:
            uint8_t half;
            uint8_t step;
        };
    }

    std::string base16::decode_text(const std::string& text) {
        base16_decode decoder;
        return decoder.decode<std::string>(text);
    }

    std::vector<uint8_t> base16::decode(const std::string& text) {
        base16_decode decoder;
        return decoder.decode<std::vector<uint8_t>>(text);
    }
}
