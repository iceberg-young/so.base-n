/**
 * @copyright 2015 Iceberg YOUNG
 * @license GNU Lesser General Public License version 3
 */

#include "base-n.hpp"
#include "base_codec.hpp"

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
            void push(uint8_t v, std::string& text) final override {
                switch (this->forward()) {
                    case 0: {
                        text += this->digit(v >> 2);
                        this->part = v << 4;
                        break;
                    }
                    case 1: {
                        text += this->digit(this->part | v >> 4);
                        this->part = v << 2;
                        break;
                    }
                    case 2: {
                        text += this->digit(this->part | v >> 6);
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
