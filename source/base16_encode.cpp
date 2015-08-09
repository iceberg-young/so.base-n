/**
 * @copyright 2015 Iceberg YOUNG
 * @license GNU Lesser General Public License version 3
 */

#include "base_encode.hpp"

namespace so {
    namespace {
        class base16_encode :
          public base_encode<base16> {
         public:
            base16_encode() :
              base_encode("0123456789ABCDEF", false) {}

         protected:
            size_t stretch(const uint8_t*& in, uint8_t* tmp, const uint8_t* end) const final override {
                tmp[0] = *in >> 4;
                tmp[1] = *in++;
                return 2;
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
