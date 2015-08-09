/**
 * @copyright 2015 Iceberg YOUNG
 * @license GNU Lesser General Public License version 3
 */

#include "base_encode.hpp"

namespace so {
    namespace {
        class base64_encode :
          public base_encode<base64> {
         public:
            base64_encode(bool url, bool padding) :
              base_encode(
                url
                  ? "ABCDEFGHIJKLMNOPQRSTUVWXYZ" "abcdefghijklmnopqrstuvwxyz"
                  "0123456789" "-_"
                  : "ABCDEFGHIJKLMNOPQRSTUVWXYZ" "abcdefghijklmnopqrstuvwxyz"
                  "0123456789" "+/",
                padding
              ) {}

         protected:
            size_t stretch(const uint8_t*& in, uint8_t* tmp, const uint8_t* end) const final override {
                tmp[0] = *in >> 2;
                tmp[1] = *in << 4;
                if (++in >= end) return 2;
                tmp[1] |= *in >> 4;
                tmp[2] = *in << 2;
                if (++in >= end) return 3;
                tmp[2] |= *in >> 6;
                tmp[3] = *in++;
                return 4;
            }
        };
    }

    std::string base64::encode(const std::string& data, bool padding) {
        base64_encode encoder{false, padding};
        return encoder.encode(data);
    }

    std::string base64::encode(const std::vector<uint8_t>& data, bool padding) {
        base64_encode encoder{false, padding};
        return encoder.encode(data);
    }

    std::string base64url::encode(const std::string& data, bool padding) {
        base64_encode encoder{true, padding};
        return encoder.encode(data);
    }

    std::string base64url::encode(const std::vector<uint8_t>& data, bool padding) {
        base64_encode encoder{true, padding};
        return encoder.encode(data);
    }
}
