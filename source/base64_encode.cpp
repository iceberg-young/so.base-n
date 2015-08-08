/**
 * @copyright 2015 Iceberg YOUNG
 * @license GNU Lesser General Public License version 3
 */

#include "base-n.hpp"
#include "base_codec.hpp"

namespace so {
    namespace {
        const char* base64_alphabet = ""
          "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
          "abcdefghijklmnopqrstuvwxyz"
          "0123456789"
          "+/";
        const char* base64url_alphabet = ""
          "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
          "abcdefghijklmnopqrstuvwxyz"
          "0123456789"
          "-_";

        class base64_encode :
          public base_encode {
         public:
            base64_encode(bool url, bool padding) :
              alphabet(url ? base64url_alphabet : base64_alphabet),
              padding(padding),
              part(0),
              step(2) {}

         protected:
            void complete(std::string& text) final override {
                if (this->step != 2) {
                    text += this->digit(this->part);
                    if (this->padding) {
                        text += this->step ? "=" : "==";
                    }
                }
            }

            size_t estimate(size_t data) const final override {
                return (data + 2) / 3 * 4;
            }

            void push(uint8_t v, std::string& text) {
                switch (++this->step %= 3) {
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

         private:
            char digit(uint8_t value) {
                return this->alphabet[value & 0x3F];
            }

         private:
            const char* alphabet;
            const bool padding;

            uint8_t part;
            uint8_t step;
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
