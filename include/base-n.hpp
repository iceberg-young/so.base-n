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
        static std::string decode_text(const std::string& text);

        static std::vector<uint8_t> decode(const std::string& text);

     public:
        static std::string encode(const std::string& data, bool padding = true);

        static std::string encode(const std::vector<uint8_t>& data, bool padding = true);

     public:
        static std::string to_base64url(const std::string& text);
    };

    // Base 64 encoding with URL and filename safe alphabet.
    class base64url :
      public base64 /* Borrow decoders. */ {
     public:
        static std::string encode(const std::string& data, bool padding = false);

        static std::string encode(const std::vector<uint8_t>& data, bool padding = false);

     public:
        static std::string to_base64(const std::string& text);
    };

    // Base 32 encoding.
    class base32 {
     public:
        static std::string decode_text(const std::string& text);

        static std::vector<uint8_t> decode(const std::string& text);

     public:
        static std::string encode(const std::string& data, bool padding = true);

        static std::string encode(const std::vector<uint8_t>& data, bool padding = true);

     public:
        static std::string to_base32hex(const std::string& text);
    };

    // Base 32 encoding with extended hex alphabet.
    class base32hex {
     public:
        static std::string decode_text(const std::string& text);

        static std::vector<uint8_t> decode(const std::string& text);

     public:
        static std::string encode(const std::string& data, bool padding = true);

        static std::string encode(const std::vector<uint8_t>& data, bool padding = true);

     public:
        static std::string to_base32(const std::string& text);
    };

    // Base 16 encoding.
    //using base16 = base_n<base_variety::base16>;
    class base16 {
     public:
        static std::string decode_text(const std::string& text);

        static std::vector<uint8_t> decode(const std::string& text);

     public:
        static std::string encode(const std::string& data);

        static std::string encode(const std::vector<uint8_t>& data);
    };
}
