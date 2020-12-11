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

#include <vector>
#include <array>
#include <string>
#include <iostream>
#include <fstream>

#include "../misc/types.hpp"
#include "../misc/print.hpp"

template <typename Lambda>
auto iterate_seats(const auto & seats, Lambda callback) {
	for (auto i = i32(0); i < seats.size(); ++i) {
		for (auto j = i32(0); j < seats[0].size(); ++j) {
			if (seats[i][j] != '.') {
				callback(i, j);
			}
		}
	}
}

auto seats_equal(const auto & seats) -> bool {
	for (auto i = usize(0); i < seats[0].size(); ++i) {
		for (auto j = usize(0); j < seats[0][0].size(); ++j) {
			if (seats[0][i][j] != seats[1][i][j]) {
				return false;
			}
		}
	}
	return true;
}

auto count_seats(const auto & seats) -> usize {
	auto occupied = usize(0);
	iterate_seats(seats, [&seats, &occupied](i32 i, i32 j) {
		occupied += (seats[i][j] == '#');
	});
	return occupied;
}

auto day11() -> void {
	auto bit = u8(0b1);
	auto seats = std::array<std::vector<std::string>, 2>();
	{
		auto line = std::string();
		auto file = std::ifstream("inputs/day11.input");
		while (getline(file, line)) {
			seats[bit].push_back(line);
		}
		seats[!bit] = seats[bit];
	}

	do {
		auto & read  = seats[bit];
		auto & write = seats[bit = !bit];

		iterate_seats(read, [&read, &write](usize i, usize j) {
			auto occupied = u8(0);
			auto max_ii = std::min(i + 2, read.size());
			auto max_jj = std::min(j + 2, read[0].size());
			for (auto ii = bool(i) * (i - 1); ii < max_ii; ++ii) {
				for (auto jj = bool(j) * (j - 1); jj < max_jj; ++jj) {
					occupied += read[ii][jj] == '#';
				}
			}
				 if (occupied == 0 && read[i][j] == 'L') write[i][j] = '#';
			else if (occupied >= 5 && read[i][j] == '#') write[i][j] = 'L'; // occupied >= 5 (not >= 4) because the occupied seat itself was counted as adjacent
			else                                         write[i][j] = read[i][j];
		});
	}
	while (!seats_equal(seats));

	print(count_seats(seats[0]));

	iterate_seats(seats[0], [&seats](i32 i, i32 j) {
		seats[0][i][j] = seats[1][i][j] = 'L';
	});

	do {
		auto & read  = seats[bit];
		auto & write = seats[bit = !bit];

		iterate_seats(read, [&read, &write](i32 i, i32 j) {
			auto occupied = u8(0);
			for (auto k = i32(0); k < 8; ++k) {
				auto dir = k + (k > 3);
				auto y   = i;
				auto x   = j;
				auto y_shift = (dir % 3) - 1;
				auto x_shift = (dir > 5) - (dir < 3);
				for (;;) {
					y += y_shift;
					x += x_shift;
					if (y == -1 || x == -1 || y == read.size() || x == read[0].size() || read[y][x] == 'L') {
						break;
					} else if (read[y][x] == '#') {
						++occupied;
						break;
					}
				}
			}
				 if (occupied == 0 && read[i][j] == 'L') write[i][j] = '#';
			else if (occupied >= 5 && read[i][j] == '#') write[i][j] = 'L'; // no longer counting the seat itself as adjacent so stays occupied >= 5
			else                                         write[i][j] = read[i][j];
		});
	} while (!seats_equal(seats));

	print(count_seats(seats[0]));
}
