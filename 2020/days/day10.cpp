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

struct Pair {
	u64 jolt;
	u64 count;
};

auto operator<(const Pair & left, const Pair & right) -> bool {
	return left.jolt < right.jolt;
}

auto day10() -> void {
	auto jolts = std::vector<Pair>{{ 0, 1 }};
	{
		auto line = std::string();
		auto file = std::ifstream("inputs/day10.input");
		while (getline(file, line)) {
			jolts.push_back({ (u64) std::stoll(line), 0 });
		}
	}
	std::sort(jolts.begin(), jolts.end());
	jolts.push_back({ jolts[jolts.size() - 1].jolt + 3, 0 });

	auto dif1 = usize(0);
	auto dif3 = usize(0);
	for (auto i = usize(0); i < jolts.size() - 1; ++i) {
		     if (jolts[i + 1].jolt - jolts[i].jolt == 1) ++dif1;
		else if (jolts[i + 1].jolt - jolts[i].jolt == 3) ++dif3;
	}

	print((dif1 * dif3));

	for (auto i = i32(0); i < jolts.size() - 1; ++i) {
		for (auto j = i + 1; j < jolts.size(); ++j) {
			if (jolts[j].jolt <= jolts[i].jolt + 3) {
				jolts[j].count += jolts[i].count;
			} else {
				break;
			}
		}
	}
	print(jolts[jolts.size() - 1].count);
}
