/****************************************************************************
 *
 *  RISC-V "Zkg" extension proposal intrinsics and emulation
 *
 *  Copyright (C) 2021  Mark Fedorov <mark.fedorov@cloudbear.ru>
 *
 *  Permission to use, copy, modify, and/or distribute this software for any
 *  purpose with or without fee is hereby granted, provided that the above
 *  copyright notice and this permission notice appear in all copies.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *  WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *  ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *  ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 ****************************************************************************/

#ifndef RVINTRINXGOST_H
#define RVINTRINXGOST_H

#ifndef __RVINTRIN_H__
#error Never use <rvzkgintrin.h> directly; include <rvintrin.h> instead.
#endif

#include <stdint.h>
#include <stddef.h>

#if __riscv_zkg && __riscv_xlen == 64
#define DECLARE_INTRIN_R(insn)  static inline int64_t __rv_##insn(int64_t rs1) \
    { int64_t rd; __asm__(#insn " %0, %1"     : "=r"(rd) : "r"(rs1)          ); return rd; }
#define DECLARE_INTRIN_RR(insn) static inline int64_t __rv_##insn(int64_t rs1, int64_t rs2) \
    { int64_t rd; __asm__(#insn " %0, %1, %2" : "=r"(rd) : "r"(rs1), "r"(rs2)); return rd; }
DECLARE_INTRIN_RR(gost64kul)
DECLARE_INTRIN_RR(gost64kuli)
DECLARE_INTRIN_RR(gost64kuh)
DECLARE_INTRIN_RR(gost64kuhi)
DECLARE_INTRIN_RR(gost64mgma)
DECLARE_INTRIN_R(gost64sb)
DECLARE_INTRIN_R(gost64sbi)
DECLARE_INTRIN_R(gost64stbg)
#undef DECLARE_INTRIN_R
#undef DECLARE_INTRIN_RR
#else // ^^^ __riscv_zkg ^^^ | vvv !__riscv_zkg vvv

static inline int64_t __rv_gost64sb(int64_t rs1) {
    static const uint8_t sbox[256] = {
        252, 238, 221,  17, 207, 110,  49,  22, 251, 196, 250, 218,  35, 197,   4,  77,
        233, 119, 240, 219, 147,  46, 153, 186,  23,  54, 241, 187,  20, 205,  95, 193,
        249,  24, 101,  90, 226,  92, 239,  33, 129,  28,  60,  66, 139,   1, 142,  79,
          5, 132,   2, 174, 227, 106, 143, 160,   6,  11, 237, 152, 127, 212, 211,  31,
        235,  52,  44,  81, 234, 200,  72, 171, 242,  42, 104, 162, 253,  58, 206, 204,
        181, 112,  14,  86,   8,  12, 118,  18, 191, 114,  19,  71, 156, 183,  93, 135,
         21, 161, 150,  41,  16, 123, 154, 199, 243, 145, 120, 111, 157, 158, 178, 177,
         50, 117,  25,  61, 255,  53, 138, 126, 109,  84, 198, 128, 195, 189,  13,  87,
        223, 245,  36, 169,  62, 168,  67, 201, 215, 121, 214, 246, 124,  34, 185,   3,
        224,  15, 236, 222, 122, 148, 176, 188, 220, 232,  40,  80,  78,  51,  10,  74,
        167, 151,  96, 115,  30,   0,  98,  68,  26, 184,  56, 130, 100, 159,  38,  65,
        173,  69,  70, 146,  39,  94,  85,  47, 140, 163, 165, 125, 105, 213, 149,  59,
          7,  88, 179,  64, 134, 172,  29, 247,  48,  55, 107, 228, 136, 217, 231, 137,
        225,  27, 131,  73,  76,  63, 248, 254, 141,  83, 170, 144, 202, 216, 133,  97,
         32, 113, 103, 164,  45,  43,   9,  91, 203, 155,  37, 208, 190, 229, 108,  82,
         89, 166, 116, 210, 230, 244, 180, 192, 209, 102, 175, 194,  57,  75,  99, 182,
    };
    int64_t rd = 0;
    for (size_t i = 0; i < 64; i += 8)
        rd |= (uint64_t)sbox[(rs1 >> i) & 0xFF] << i;
    return rd;
}

static inline int64_t __rv_gost64sbi(int64_t rs1) {
    static const uint8_t sbox[256] = {
        165,  45,  50, 143,  14,  48,  56, 192,  84, 230, 158,  57,  85, 126,  82, 145,
        100,   3,  87,  90,  28,  96,   7,  24,  33, 114, 168, 209,  41, 198, 164,  63,
        224,  39, 141,  12, 130, 234, 174, 180, 154,  99,  73, 229,  66, 228,  21, 183,
        200,   6, 112, 157,  65, 117,  25, 201, 170, 252,  77, 191,  42, 115, 132, 213,
        195, 175,  43, 134, 167, 177, 178,  91,  70, 211, 159, 253, 212,  15, 156,  47,
        155,  67, 239, 217, 121, 182,  83, 127, 193, 240,  35, 231,  37,  94, 181,  30,
        162, 223, 166, 254, 172,  34, 249, 226,  74, 188,  53, 202, 238, 120,   5, 107,
         81, 225,  89, 163, 242, 113,  86,  17, 106, 137, 148, 101, 140, 187, 119,  60,
        123,  40, 171, 210,  49, 222, 196,  95, 204, 207, 118,  44, 184, 216,  46,  54,
        219, 105, 179,  20, 149, 190,  98, 161,  59,  22, 102, 233,  92, 108, 109, 173,
         55,  97,  75, 185, 227, 186, 241, 160, 133, 131, 218,  71, 197, 176,  51, 250,
        150, 111, 110, 194, 246,  80, 255,  93, 169, 142,  23,  27, 151, 125, 236,  88,
        247,  31, 251, 124,   9,  13, 122, 103,  69, 135, 220, 232,  79,  29,  78,   4,
        235, 248, 243,  62,  61, 189, 138, 136, 221, 205,  11,  19, 152,   2, 147, 128,
        144, 208,  36,  52, 203, 237, 244, 206, 153,  16,  68,  64, 146,  58,   1,  38,
         18,  26,  72, 104, 245, 129, 139, 199, 214,  32,  10,   8,   0,  76, 215, 116,
    };
    int64_t rd = 0;
    for (size_t i = 0; i < 64; i += 8)
        rd |= (uint64_t)sbox[(rs1 >> i) & 0xFF] << i;
    return rd;
}

// SIMD-like multiplication of GF(2^8) vectors
static inline uint64_t __rv_gost64_gfmul(uint64_t a, uint64_t b) {
    uint64_t res = 0;
    // Replicated primitive polynomial p(x) = 1 + x + x^6 + x^7 + x^8 (0xC3)
    uint64_t mask_poly = 0xC3C3C3C3C3C3C3C3;
    uint64_t mask_b = 0x0101010101010101;
    uint64_t mask_a = mask_b << 7; // 0x8080808080808080
    uint64_t bm;
    uint64_t am;
    for (size_t i = 0; i < 8; ++i) {
        // Select LSB in each byte
        bm = (b & mask_b);
        // Extend LSB to all bits in each byte
        bm |= (bm << 1);
        bm |= (bm << 2);
        bm |= (bm << 4);
        // Add "a" to result if corresponding "b" bit is one
        res ^= a & bm;
        // Go to next "b" bit
        b >>= 1;
        // Select MSB in each byte
        am = (a & mask_a);
        // Clear MSB in each byte
        a ^= am;
        // Shift, since MSB is clear already it doesn't propagate to next byte
        a <<= 1;
        // Extend MSB to all bits in each byte
        am |= (am >> 1);
        am |= (am >> 2);
        am |= (am >> 4);
        // Substract minimal polynom from each "a" byte if MSB in corresponding bit is one
        a ^= (am & mask_poly);
    }
    return res;
}

static inline int64_t __rv_gost64_kuzn(uint8_t coef[8][16], int64_t rs1, int64_t rs2) {
    int64_t rd = 0;
    uint64_t sum;
    uint64_t *coef1;
    uint64_t *coef2;
    // Multiply 8x16 matrix to 16 element vector represented by rs1, rs2
    for (size_t i = 0; i < 8; ++i) {
        // Pointers to row coefficients
        coef1 = (uint64_t*) &coef[i];
        coef2 = coef1 + 1;
        // SIMD like dot product of two vectors
        sum = __rv_gost64_gfmul(*coef1, rs1) ^ __rv_gost64_gfmul(*coef2, rs2);
        sum ^= (sum >> 32);
        sum ^= (sum >> 16);
        sum ^= (sum >> 8);
        sum &= 0xFF;
        // Put result to appropriate position
        rd |= sum << (8 * i);
    }
    return rd;
}

static inline int64_t __rv_gost64kul(int64_t rs1, int64_t rs2) {
    static uint8_t coef[8][16] = {
        {  1, 148,  32, 133,  16, 194, 192,   1, 251,   1, 192, 194,  16, 133,  32, 148},
        {148, 165,  60,  68, 209, 141, 180,  84, 222, 111, 119,  93, 150, 116,  45, 132},
        {132, 100,  72, 223, 211,  49, 166,  48, 224,  90,  68, 151, 202, 117, 153, 221},
        {221,  13, 248,  82, 145, 100, 255, 123, 175,  61, 148, 243, 217, 208, 233,  16},
        { 16, 137,  72, 127, 145, 236,  57, 239,  16, 191,  96, 233,  48,  94, 149, 189},
        {189, 162,  72, 198, 254, 235,  47, 132, 201, 173, 124,  26, 104, 190, 159,  39},
        { 39, 127, 200, 152, 243,  15,  84,   8, 246, 238,  18, 141,  47, 184, 212,  93},
        { 93,  75, 142,  96,   1,  42, 108,   9,  73, 171, 141, 203,  20, 135,  73, 184},
    };
    return __rv_gost64_kuzn(coef, rs1, rs2);
}

static inline int64_t __rv_gost64kuh(int64_t rs1, int64_t rs2) {
    static uint8_t coef[8][16] = {
        {184, 110,  42, 212, 177,  55, 175, 212, 190, 241,  46, 187,  26,  78, 230, 122},
        {122,  22, 245,  82, 120, 153, 235, 213, 231, 196,  45,   6,  23,  98, 213,  72},
        { 72, 195,   2,  14,  88, 144, 225, 163, 110, 175, 188, 197,  12, 236, 118, 108},
        {108,  76, 221, 101,   1, 196, 212, 141, 164,   2, 235,  32, 202, 107, 242, 114},
        {114, 232,  20,   7,  73, 246, 215, 166, 106, 214,  17,  28,  12,  16,  51, 118},
        {118, 227,  48, 159, 107,  48,  99, 161,  43,  28,  67, 104, 112, 135, 200, 162},
        {162, 208,  68, 134,  45, 184, 100, 193, 156, 137,  72, 144, 218, 198,  32, 110},
        {110,  77, 142, 234, 169, 246, 191,  10, 243, 242, 142, 147, 191, 116, 152, 207},
    };
    return __rv_gost64_kuzn(coef, rs1, rs2);
}

static inline int64_t __rv_gost64kuli(int64_t rs1, int64_t rs2) {
    static uint8_t coef[8][16] = {
        {207, 152, 116, 191, 147, 142, 242, 243,  10, 191, 246, 169, 234, 142,  77, 110},
        {110,  32, 198, 218, 144,  72, 137, 156, 193, 100, 184,  45, 134,  68, 208, 162},
        {162, 200, 135, 112, 104,  67,  28,  43, 161,  99,  48, 107, 159,  48, 227, 118},
        {118,  51,  16,  12,  28,  17, 214, 106, 166, 215, 246,  73,   7,  20, 232, 114},
        {114, 242, 107, 202,  32, 235,   2, 164, 141, 212, 196,   1, 101, 221,  76, 108},
        {108, 118, 236,  12, 197, 188, 175, 110, 163, 225, 144,  88,  14,   2, 195,  72},
        { 72, 213,  98,  23,   6,  45, 196, 231, 213, 235, 153, 120,  82, 245,  22, 122},
        {122, 230,  78,  26, 187,  46, 241, 190, 212, 175,  55, 177, 212,  42, 110, 184},
    };
    return __rv_gost64_kuzn(coef, rs1, rs2);
}

static inline int64_t __rv_gost64kuhi(int64_t rs1, int64_t rs2) {
    static uint8_t coef[8][16] = {
        {184,  73, 135,  20, 203, 141, 171,  73,   9, 108,  42,   1,  96, 142,  75,  93},
        { 93, 212, 184,  47, 141,  18, 238, 246,   8,  84,  15, 243, 152, 200, 127,  39},
        { 39, 159, 190, 104,  26, 124, 173, 201, 132,  47, 235, 254, 198,  72, 162, 189},
        {189, 149,  94,  48, 233,  96, 191,  16, 239,  57, 236, 145, 127,  72, 137,  16},
        { 16, 233, 208, 217, 243, 148,  61, 175, 123, 255, 100, 145,  82, 248,  13, 221},
        {221, 153, 117, 202, 151,  68,  90, 224,  48, 166,  49, 211, 223,  72, 100, 132},
        {132,  45, 116, 150,  93, 119, 111, 222,  84, 180, 141, 209,  68,  60, 165, 148},
        {148,  32, 133,  16, 194, 192,   1, 251,   1, 192, 194,  16, 133,  32, 148,   1},
    };
    return __rv_gost64_kuzn(coef, rs1, rs2);
}

static inline int64_t __rv_gost64mgma(int64_t rs1, int64_t rs2) {
    static uint8_t sbox[8][16] = {
        {12,  4,  6,  2, 10,  5, 11,  9, 14,  8, 13,  7,  0,  3, 15,  1},
        { 6,  8,  2,  3,  9, 10,  5, 12,  1, 14,  4,  7, 11, 13,  0, 15},
        {11,  3,  5,  8,  2, 15, 10, 13, 14,  1,  7,  4, 12,  9,  6,  0},
        {12,  8,  2,  1, 13,  4, 15,  6,  7,  0, 10,  5,  3, 14,  9, 11},
        { 7, 15,  5, 10,  8,  1,  6, 13,  0,  9,  3, 14, 11,  4,  2, 12},
        { 5, 13, 15,  6,  9,  2, 12, 10, 11,  7,  8,  1,  4,  3, 14,  0},
        { 8, 14,  2,  5,  6,  9,  1, 12, 15,  4, 11,  0, 13, 10,  3,  7},
        { 1,  7, 14, 13,  0,  5,  8,  3,  4, 15, 10,  6,  9, 12, 11,  2},
    };
    uint32_t lo_key;
    uint32_t t = 0;
    uint32_t g;
    lo_key = (uint32_t)rs1 + (uint32_t)rs2;
    for (size_t i = 0; i < 32; i += 4)
        t |= (uint32_t)sbox[i >> 2][(lo_key >> i) & 0xF] << i;
    g = (t << 11) | (t >> 21);
    g ^= (uint32_t)(rs1 >> 32);
    return (rs1 << 32) | g;
}

static inline int64_t __rv_gost64stbg(int64_t rs1) {
    static uint64_t mat[64] = {
        0x8e20faa72ba0b470ull, 0x47107ddd9b505a38ull, 0xad08b0e0c3282d1cull, 0xd8045870ef14980eull,
        0x6c022c38f90a4c07ull, 0x3601161cf205268dull, 0x1b8e0b0e798c13c8ull, 0x83478b07b2468764ull,
        0xa011d380818e8f40ull, 0x5086e740ce47c920ull, 0x2843fd2067adea10ull, 0x14aff010bdd87508ull,
        0x0ad97808d06cb404ull, 0x05e23c0468365a02ull, 0x8c711e02341b2d01ull, 0x46b60f011a83988eull,
        0x90dab52a387ae76full, 0x486dd4151c3dfdb9ull, 0x24b86a840e90f0d2ull, 0x125c354207487869ull,
        0x092e94218d243cbaull, 0x8a174a9ec8121e5dull, 0x4585254f64090fa0ull, 0xaccc9ca9328a8950ull,
        0x9d4df05d5f661451ull, 0xc0a878a0a1330aa6ull, 0x60543c50de970553ull, 0x302a1e286fc58ca7ull,
        0x18150f14b9ec46ddull, 0x0c84890ad27623e0ull, 0x0642ca05693b9f70ull, 0x0321658cba93c138ull,
        0x86275df09ce8aaa8ull, 0x439da0784e745554ull, 0xafc0503c273aa42aull, 0xd960281e9d1d5215ull,
        0xe230140fc0802984ull, 0x71180a8960409a42ull, 0xb60c05ca30204d21ull, 0x5b068c651810a89eull,
        0x456c34887a3805b9ull, 0xac361a443d1c8cd2ull, 0x561b0d22900e4669ull, 0x2b838811480723baull,
        0x9bcf4486248d9f5dull, 0xc3e9224312c8c1a0ull, 0xeffa11af0964ee50ull, 0xf97d86d98a327728ull,
        0xe4fa2054a80b329cull, 0x727d102a548b194eull, 0x39b008152acb8227ull, 0x9258048415eb419dull,
        0x492c024284fbaec0ull, 0xaa16012142f35760ull, 0x550b8e9e21f7a530ull, 0xa48b474f9ef5dc18ull,
        0x70a6a56e2440598eull, 0x3853dc371220a247ull, 0x1ca76e95091051adull, 0x0edd37c48a08a6d8ull,
        0x07e095624504536cull, 0x8d70c431ac02a736ull, 0xc83862965601dd1bull, 0x641c314b2b8ee083ull,
    };
    int64_t rd = 0;
    for (size_t i = 0; i < 64; ++i) {
        if ((rs1 >> (63 - i)) & 1) {
            rd ^= mat[i];
        }
    }
    return rd;
}

#endif //!__riscv_zkg
#endif //RVINTRINXGOST_H
