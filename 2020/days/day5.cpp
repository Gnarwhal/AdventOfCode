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
#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>

#include "../misc/types.hpp"
#include "../misc/print.hpp"

auto day5() -> void {
	auto seat = usize(0);
	auto line = std::string();
	auto file = std::ifstream("inputs/day5.input");

	auto seats = std::vector<usize>();

	while (getline(file, line)) {
		auto local_seat = usize(0);
		for (auto i = usize(0); i < 7 + 3; ++i) {
			local_seat = (local_seat << 1) | (line[i] == 'B' || line[i] == 'R');
		}
		if (local_seat > seat) {
			seat = local_seat;
		}
		seats.push_back(local_seat);
	}
	print(seat);

	std::sort(seats.begin(), seats.end());

	for (auto i = usize(0); i < seats.size() - 1; ++i) {
		if (seats[i] + 2 == seats[i + 1]) {
			print((seats[i] + 1));
			break;
		}
	}
}
