/**
 * @copyright 2015 Iceberg YOUNG
 * @license GNU Lesser General Public License version 3
 */

#pragma once

namespace so {
    template<typename base_t>
    constexpr size_t bytes_per_unit();

    template<>
    constexpr size_t bytes_per_unit<base64>() {
        return 3;
    }

    template<>
    constexpr size_t bytes_per_unit<base32>() {
        return 5;
    }

    template<>
    constexpr size_t bytes_per_unit<base16>() {
        return 1;
    }

    template<typename base_t>
    constexpr size_t digits_per_unit();

    template<>
    constexpr size_t digits_per_unit<base64>() {
        return 4;
    }

    template<>
    constexpr size_t digits_per_unit<base32>() {
        return 8;
    }

    template<>
    constexpr size_t digits_per_unit<base16>() {
        return 2;
    }

    template<typename base_t>
    constexpr uint8_t mask_per_digit();

    template<>
    constexpr uint8_t mask_per_digit<base64>() {
        return 0x3F;
    }

    template<>
    constexpr uint8_t mask_per_digit<base32>() {
        return 0x1F;
    }

    template<>
    constexpr uint8_t mask_per_digit<base16>() {
        return 0x0F;
    }

    class base_codec {
     public:
        base_codec() :
          part(0),
          step(-1) {}

     protected:
        uint8_t part;
        uint8_t step;
    };

    template<class base_t>
    class base_decode :
      public base_codec {
     public:
        template<typename data_t>
        data_t decode(const std::string& text) {
            data_t data;
            data.reserve(this->estimate(text.size()));
            for (char c : text) {
                uint8_t v;
                if (this->pop(c, v)) {
                    data.push_back(v);
                }
            }
            return data;
        }

     protected:
        constexpr size_t estimate(size_t text) const {
            return text
              * bytes_per_unit<base_t>()
              / digits_per_unit<base_t>();
        }

        uint8_t forward() {
            return ++this->step %= digits_per_unit<base_t>();
        }

     protected:
        virtual bool pop(char c, uint8_t& v) = 0;
    };

    template<class base_t>
    class base_encode :
      public base_codec {
     public:
        base_encode(const char* alphabet, bool padding) :
          alphabet(alphabet),
          padding(padding) {}

     public:
        template<typename data_t>
        std::string encode(const data_t& data) {
            std::string text;
            text.reserve(this->estimate(data.size()));
            for (uint8_t b : data) {
                this->push(b, text);
            }
            this->complete(text);
            return text;
        }

     protected:
        void complete(std::string& text) {
            if (this->forward()) {
                text += this->digit(this->part);
                if (this->padding) {
                    auto dpu = digits_per_unit<base_t>();
                    text.append(dpu - text.size() % dpu, '=');
                }
            }
        }

        char digit(uint8_t value) {
            return this->alphabet[value & mask_per_digit<base_t>()];
        }

        constexpr size_t estimate(size_t data) const {
            return (data + bytes_per_unit<base_t>() - 1)
              / bytes_per_unit<base_t>()
              * digits_per_unit<base_t>();
        }

        uint8_t forward() {
            return ++this->step %= bytes_per_unit<base_t>();
        }

     protected:
        virtual void push(uint8_t v, std::string& text) = 0;

     protected:
        const char* alphabet;
        const bool padding;
    };
}
