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

enum OpCode { Acc, Jmp, Nop };
struct Op{ OpCode code; i32 num; bool executed; };
auto extract_op(const std::string & string) -> Op {
	auto op = Op{ Nop, 0 };
	auto op_code_str = string.substr(0, 3);
	     if (string.substr(0, 3) == "acc") { op.code = Acc; }
	else if (string.substr(0, 3) == "jmp") { op.code = Jmp; }
	else if (string.substr(0, 3) == "nop") { op.code = Nop; }

	op.num = std::stoi(string.substr(string.find(" ") + 1, string.size() - 4));

	return op;
}

struct State{ u32 isp; i32 acc; };

auto execute(State & state, std::vector<Op> & ops) -> void {
	switch (ops[state.isp].code) {
		case Acc: ops[state.isp].executed = true; state.acc += ops[state.isp].num; ++state.isp; break;
		case Jmp: ops[state.isp].executed = true; state.isp += ops[state.isp].num;              break;
		case Nop: ops[state.isp].executed = true;                                  ++state.isp; break;
	}
}

auto attempt_swap(State & state, std::vector<Op> & ops) -> bool {
	if (ops[state.isp].code == Jmp) {
		ops[state.isp].code = Nop;
	} else if (ops[state.isp].code == Nop) {
		ops[state.isp].code = Jmp;
	} else {
		return false;
	}

	auto local_state = state;
	ops[state.isp].executed = false;
	while (local_state.isp < ops.size() && !ops[local_state.isp].executed) {
		execute(local_state, ops);
	}
	if (local_state.isp >= ops.size()) {
		state = local_state;
		return true;
	} else if (ops[state.isp].code == Jmp) {
		ops[state.isp].code = Nop;
	} else if (ops[state.isp].code == Nop) {
		ops[state.isp].code = Jmp;
	}

	return false;
}

auto main(i32 argc, char * argv[]) -> i32 {
	auto ops = std::vector<Op>();
	{
		auto line = std::string();
		auto file = std::ifstream("day8.input");
		while (getline(file, line)) {
			ops.push_back(extract_op(line));
		}
	}
	
	auto state = State{ 0, 0 };
	while (!ops[state.isp].executed) {
		execute(state, ops);
	}
	std::cout << state.acc << std::endl;

	for (auto & op : ops) { op.executed = false; }

	state = State{ 0, 0 };
	for (;;) {
		if (attempt_swap(state, ops)) {
			std::cout << state.acc << std::endl;
			break;
		}
		execute(state, ops);
	}

	return 0;
}
