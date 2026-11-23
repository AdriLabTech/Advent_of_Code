// MD5 mínimo (RFC 1321) para no depender de librerías externas. Solo se usa en 2015 día 4.
#pragma once

#include <array>
#include <cmath>
#include <cstdint>
#include <string>
#include <vector>

namespace aoc {

inline std::array<std::uint8_t, 16> md5(const std::string& data) {
    static constexpr int S[64] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 5, 9,  14, 20, 5, 9,
                                  14, 20, 5, 9,  14, 20, 5, 9,  14, 20, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
                                  4, 11, 16, 23, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};
    // K[i] = floor(2^32 * abs(sin(i + 1))); se calcula una sola vez
    static const std::array<std::uint32_t, 64> k = [] {
        std::array<std::uint32_t, 64> t{};
        for (int i = 0; i < 64; ++i) t[i] = static_cast<std::uint32_t>(std::fabs(std::sin(i + 1.0)) * 4294967296.0);
        return t;
    }();
    std::uint32_t a0 = 0x67452301, b0 = 0xefcdab89, c0 = 0x98badcfe, d0 = 0x10325476;

    // relleno: 0x80, ceros y longitud en bits (64 bits little endian)
    std::vector<std::uint8_t> msg(data.begin(), data.end());
    msg.push_back(0x80);
    while (msg.size() % 64 != 56) msg.push_back(0);
    std::uint64_t bits = static_cast<std::uint64_t>(data.size()) * 8;
    for (int i = 0; i < 8; ++i) msg.push_back(static_cast<std::uint8_t>(bits >> (8 * i)));

    for (std::size_t off = 0; off < msg.size(); off += 64) {
        std::uint32_t m[16];
        for (int i = 0; i < 16; ++i)
            m[i] = msg[off + 4 * i] | (msg[off + 4 * i + 1] << 8) | (msg[off + 4 * i + 2] << 16) |
                   (static_cast<std::uint32_t>(msg[off + 4 * i + 3]) << 24);
        std::uint32_t a = a0, b = b0, c = c0, d = d0;
        for (int i = 0; i < 64; ++i) {
            std::uint32_t f;
            int g;
            if (i < 16) { f = (b & c) | (~b & d); g = i; }
            else if (i < 32) { f = (d & b) | (~d & c); g = (5 * i + 1) % 16; }
            else if (i < 48) { f = b ^ c ^ d; g = (3 * i + 5) % 16; }
            else { f = c ^ (b | ~d); g = (7 * i) % 16; }
            f += a + k[i] + m[g];
            a = d; d = c; c = b;
            b += (f << S[i]) | (f >> (32 - S[i]));
        }
        a0 += a; b0 += b; c0 += c; d0 += d;
    }

    std::array<std::uint8_t, 16> out{};
    const std::uint32_t v[4] = {a0, b0, c0, d0};
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j) out[i * 4 + j] = static_cast<std::uint8_t>(v[i] >> (8 * j));
    return out;
}

}  // namespace aoc
