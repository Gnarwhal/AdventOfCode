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

// Find 2 numbers that sum to 2020
auto find_2020_x2(const std::vector<i32> & list) -> void {
	auto begin = 0;
	auto end   = list.size() - 1;
	auto sum   = 0;
	while ((sum = list[begin] + list[end]) != 2020) {
		if (sum < 2020) {
			++begin;
		} else {
			--end;
		}
	}
	print((list[begin] * list[end]));
}

// Find 3 numbers that sum to 2020
auto find_2020_x3(const std::vector<i32> & list) -> void {
	for (auto n0 = 0; n0 < list.size() - 2; ++n0) {
		for (auto n1 = 1; n1 < list.size() - 1; ++n1) {
			auto low  = n0 + 1;
			auto high = n1;
			while (low < high) {
				auto n2  = (low + high) / 2;
				auto sum = 0;
				if ((sum = list[n0] + list[n1] + list[n2]) == 2020) {
					print((list[n0] * list[n1] * list[n2]));
					return;
				} else if (sum < 2020) {
					low = n2 + 1;
				} else {
					high = n2;
				}
			}
		}
	}
}

auto day1() -> void {
	auto list = std::vector<i32>();
	{
		auto line = std::string();
		auto file = std::ifstream("inputs/day1.input");
		while (getline(file, line)) {
			list.push_back(std::stoi(line));
		}
	}
	std::sort(list.begin(), list.end());

	find_2020_x2(list);
	find_2020_x3(list);
}
