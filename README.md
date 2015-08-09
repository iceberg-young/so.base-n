so.base-n
=========

Decode/encode [RFC 4648] described `base64`, `base64url`, `base32`, `base32hex`,
and `base16` text.


API
---

See [base-n.hpp](include/base-n.hpp).

- Decode data from a base-*n* string.

  ```cpp
  so::base64::decode(std::string text, bool liberal) -> std::vector<uint8_t>
  so::base64url::decode(std::string text, bool liberal) -> std::vector<uint8_t>
  so::base32::decode(std::string text, bool liberal) -> std::vector<uint8_t>
  so::base32hex::decode(std::string text, bool liberal) -> std::vector<uint8_t>
  so::base16::decode(std::string text, bool liberal) -> std::vector<uint8_t>
  ```

  > **Tip!**
  > Turn `liberal` mode on will ignore invalid characters.
  > (*Include incomplete/incorrect padding sequence.*)

- Encode data into a base-*n* string.

  ```cpp
  so::base64::encode(std::vector<uint8_t> data, bool padding) -> std::string
  so::base64url::encode(std::vector<uint8_t> data, bool padding) -> std::string
  so::base32::encode(std::vector<uint8_t> data, bool padding) -> std::string
  so::base32hex::encode(std::vector<uint8_t> data, bool padding) -> std::string
  so::base16::encode(std::vector<uint8_t> data, bool padding) -> std::string
  ```

  > **Note!**
  > `base64url` turns padding off *by default*.

- Corresponding functions to play with `string` data.

  ```cpp
  so::base64::decode_text(std::string text, bool liberal) -> std::string
  so::base64url::decode_text(std::string text, bool liberal) -> std::string
  so::base32::decode_text(std::string text, bool liberal) -> std::string
  so::base32hex::decode_text(std::string text, bool liberal) -> std::string
  so::base16::decode_text(std::string text, bool liberal) -> std::string
  ```
  ```cpp
  so::base64::encode(std::string data, bool padding) -> std::string
  so::base64url::encode(std::string data, bool padding) -> std::string
  so::base32::encode(std::string data, bool padding) -> std::string
  so::base32hex::encode(std::string data, bool padding) -> std::string
  so::base16::encode(std::string data, bool padding) -> std::string
  ```

  > **Note!**
  > These functions are not preferred *by semantics*.
  > And Use with caution when the system has a non-trivial `char`.


Implementation Defined Behavior
-------------------------------

Decode functions will **not stop** at the end of padding sequence.
Means concatenate text can be decoded in one call. E.g.

```cpp
std::cout << base64::decode_text("Zm9vYmE=Zm9vYg==Zm8=Zg==");
```
> ```
> foobafoobfof
> ```

See http://stackoverflow.com/a/26632221 for reference.


License
-------
![LGPLv3]

Copyright (C) 2015  Iceberg YOUNG

This program is free software: you can redistribute it and/or modify it
under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.


---

[RFC 4648]: http://tools.ietf.org/html/rfc4648
"The Base16, Base32, and Base64 Data Encodings"

[LGPLv3]: http://www.gnu.org/graphics/lgplv3-88x31.png
"GNU Lesser General Public License version 3"
