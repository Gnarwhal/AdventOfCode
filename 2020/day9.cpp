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
#include <string>
#include <iostream>
#include <fstream>

#include "types.hpp"

auto find_sum(usize index, std::vector<u64> xmas) {
	for (auto i = index - 25; i < index - 1; ++i) {
		for (auto j = i + 1; j < index; ++j) {
			if (xmas[i] + xmas[j] == xmas[index]) {
				return true;
			}
		}
	}
	return false;
}

auto main(i32 argc, char * argv[]) -> i32 {
	auto xmas = std::vector<u64>();
	auto line = std::string();
	auto file = std::ifstream("day9.input");
	while (getline(file, line)) {
		xmas.push_back(std::stoll(line));
	}

	auto invalid = u64(0);
	for (auto i = usize(25); i < xmas.size(); ++i) {
		if (!find_sum(i, xmas)) {
			std::cout << (invalid = xmas[i]) << std::endl;
			break;
		}
	}
	
	auto head_index = 0;
	auto tail_index = 1;
	auto sum        = xmas[0] + xmas[1];
	while (sum != invalid) {
		if (sum < invalid) {
			sum += xmas[++tail_index];
		} else if (head_index + 1 < tail_index) {
			sum -= xmas[head_index];
			++head_index;
		} else {
			head_index = tail_index + 1;
			tail_index = head_index + 1;
			sum        = xmas[head_index] + xmas[tail_index];
		}
	}
	auto min = xmas[tail_index];
	auto max = xmas[tail_index];
	for (auto i = head_index; i < tail_index; ++i) {
		if (xmas[i] < min) {
			min = xmas[i];
		} else if (xmas[i] > max) {
			max = xmas[i];
		}
	}
	std::cout << (min + max) << std::endl;

	return 0;
}
