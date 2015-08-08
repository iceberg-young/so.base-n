/**
 * @copyright 2015 Iceberg YOUNG
 * @license GNU Lesser General Public License version 3
 */

#include "base-n.hpp"
#include "base_codec.hpp"
#include <stdexcept>

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
            throw new std::out_of_range{
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
            throw new std::out_of_range{
              std::to_string(digit) + " is not in Base32 alphabet."
            };
        }

        class base32_decode :
          public base_decode<base32> {
         public:
            base32_decode(bool hex) :
              value(hex ? &lookup_hex : &lookup) {}

         protected:
            bool pop(char c, uint8_t& v) final override {
                if (c == '=') {
                    this->step = -1;
                    return false;
                }

                switch (this->forward()) {
                    case 0: {
                        this->part = this->value(c) << 3;
                        return false;
                    }
                    case 1: {
                        uint8_t rest = this->value(c);
                        v = this->part | (rest >> 2);
                        this->part = rest << 6;
                        return true;
                    }
                    case 2: {
                        this->part |= this->value(c) << 1;
                        return false;
                    }
                    case 3: {
                        uint8_t rest = this->value(c);
                        v = this->part | (rest >> 4);
                        this->part = rest << 4;
                        return true;
                    }
                    case 4: {
                        uint8_t rest = this->value(c);
                        v = this->part | (rest >> 1);
                        this->part = rest << 7;
                        return true;
                    }
                    case 5: {
                        this->part |= this->value(c) << 2;
                        return false;
                    }
                    case 6: {
                        uint8_t rest = this->value(c);
                        v = this->part | (rest >> 3);
                        this->part = rest << 5;
                        return true;
                    }
                    case 7: {
                        v = this->part | this->value(c);
                        return true;
                    }
                    default: {
                        throw this->step;
                    }
                }
            }

         private:
            uint8_t (* const value)(char);
        };
    }

    std::string base32::decode_text(const std::string& text) {
        base32_decode decoder{false};
        return decoder.decode<std::string>(text);
    }

    std::vector<uint8_t> base32::decode(const std::string& text) {
        base32_decode decoder{false};
        return decoder.decode<std::vector<uint8_t>>(text);
    }

    std::string base32hex::decode_text(const std::string& text) {
        base32_decode decoder{true};
        return decoder.decode<std::string>(text);
    }

    std::vector<uint8_t> base32hex::decode(const std::string& text) {
        base32_decode decoder{true};
        return decoder.decode<std::vector<uint8_t>>(text);
    }
}
