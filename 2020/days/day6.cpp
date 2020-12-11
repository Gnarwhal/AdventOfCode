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

#include "../misc/types.hpp"
#include "../misc/print.hpp"

auto day6() -> void {
	{
		auto line    = std::string();
		auto file    = std::ifstream("inputs/day6.input");

		auto answers = std::vector<u32>(26);

		auto sum_1 = usize(0);

		auto group_size = usize(0);
		auto sum_2      = usize(0);
		while (getline(file, line)) {
			if (line == "") {
				for (auto i = usize(0); i < answers.size(); ++i) {
					sum_1 += (answers[i] > 0);
					sum_2 += (answers[i] == group_size);
					answers[i] = 0;
				}
				group_size = 0;
			} else {
				++group_size;
				for (char c : line) {
					++answers[c  - 'a'];
				}
			}
		}
		print(sum_1);
		print(sum_2);
	}
}
