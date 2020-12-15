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

#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>

#include "../misc/types.hpp"
#include "../misc/print.hpp"

struct Pair{ u64 num; usize last; };

auto day15() -> void {
	auto last     = usize(0);
	auto index    = usize(0);
	auto sequence = std::unordered_map<u64, u64>();
	{
		auto line = std::string();
		auto file = std::ifstream("inputs/day15.input");
		getline(file, line);
		auto start = usize(0);
		auto end   = usize(0);
		auto num   = std::string();
		while ((end = line.find(',', start)) != std::string::npos) {
			num = line.substr(start, end - start);
			sequence.insert_or_assign(u64(std::stoll(num)), ++index);
			start = end + 1;
		}
		end = line.size();
		num = line.substr(start, end - start);
		sequence.insert_or_assign(u64(std::stoll(num)), ++index);
	}
	while (++index < 30000000) {
		if (index == 2020) {
			print(last);
		}
		if (sequence.contains(last)) {
			auto new_last = index - sequence[last];
			sequence[last] = index;
			last = new_last;
		} else {
			sequence.insert_or_assign(last, index);
			last = 0;
		}
	}
	print(last);
}
