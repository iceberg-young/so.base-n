/**
 * @copyright 2015 Iceberg YOUNG
 * @license GNU Lesser General Public License version 3
 */

#include "base-n.hpp"
#include "base_codec.hpp"

namespace so {
    namespace {
        class base16_encode :
          public base_encode<base16> {
         public:
            base16_encode() :
              base_encode("0123456789ABCDEF", false) {}

         protected:
            void push(uint8_t b, std::string& text) final override {
                (text += this->digit(b >> 4)) += this->digit(b);
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
