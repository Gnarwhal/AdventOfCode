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

constexpr auto CUP_COUNT = 9;

auto day23() -> void {
	auto start = usize(0);
	auto nums = std::array<usize, CUP_COUNT>();
	auto big_nums = std::vector<usize>(1000000);
	{
		auto line = std::string();
		auto file = std::ifstream("inputs/day23.input");
		getline(file, line);
		for (auto i = usize(0); i < CUP_COUNT; ++i) {
			nums[line[i] - '1'] = line[(i + 1) % CUP_COUNT] - '1';
		}
		start = line[0] - '1';
		for (auto i = usize(0); i < CUP_COUNT; ++i) {
			if (nums[i] != start) {
				big_nums[i] = nums[i];
			} else {
				big_nums[i] = CUP_COUNT;
			}
		}
		for (auto i = CUP_COUNT; i < big_nums.size() - 1; ++i) {
			big_nums[i] = i + 1;
		}
		big_nums[big_nums.size() - 1] = start;
	}

	auto begin = usize(0);
	auto end   = usize(0);

	// Part 1
	auto current = start;
	for (auto i = usize(0); i < 100; ++i) {
		begin = nums[current];
		end   = nums[nums[begin]];
		nums[current] = nums[end];
		auto destination = current;
		while (
			   begin       == (destination = (destination + CUP_COUNT - 1) % CUP_COUNT)
			|| nums[begin] ==  destination
			|| end         ==  destination
		);
		nums[end] = nums[destination];
		nums[destination] = begin;
		current = nums[current];
	}
	auto out = std::array<c8, CUP_COUNT + 1>{ 0 };
	for (auto i = nums[0], j = usize(0); i != 0; i = nums[i], ++j) {
		out[j] = (i + '1');
	}
	print(&out[0]);

	// Part 2
	current = start;
	for (auto i = usize(0); i < 10000000; ++i) {
		begin = big_nums[current];
		end   = big_nums[big_nums[begin]];
		big_nums[current] = big_nums[end];
		auto destination = current;
		while (
			   begin           == (destination = (destination + big_nums.size() - 1) % big_nums.size())
			|| big_nums[begin] ==  destination
			|| end             ==  destination
		);
		big_nums[end] = big_nums[destination];
		big_nums[destination] = begin;
		current = big_nums[current];
	}
	print(((big_nums[0] + 1) * (big_nums[big_nums[0]] + 1)));
}
