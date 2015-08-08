/**
 * @copyright 2015 Iceberg YOUNG
 * @license GNU Lesser General Public License version 3
 */

#pragma once

namespace so {
    class base_decode {
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
        virtual size_t estimate(size_t text) const = 0;

        virtual bool pop(char c, uint8_t& v) = 0;
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
