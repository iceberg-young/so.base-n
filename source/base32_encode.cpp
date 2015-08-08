/**
 * @copyright 2015 Iceberg YOUNG
 * @license GNU Lesser General Public License version 3
 */

#include "base-n.hpp"
#include "base_codec.hpp"

namespace so {
    namespace {
        const char* base32_alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ" "234567";
        const char* base32hex_alphabet = "0123456789" "ABCDEFGHIJKLMNOPQRSTUV";

        class base32_encode :
          public base_encode {
         public:
            base32_encode(bool hex, bool padding) :
              alphabet(hex ? base32hex_alphabet : base32_alphabet),
              padding(padding),
              part(0),
              step(4) {}

         protected:
            void complete(std::string& text) final override {
                if (this->step != 4) {
                    text += this->digit(this->part);
                    if (this->padding) {
                        text.append(8 - text.size() % 8, '=');
                    }
                }
            }

            size_t estimate(size_t data) const final override {
                return (data + 4) / 5 * 8;
            }

            void push(uint8_t v, std::string& text) {
                switch (++this->step %= 5) {
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

         private:
            char digit(uint8_t value) {
                return this->alphabet[value & 0x1F];
            }

         private:
            const char* alphabet;
            const bool padding;

            uint8_t part;
            uint8_t step;
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
