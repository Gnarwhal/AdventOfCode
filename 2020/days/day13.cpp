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

struct Pair{ i64 id; usize index; };

// f = a + n0 * b = c + n1 * d
// f = req_base + n0 * req_loop = new_base + n1 * new_loop
// Solve for the smallest integer value f such that this holds true
auto find_least(i64 new_base, i64 new_loop, i64 req_base, i64 req_loop, i64 iter) -> i64 {
	while ((req_base - new_base + ++iter * req_loop) % new_loop != 0);
	return req_base + iter * req_loop;
}

auto day13() -> void {
	auto ready = usize(0);
	auto buses = std::vector<Pair>();
	{
		auto line = std::string();
		auto file = std::ifstream("inputs/day13.input");
		getline(file, line);
		ready = std::stoi(line);
		getline(file, line);
		auto start = usize(0);
		auto end   = usize(0);
		auto index = usize(0);
		auto id    = std::string();
		while ((end = line.find(',', start)) != std::string::npos) {
			id = line.substr(start, end - start);
			if (id != "x") {
				buses.push_back({ i64(std::stoi(line.substr(start, end - start))), index });
			}
			start = end + 1;
			++index;
		}
		end = line.size();
		id = line.substr(start, end - start);
		if (id != "x") {
			buses.push_back({ i64(std::stoi(line.substr(start, end - start))), index });
		}
	}
	
	auto id      = buses[0].id;
	auto minutes = buses[0].id - (ready % buses[0].id);
	for (auto i = usize(1); i < buses.size(); ++i) {
		auto local_minutes = buses[i].id - (ready % buses[i].id);
		if (local_minutes < minutes) {
			id      = buses[i].id;
			minutes = local_minutes;
		}
	}
	print((id * minutes));

	auto req_base = usize(buses[0].index);
	auto req_loop = usize(buses[0].id   );
	for (auto i = usize(1); i < buses.size(); ++i) {
		req_base = find_least(-buses[i].index, buses[i].id, req_base, req_loop, -1);
		if (i < buses.size() - 1) {
			req_loop = find_least(0, buses[i].id, 0, req_loop, 0);
		}
		/*
		required_base (rqb), required_loop (rql)

		base_loop (bl), repeat_loop (rl)

		rqb + a0 * rql = bl + a1 * rl < minimize and store in required loop
		a0 = (bl + a1 * rl - rqb) / rql

		b0 * rql = b1 * rl < minimize and store in required loop
		*/
	}
	print(req_base);
}
