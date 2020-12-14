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
#include <map>
#include <string>
#include <bitset>
#include <iostream>
#include <fstream>

#include "../misc/types.hpp"
#include "../misc/print.hpp"

struct Op{ u8 op; u64 num1; u64 num2; };

auto set_memory(std::map<u64, u64> & map, u64 addr, const std::vector<bool> & maskX, usize index, u64 value) -> void {
	while (++index < maskX.size() && !maskX[index]);
	if (index == maskX.size()) {
		map.insert_or_assign(addr, value);
	} else {
		set_memory(map, addr, maskX, index, value);
		set_memory(map, addr ^ (u64(1) << (maskX.size() - index - 1)), maskX, index, value);
	}
}

auto day14() -> void {
	auto ops = std::vector<Op>();
	{
		auto line = std::string();
		auto file = std::ifstream("inputs/day14.input");
		while (getline(file, line)) {
			if (line.find("mask") != std::string::npos) {
				auto mask0 = u64(-1);
				auto mask1 = u64( 0);
				for (auto i = usize(7); i < line.size(); ++i) {
					if (line[i] == '0') {
						mask0 ^= (u64(1) << (42 - i));
					} else if (line[i] == '1') {
						mask1 ^= (u64(1) << (42 - i));
					}
				}
				ops.push_back({ 0, mask0, mask1 });
			} else {
				auto value = line.find("=") + 2;
				ops.push_back({
					1,
					u64(std::stoll(line.substr(4, line.find("]") - 4))),
					u64(std::stoll(line.substr(value, line.size() - value)))
				});
			}
		}
	}
	auto mask0  = u64(-1);
	auto mask1  = u64( 0);
	auto memory = std::map<u64, u64>();
	for (auto op : ops) {
		if (op.op == 0) {
			mask0 = op.num1;
			mask1 = op.num2;
		} else {
			memory.insert_or_assign(op.num1, (op.num2 & mask0) | mask1);
		}
	}
	auto sum = u64(0);
	for(auto mem : memory) {
		sum += mem.second;
	}
	print(sum);

	mask1  = u64(0);
	memory = std::map<u64, u64>();
	auto maskX = std::vector<bool>(36);
	for (auto op : ops) {
		if (op.op == 0) {
			mask1 = op.num2;
			for (auto i = usize(0); i < maskX.size(); ++i) {
				auto bit = u64(1) << u64(35 - i);
				maskX[i] = (op.num1 & bit) && !(op.num2 & bit);
			}
		} else {
			set_memory(memory, op.num1 | mask1, maskX, -1, op.num2);
		}
	}
	sum = u64(0);
	for(auto mem : memory) {
		sum += mem.second;
	}
	print(sum);
}
