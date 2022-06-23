# coding: utf-8
##############################################################################
#
# @brief Implementation of xgost-ext functions
#
# Copyright (c) 2022 CloudBEAR LLC, all rights reserved.
#
#  Permission to use, copy, modify, and/or distribute this software for any
#  purpose with or without fee is hereby granted, provided that the above
#  copyright notice and this permission notice appear in all copies.
#
#  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
#  WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
#  MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
#  ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
#  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
#  ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
#  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
#
##############################################################################

from .bext import rev8

_kul_sb = [
# noqa 0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
    [  1, 148,  32, 133,  16, 194, 192,   1, 251,   1, 192, 194,  16, 133,  32, 148],  # noqa 0
    [148, 165,  60,  68, 209, 141, 180,  84, 222, 111, 119,  93, 150, 116,  45, 132],  # noqa 1
    [132, 100,  72, 223, 211,  49, 166,  48, 224,  90,  68, 151, 202, 117, 153, 221],  # noqa 2
    [221,  13, 248,  82, 145, 100, 255, 123, 175,  61, 148, 243, 217, 208, 233,  16],  # noqa 3
    [ 16, 137,  72, 127, 145, 236,  57, 239,  16, 191,  96, 233,  48,  94, 149, 189],  # noqa 4
    [189, 162,  72, 198, 254, 235,  47, 132, 201, 173, 124,  26, 104, 190, 159,  39],  # noqa 5
    [ 39, 127, 200, 152, 243,  15,  84,   8, 246, 238,  18, 141,  47, 184, 212,  93],  # noqa 6
    [ 93,  75, 142,  96,   1,  42, 108,   9,  73, 171, 141, 203,  20, 135,  73, 184]   # noqa 7
]

_mgma_sb = [
# noqa    1   2   3   4   5   6   7   8   9   A   B   C   D   E   F
    [12,  4,  6,  2, 10,  5, 11,  9, 14,  8, 13,  7,  0,  3, 15,  1],  # noqa 0
    [ 6,  8,  2,  3,  9, 10,  5, 12,  1, 14,  4,  7, 11, 13,  0, 15],  # noqa 1
    [11,  3,  5,  8,  2, 15, 10, 13, 14,  1,  7,  4, 12,  9,  6,  0],  # noqa 2
    [12,  8,  2,  1, 13,  4, 15,  6,  7,  0, 10,  5,  3, 14,  9, 11],  # noqa 3
    [ 7, 15,  5, 10,  8,  1,  6, 13,  0,  9,  3, 14, 11,  4,  2, 12],  # noqa 4
    [ 5, 13, 15,  6,  9,  2, 12, 10, 11,  7,  8,  1,  4,  3, 14,  0],  # noqa 5
    [ 8, 14,  2,  5,  6,  9,  1, 12, 15,  4, 11,  0, 13, 10,  3,  7],  # noqa 6
    [ 1,  7, 14, 13,  0,  5,  8,  3,  4, 15, 10,  6,  9, 12, 11,  2]   # noqa 7
]

_sb_sb = [
# noqa     1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
    252, 238, 221,  17, 207, 110,  49,  22, 251, 196, 250, 218,  35, 197,   4,  77,  # noqa 0
    233, 119, 240, 219, 147,  46, 153, 186,  23,  54, 241, 187,  20, 205,  95, 193,  # noqa 1
    249,  24, 101,  90, 226,  92, 239,  33, 129,  28,  60,  66, 139,   1, 142,  79,  # noqa 2
      5, 132,   2, 174, 227, 106, 143, 160,   6,  11, 237, 152, 127, 212, 211,  31,  # noqa 3
    235,  52,  44,  81, 234, 200,  72, 171, 242,  42, 104, 162, 253,  58, 206, 204,  # noqa 4
    181, 112,  14,  86,   8,  12, 118,  18, 191, 114,  19,  71, 156, 183,  93, 135,  # noqa 5
     21, 161, 150,  41,  16, 123, 154, 199, 243, 145, 120, 111, 157, 158, 178, 177,  # noqa 6
     50, 117,  25,  61, 255,  53, 138, 126, 109,  84, 198, 128, 195, 189,  13,  87,  # noqa 7
    223, 245,  36, 169,  62, 168,  67, 201, 215, 121, 214, 246, 124,  34, 185,   3,  # noqa 8
    224,  15, 236, 222, 122, 148, 176, 188, 220, 232,  40,  80,  78,  51,  10,  74,  # noqa 9
    167, 151,  96, 115,  30,   0,  98,  68,  26, 184,  56, 130, 100, 159,  38,  65,  # noqa A
    173,  69,  70, 146,  39,  94,  85,  47, 140, 163, 165, 125, 105, 213, 149,  59,  # noqa B
      7,  88, 179,  64, 134, 172,  29, 247,  48,  55, 107, 228, 136, 217, 231, 137,  # noqa C
    225,  27, 131,  73,  76,  63, 248, 254, 141,  83, 170, 144, 202, 216, 133,  97,  # noqa D
     32, 113, 103, 164,  45,  43,   9,  91, 203, 155,  37, 208, 190, 229, 108,  82,  # noqa E
     89, 166, 116, 210, 230, 244, 180, 192, 209, 102, 175, 194,  57,  75,  99, 182   # noqa F
]

_sbi_sb = [
# noqa     1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
    165,  45,  50, 143,  14,  48,  56, 192,  84, 230, 158,  57,  85, 126,  82, 145,  # noqa 0
    100,   3,  87,  90,  28,  96,   7,  24,  33, 114, 168, 209,  41, 198, 164,  63,  # noqa 1
    224,  39, 141,  12, 130, 234, 174, 180, 154,  99,  73, 229,  66, 228,  21, 183,  # noqa 2
    200,   6, 112, 157,  65, 117,  25, 201, 170, 252,  77, 191,  42, 115, 132, 213,  # noqa 3
    195, 175,  43, 134, 167, 177, 178,  91,  70, 211, 159, 253, 212,  15, 156,  47,  # noqa 4
    155,  67, 239, 217, 121, 182,  83, 127, 193, 240,  35, 231,  37,  94, 181,  30,  # noqa 5
    162, 223, 166, 254, 172,  34, 249, 226,  74, 188,  53, 202, 238, 120,   5, 107,  # noqa 6
     81, 225,  89, 163, 242, 113,  86,  17, 106, 137, 148, 101, 140, 187, 119,  60,  # noqa 7
    123,  40, 171, 210,  49, 222, 196,  95, 204, 207, 118,  44, 184, 216,  46,  54,  # noqa 8
    219, 105, 179,  20, 149, 190,  98, 161,  59,  22, 102, 233,  92, 108, 109, 173,  # noqa 9
     55,  97,  75, 185, 227, 186, 241, 160, 133, 131, 218,  71, 197, 176,  51, 250,  # noqa A
    150, 111, 110, 194, 246,  80, 255,  93, 169, 142,  23,  27, 151, 125, 236,  88,  # noqa B
    247,  31, 251, 124,   9,  13, 122, 103,  69, 135, 220, 232,  79,  29,  78,   4,  # noqa C
    235, 248, 243,  62,  61, 189, 138, 136, 221, 205,  11,  19, 152,   2, 147, 128,  # noqa D
    144, 208,  36,  52, 203, 237, 244, 206, 153,  16,  68,  64, 146,  58,   1,  38,  # noqa E
     18,  26,  72, 104, 245, 129, 139, 199, 214,  32,  10,   8,   0,  76, 215, 116   # noqa F
]

_stbg_sb = [
    0x8e20faa72ba0b470, 0x47107ddd9b505a38, 0xad08b0e0c3282d1c, 0xd8045870ef14980e,  # noqa
    0x6c022c38f90a4c07, 0x3601161cf205268d, 0x1b8e0b0e798c13c8, 0x83478b07b2468764,  # noqa
    0xa011d380818e8f40, 0x5086e740ce47c920, 0x2843fd2067adea10, 0x14aff010bdd87508,  # noqa
    0x0ad97808d06cb404, 0x05e23c0468365a02, 0x8c711e02341b2d01, 0x46b60f011a83988e,  # noqa
    0x90dab52a387ae76f, 0x486dd4151c3dfdb9, 0x24b86a840e90f0d2, 0x125c354207487869,  # noqa
    0x092e94218d243cba, 0x8a174a9ec8121e5d, 0x4585254f64090fa0, 0xaccc9ca9328a8950,  # noqa
    0x9d4df05d5f661451, 0xc0a878a0a1330aa6, 0x60543c50de970553, 0x302a1e286fc58ca7,  # noqa
    0x18150f14b9ec46dd, 0x0c84890ad27623e0, 0x0642ca05693b9f70, 0x0321658cba93c138,  # noqa
    0x86275df09ce8aaa8, 0x439da0784e745554, 0xafc0503c273aa42a, 0xd960281e9d1d5215,  # noqa
    0xe230140fc0802984, 0x71180a8960409a42, 0xb60c05ca30204d21, 0x5b068c651810a89e,  # noqa
    0x456c34887a3805b9, 0xac361a443d1c8cd2, 0x561b0d22900e4669, 0x2b838811480723ba,  # noqa
    0x9bcf4486248d9f5d, 0xc3e9224312c8c1a0, 0xeffa11af0964ee50, 0xf97d86d98a327728,  # noqa
    0xe4fa2054a80b329c, 0x727d102a548b194e, 0x39b008152acb8227, 0x9258048415eb419d,  # noqa
    0x492c024284fbaec0, 0xaa16012142f35760, 0x550b8e9e21f7a530, 0xa48b474f9ef5dc18,  # noqa
    0x70a6a56e2440598e, 0x3853dc371220a247, 0x1ca76e95091051ad, 0x0edd37c48a08a6d8,  # noqa
    0x07e095624504536c, 0x8d70c431ac02a736, 0xc83862965601dd1b, 0x641c314b2b8ee083   # noqa
]


def _gost64_gfmul(a, b):
    res = 0
    # Replicated primitive polynomial p(x) = 1 + x + x^6 + x^7 + x^8 (0xC3)
    mask_poly = 0xC3C3C3C3C3C3C3C3
    mask_b = 0x0101010101010101
    mask_a = mask_b << 7  # 0x8080808080808080
    for _ in range(8):
        # Select LSB in each byte
        bm = (b & mask_b)
        # Extend LSB to all bits in each byte
        bm |= (bm << 1)
        bm |= (bm << 2)
        bm |= (bm << 4)
        # Add "a" to result if corresponding "b" bit is one
        res ^= a & bm
        # Go to next "b" bit
        b >>= 1
        # Select MSB in each byte
        am = (a & mask_a)
        # Clear MSB in each byte
        a ^= am
        # Shift, since MSB is clear already it doesn't propagate to next byte
        a <<= 1
        # Extend MSB to all bits in each byte
        am |= (am >> 1)
        am |= (am >> 2)
        am |= (am >> 4)
        # Substract minimal polynom from each "a" byte
        # if MSB in corresponding bit is one
        a ^= (am & mask_poly)
    return res


def _gost64_kuzn(rs1, rs2, coef=_kul_sb):
    rd = 0
    # Multiply 8x16 matrix to 16 element vector represented by rs1, rs2
    for i in range(8):
        # Pointers to row coefficients
        coef1 = 0
        for j in range(8):
            coef1 |= (coef[i][j]) << (j * 8)
        coef2 = 0
        for j in range(8):
            coef2 |= (coef[i][j + 8]) << (j * 8)
        # SIMD like dot product of two vectors
        sum = _gost64_gfmul(coef1, rs1) ^ _gost64_gfmul(coef2, rs2)
        sum ^= (sum >> 32)
        sum ^= (sum >> 16)
        sum ^= (sum >> 8)
        sum &= 0xFF
        # Put result to appropriate position
        rd |= sum << (8 * i)

    return rd


def _gostsb(rs1, rs2, xlen):
    rs1 ^= rs2
    rd = 0
    for i in range(0, xlen, 8):
        rd |= _sb_sb[(rs1 >> i) & 0xFF] << i
    return rd


def _gostsbi(rs1, rs2, xlen):
    rd = 0
    for i in range(0, xlen, 8):
        rd |= _sbi_sb[(rs1 >> i) & 0xFF] << i
    return rd ^ rs2


def gost32sb(**k):
    return _gostsb(**k)


def gost32sbi(**k):
    return _gostsbi(**k)


def gost64sb(**k):
    return _gostsb(**k)


def gost64sbi(**k):
    return _gostsbi(**k)


def gost32kuldh(rs1, rs2, xlen):
    assert xlen == 32, 'This is rv32-only function'
    return _gost64_kuzn(rs1 + rs2 * 2**32, 0) & (2**32 - 1)


def gost32kuld(rs1, rs2, xlen):
    assert xlen == 32, 'This is rv32-only function'
    return _gost64_kuzn(0, rs1 + rs2 * 2**32) & (2**32 - 1)


def gost32kule(rs1, rs2, xlen):
    assert xlen == 32, 'This is rv32-only function'
    return rev8(gost32kuldh(rev8(rs2, 32), rev8(rs1, 32), 32), 32)


def gost32kuleh(rs1, rs2, xlen):
    assert xlen == 32, 'This is rv32-only function'
    return rev8(gost32kuld(rev8(rs2, 32), rev8(rs1, 32), 32), 32)


def gost64kuld(rs1, rs2, xlen):
    assert xlen == 64, 'This is rv64-only function'
    return _gost64_kuzn(rs1, rs2)


def gost64kule(rs1, rs2, xlen):
    assert xlen == 64, 'This is rv64-only function'
    return rev8(gost64kuld(rev8(rs2, 64), rev8(rs1, 64), 64), 64)


def gost32mgma(rs1, rs2, xlen):
    assert xlen == 32, 'This is rv32-only function'
    rs1, rs2 = rev8(rs1, 32), rev8(rs2, 32)
    lo_key, g = (rs1 + rs2) & (2**32 - 1), 0
    for i in range(0, 32, 4):
        g |= _mgma_sb[i >> 2][(lo_key >> i) & 0xF] << i
    g = (g << 11) | (g >> 21)
    return rev8(g & (2**32 - 1), 32)


def gost64mgma(rs1, rs2, xlen):
    assert xlen == 64, 'This is rv64-only function'
    g = gost32mgma(rs1 >> 32, rs2 & 2**32 - 1, 32)
    g ^= rs1 & (2**32 - 1)
    return (rs1 >> 32) | (g << 32)


def _gost64stbg(rs1):
    rd = 0
    for i in range(64):
        if (rs1 >> (63 - i)) & 1:
            rd ^= _stbg_sb[i]
    rd &= (2**64 - 1)
    return rd


def gost32tau1(rs1, rs2, xlen):
    assert xlen == 32, 'This is rv32-only function'
    return ((rs1 & 0xFF) | ((rs2 & 0xFF) << 8)
            | (((rs1 >> 8) & 0xFF) << 16)
            | (((rs2 >> 8) & 0xFF) << 24))


def gost32tau2(rs1, rs2, xlen):
    return gost32tau1(rs1 >> 16, rs2 >> 16, xlen)


def gost64tau1(rs1, rs2, xlen):
    assert xlen == 64, 'This is rv64-only function'
    return (((rs1) & 0xFF)
            | (((rs1 >> 16) & 0xFF) << 8)
            | (((rs1 >> 32) & 0xFF) << 16)
            | (((rs1 >> 48) & 0xFF) << 24)
            | (((rs2 >> 00) & 0xFF) << 32)
            | (((rs2 >> 16) & 0xFF) << 40)
            | (((rs2 >> 32) & 0xFF) << 48)
            | (((rs2 >> 48) & 0xFF) << 56))


def gost64tau2(rs1, rs2, xlen):
    return gost64tau1(rs1 >> 8, rs2 >> 8, xlen)


def gost32lin1(rs1, rs2, xlen):
    assert xlen == 32, 'This is rv32-only function'
    return _gost64stbg(rs1 | rs2 << 32) & (2**xlen - 1)


def gost32lin2(rs1, rs2, xlen):
    assert xlen == 32, 'This is rv32-only function'
    return _gost64stbg(rs1 | rs2 << 32) >> 32


def gost64lin1(rs1, rs2, xlen):
    assert xlen == 64, 'This is rv64-only function'
    return _gost64stbg(gost64tau1(rs1, rs2, xlen))


def gost64lin2(rs1, rs2, xlen):
    assert xlen == 64, 'This is rv64-only function'
    return _gost64stbg(gost64tau2(rs1, rs2, xlen))
