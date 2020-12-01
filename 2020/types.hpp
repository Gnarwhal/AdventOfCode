/*******************************************************************************
 *
 * Copyright (c) 2020 Gnarwhal
 *
 * -----------------------------------------------------------------------------
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files(the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 *******************************************************************************/

#ifndef GNARWHAL_REDWOOD_TYPES
#define GNARWHAL_REDWOOD_TYPES

#include <cstddef>
#include <cstdint>

using u8    = std::uint8_t;
using i8    = std::int8_t;
using u16   = std::uint16_t;
using i16   = std::int16_t;
using u32   = std::uint32_t;
using i32   = std::int32_t;
using u64   = std::uint64_t;
using i64   = std::int64_t;
using usize = std::size_t;

constexpr auto operator "" _u8   (unsigned long long int num) noexcept -> u8;
constexpr auto operator "" _i8   (unsigned long long int num) noexcept -> i8;
constexpr auto operator "" _u16  (unsigned long long int num) noexcept -> u16;
constexpr auto operator "" _i16  (unsigned long long int num) noexcept -> i16;
constexpr auto operator "" _u32  (unsigned long long int num) noexcept -> u32;
constexpr auto operator "" _i32  (unsigned long long int num) noexcept -> i32;
constexpr auto operator "" _u64  (unsigned long long int num) noexcept -> u64;
constexpr auto operator "" _i64  (unsigned long long int num) noexcept -> i64;
constexpr auto operator "" _usize(unsigned long long int num) noexcept -> usize;

using c8  = u8;
using c16 = u16;
using c32 = u32;

constexpr auto operator "" _c8 (char c) noexcept -> c8;
constexpr auto operator "" _c16(char c) noexcept -> c16;
constexpr auto operator "" _c32(char c) noexcept -> c32;
constexpr auto operator "" _c8 (unsigned long long int c) noexcept -> c8;
constexpr auto operator "" _c16(unsigned long long int c) noexcept -> c16;
constexpr auto operator "" _c32(unsigned long long int c) noexcept -> c32;

using f32 = float;
using f64 = double;

constexpr auto operator "" _f32(long double num) noexcept -> f32;
constexpr auto operator "" _f64(long double num) noexcept -> f64;

#endif // GNARWHAL_REDWOOD_TYPES
