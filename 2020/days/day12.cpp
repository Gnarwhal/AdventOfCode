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

struct Instruction{ char op; i32 num; };

auto day12() -> void {
	auto instructions = std::vector<Instruction>();
	{
		auto line = std::string();
		auto file = std::ifstream("inputs/day12.input");
		while (getline(file, line)) {
			instructions.push_back({ line[0], std::stoi(line.substr(1, line.size() - 1)) });
			if (line[0] == 'L' || line[0] == 'R') {
				instructions[instructions.size() - 1].num /= 90;
			}
		}
	}

	{
		auto ship_x = i32(0);
		auto ship_y = i32(0);
		auto direction = i32(2);
		for (const auto & instruction : instructions) {
			switch (instruction.op) {
				case 'N': ship_y += instruction.num; break;
				case 'E': ship_x += instruction.num; break;
				case 'S': ship_y -= instruction.num; break;
				case 'W': ship_x -= instruction.num; break;
				case 'R': direction = (direction - instruction.num + 4) % 4; break;
				case 'L': direction = (direction + instruction.num    ) % 4; break;
				case 'F':
					ship_x += ((direction - 1) % 2) * instruction.num;
					ship_y += ((direction - 2) % 2) * instruction.num;
					break;
			}
		}
		print((std::abs(ship_x) + std::abs(ship_y)));
	}

	{
		auto ship_x = i32(0);
		auto ship_y = i32(0);
		auto waypoint_x = i32(10);
		auto waypoint_y = i32( 1);
		for (const auto & instruction : instructions) {
			switch (instruction.op) {
				case 'N': waypoint_y += instruction.num; break;
				case 'E': waypoint_x += instruction.num; break;
				case 'S': waypoint_y -= instruction.num; break;
				case 'W': waypoint_x -= instruction.num; break;
				case 'R':
					for (auto i = i32(0); i < instruction.num; ++i) {
						auto copy = waypoint_x;
						waypoint_x =  waypoint_y;
						waypoint_y = -copy;
					}
					break;
				case 'L':
					for (auto i = i32(0); i < instruction.num; ++i) {
						auto copy = waypoint_x;
						waypoint_x = -waypoint_y;
						waypoint_y =  copy;
					}
					break;
				case 'F':
					ship_x += waypoint_x * instruction.num;
					ship_y += waypoint_y * instruction.num;
					break;
			}
		}
		print((std::abs(ship_x) + std::abs(ship_y)));
	}
}
