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

    template<class variety_t>
    class base_decode {
     public:
        base_decode() :
          part(0),
          step(-1) {}

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
              * bytes_per_unit<variety_t>()
              / digits_per_unit<variety_t>();
        }

        uint8_t forward() {
            return ++this->step %= digits_per_unit<variety_t>();
        }

        virtual bool pop(char c, uint8_t& v) = 0;

     protected:
        uint8_t part;
        uint8_t step;
    };

    class base_encode {
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
        virtual void complete(std::string& text) = 0;

        virtual size_t estimate(size_t data) const = 0;

        virtual void push(uint8_t v, std::string& text) = 0;
    };
}
