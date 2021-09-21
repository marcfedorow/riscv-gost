/****************************************************************************
 *
 *  RISC-V intrinsics top-level header file.
 *
 *  https://github.com/riscv/riscv-bitmanip/issues/29#issuecomment-505177062
 *     "the idea is put in all intrinsics in one file, and conditionalize
 *      them based on enabled extensions, similar to x86intrin.h."
 *  Thus rvintrin.h only has some common defines, and includes specific
 *      intrinsic files (nameing scheme: rvEXTintrin.h). This files should
 *      NOT be included separately. Consider including this file instead.
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

#ifndef __RVINTRIN_H__
#define __RVINTRIN_H__

// Bitmanip intrinsics (Zba, Zbb, Zbc, Zbs) are not implemented.
// Bitmanip spec ver. 1.0.0. does not require any of them.
// There are some reasons not to implement them:
//   > Redundantness: all these functions have their machine descriptions --
//     because they are simple enough for compiler to emit them.
//   > Readability: e.g. a | ~b is more readable than __rv__orn(a, b).
//   > Robustness: no unexpected type cast issues / redundant warnings.

#include "rvzkgintrin.h"

#endif // __RVINTRIN_H__
