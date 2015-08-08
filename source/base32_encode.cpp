/**
 * @copyright 2015 Iceberg YOUNG
 * @license GNU Lesser General Public License version 3
 */

#include "base-n.hpp"
#include "base_codec.hpp"

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
            void push(uint8_t v, std::string& text) final override {
                switch (this->forward()) {
                    case 0: {
                        text += this->digit(v >> 3);
                        this->part = v << 2;
                        break;
                    }
                    case 1: {
                        text += this->digit(this->part | v >> 6);
                        text += this->digit(v >> 1);
                        this->part = v << 4;
                        break;
                    }
                    case 2: {
                        text += this->digit(this->part | v >> 4);
                        this->part = v << 1;
                        break;
                    }
                    case 3: {
                        text += this->digit(this->part | v >> 7);
                        text += this->digit(v >> 2);
                        this->part = v << 3;
                        break;
                    }
                    case 4: {
                        text += this->digit(this->part | v >> 5);
                        text += this->digit(v);
                        break;
                    }
                    default: {
                        throw this->step;
                    }
                }
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
