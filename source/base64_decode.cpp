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
            throw new std::out_of_range{
              std::to_string(digit) + " is not in Base64 alphabet."
            };
        }

        class base64_decode :
          public base_decode {
         public:
            base64_decode() :
              part(0),
              step(3) {}

         protected:
            size_t estimate(size_t text) const final override {
                return text * 3 / 4;
            }

            bool pop(char c, uint8_t& v) final override {
                if (c == '=') {
                    this->step = 3;
                    return false;
                }

                switch (++this->step %= 4) {
                    case 0: {
                        this->part = value(c) << 2;
                        return false;
                    }
                    case 1: {
                        uint8_t rest = value(c);
                        v = this->part | (rest >> 4);
                        this->part = rest << 4;
                        return true;
                    }
                    case 2: {
                        uint8_t rest = value(c);
                        v = this->part | (rest >> 2);
                        this->part = rest << 6;
                        return true;
                    }
                    case 3: {
                        v = this->part | value(c);
                        return true;
                    }
                    default: {
                        throw this->step;
                    }
                }
            }

         private:
            uint8_t part;
            uint8_t step;
        };
    }

    std::string base64::decode_text(const std::string& text) {
        base64_decode decoder;
        return decoder.decode<std::string>(text);
    }

    std::vector<uint8_t> base64::decode(const std::string& text) {
        base64_decode decoder;
        return decoder.decode<std::vector<uint8_t>>(text);
    }
}
