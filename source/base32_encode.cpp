/**
 * @copyright 2015 Iceberg YOUNG
 * @license GNU Lesser General Public License version 3
 */

#include "base_encode.hpp"

namespace so {
    namespace {
        class base32_encode :
          public base_encode<base32> {
         public:
            base32_encode(bool hex, bool padding) :
              base_encode(
                hex
                  ? "0123456789" "ABCDEFGHIJKLMNOPQRSTUV"
                  : "ABCDEFGHIJKLMNOPQRSTUVWXYZ" "234567",
                padding
              ) {}

         protected:
            size_t stretch(const uint8_t*& in, uint8_t* tmp, const uint8_t* end) const final override {
                tmp[0] = *in >> 3;
                tmp[1] = *in << 2;
                if (++in >= end) return 2;
                tmp[1] |= *in >> 6;
                tmp[2] = *in >> 1;
                tmp[3] = *in << 4;
                if (++in >= end) return 4;
                tmp[3] |= *in >> 4;
                tmp[4] = *in << 1;
                if (++in >= end) return 5;
                tmp[4] |= *in >> 7;
                tmp[5] = *in >> 2;
                tmp[6] = *in << 3;
                if (++in >= end) return 7;
                tmp[6] |= *in >> 5;
                tmp[7] = *in++;
                return 8;
            }
        };
    }

    std::string base32::encode(const std::string& data, bool padding) {
        base32_encode encoder{false, padding};
        return encoder.encode(data);
    }

    std::string base32::encode(const std::vector<uint8_t>& data, bool padding) {
        base32_encode encoder{false, padding};
        return encoder.encode(data);
    }

    std::string base32hex::encode(const std::string& data, bool padding) {
        base32_encode encoder{true, padding};
        return encoder.encode(data);
    }

    std::string base32hex::encode(const std::vector<uint8_t>& data, bool padding) {
        base32_encode encoder{true, padding};
        return encoder.encode(data);
    }
}
