/**
 * @copyright 2015 Iceberg YOUNG
 * @license GNU Lesser General Public License version 3
 */
#pragma once

#include <string>
#include <vector>

namespace so {
    // Base 64 encoding.
    class base64 {
     public:
        static constexpr uint8_t digit_mask = 0x3F;
        static constexpr int bytes_per_unit = 3;
        static constexpr int digits_per_unit = 4;

     public:
        static std::string decode_text(const std::string& text, bool liberal = false);

        static std::vector<uint8_t> decode(const std::string& text, bool liberal = false);

     public:
        static std::string encode(const std::string& data, bool padding = true);

        static std::string encode(const std::vector<uint8_t>& data, bool padding = true);
    };

    // Base 64 encoding with URL and filename safe alphabet.
    class base64url {
     public:
        static std::string decode_text(const std::string& text, bool liberal = false);

        static std::vector<uint8_t> decode(const std::string& text, bool liberal = false);

     public:
        static std::string encode(const std::string& data, bool padding = false);

        static std::string encode(const std::vector<uint8_t>& data, bool padding = false);
    };

    // Base 32 encoding.
    class base32 {
     public:
        static constexpr uint8_t digit_mask = 0x1F;
        static constexpr int bytes_per_unit = 5;
        static constexpr int digits_per_unit = 8;

     public:
        static std::string decode_text(const std::string& text, bool liberal = false);

        static std::vector<uint8_t> decode(const std::string& text, bool liberal = false);

     public:
        static std::string encode(const std::string& data, bool padding = true);

        static std::string encode(const std::vector<uint8_t>& data, bool padding = true);
    };

    // Base 32 encoding with extended hex alphabet.
    class base32hex {
     public:
        static std::string decode_text(const std::string& text, bool liberal = false);

        static std::vector<uint8_t> decode(const std::string& text, bool liberal = false);

     public:
        static std::string encode(const std::string& data, bool padding = true);

        static std::string encode(const std::vector<uint8_t>& data, bool padding = true);
    };

    // Base 16 encoding.
    class base16 {
     public:
        static constexpr uint8_t digit_mask = 0x0F;
        static constexpr int bytes_per_unit = 1;
        static constexpr int digits_per_unit = 2;

     public:
        static std::string decode_text(const std::string& text, bool liberal = false);

        static std::vector<uint8_t> decode(const std::string& text, bool liberal = false);

     public:
        static std::string encode(const std::string& data);

        static std::string encode(const std::vector<uint8_t>& data);
    };
}
