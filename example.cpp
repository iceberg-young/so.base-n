#include "include/base-n.hpp"
#include <iostream>

using namespace so;
using namespace std;

void test(const std::string& a, const std::string& b) {
    cerr << (a == b ? '.' : 'F');
}

void test_base64(const std::string& a, const std::string& b) {
    test(base64::encode(a), b);
    test(base64::decode_text(b), a);
}

void test_base32(const std::string& a, const std::string& b) {
    test(base32::encode(a), b);
    test(base32::decode_text(b), a);
}

void test_base32hex(const std::string& a, const std::string& b) {
    test(base32hex::encode(a), b);
    test(base32hex::decode_text(b), a);
}

void test_base16(const std::string& a, const std::string& b) {
    test(base16::encode(a), b);
    test(base16::decode_text(b), a);
}

int main() {
    test_base64("", "");
    test_base64("f", "Zg==");
    test_base64("fo", "Zm8=");
    test_base64("foo", "Zm9v");
    test_base64("foob", "Zm9vYg==");
    test_base64("fooba", "Zm9vYmE=");
    test_base64("foobar", "Zm9vYmFy");

    test_base32("", "");
    test_base32("f", "MY======");
    test_base32("fo", "MZXQ====");
    test_base32("foo", "MZXW6===");
    test_base32("foob", "MZXW6YQ=");
    test_base32("fooba", "MZXW6YTB");
    test_base32("foobar", "MZXW6YTBOI======");

    test_base32hex("", "");
    test_base32hex("f", "CO======");
    test_base32hex("fo", "CPNG====");
    test_base32hex("foo", "CPNMU===");
    test_base32hex("foob", "CPNMUOG=");
    test_base32hex("fooba", "CPNMUOJ1");
    test_base32hex("foobar", "CPNMUOJ1E8======");

    test_base16("", "");
    test_base16("f", "66");
    test_base16("fo", "666F");
    test_base16("foo", "666F6F");
    test_base16("foob", "666F6F62");
    test_base16("fooba", "666F6F6261");
    test_base16("foobar", "666F6F626172");

    return 0;
}
