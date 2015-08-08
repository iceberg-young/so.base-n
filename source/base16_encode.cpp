/**
 * @copyright 2015 Iceberg YOUNG
 * @license GNU Lesser General Public License version 3
 */

#include "base-n.hpp"
#include "base_codec.hpp"

namespace so {
    namespace {
        char digit(uint8_t value) {
            return "0123456789ABCDEF"[value & 0x0F];
        }

        class base16_encode :
          public base_encode {
         protected:
            void complete(std::string& text) final override {}

            size_t estimate(size_t data) const final override {
                return data * 2;
            }

            void push(uint8_t b, std::string& text) final override {
                (text += digit(b >> 4)) += digit(b);
            }
        };
    }

    std::string base16::encode(const std::string& data) {
        base16_encode encoder;
        return encoder.encode(data);
    }

    std::string base16::encode(const std::vector<uint8_t>& data) {
        base16_encode encoder;
        return encoder.encode(data);
    }
}
