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

auto evaluate_part1(const std::string & equation, usize & index) -> u64 {
	auto value     = u64(0);
	auto operation = 0;
	while (equation[index] != ')') {
		if ('0' <= equation[index] && equation[index] <= '9') {
			auto end = index;
			while ('0' <= equation[++end] && equation[end] <= '9');
			if (operation == 0) {
				value += std::stoll(equation.substr(index, end - index));
			} else {
				value *= std::stoll(equation.substr(index, end - index));
			}
			index = end;
		} else if (equation[index] == '+') {
			operation = 0;
			index += 2;
		} else if (equation[index] == '*') {
			operation = 1;
			index += 2;
		} else if (equation[index] == '(') {
			if (operation == 0) {
				value += evaluate_part1(equation, ++index);
			} else {
				value *= evaluate_part1(equation, ++index);
			}
		} else if (equation[index] == ' ') {
			++index;
		}
	}
	++index;
	return value;
}

auto evaluate_part2(const std::string & equation, usize & index) -> u64;
auto evaluate_part2_addition(const std::string & equation, usize & index) -> u64;
auto evaluate_part2_factor(const std::string & equation, usize & index) -> u64;

auto evaluate_part2(const std::string & equation, usize & index) -> u64 {
	auto value1 = evaluate_part2_addition(equation, index);
	if (++index < equation.size() && equation[index] == '*') {
		auto value2 = evaluate_part2(equation, index += 2);
		return value1 * value2;
	}
	--index;
	return value1;
}

auto evaluate_part2_addition(const std::string & equation, usize & index) -> u64 {
	auto value1 = evaluate_part2_factor(equation, index);
	if (++index < equation.size() && equation[index] == '+') {
		auto value2 = evaluate_part2_addition(equation, index += 2);
		return value1 + value2;
	}
	--index;
	return value1;
}

auto evaluate_part2_factor(const std::string & equation, usize & index) -> u64 {
	auto value = u64(0);
	if (equation[index] == '(') {
		value = evaluate_part2(equation, ++index);
		++index;
	} else {
		auto end = index;
		while ('0' <= equation[++end] && equation[end] <= '9');
		value = std::stoll(equation.substr(index, end - index));
		index = end;
	}
	return value;
}

auto day18() -> void {
	auto equations = std::vector<std::string>();
	{
		auto line = std::string();
		auto file = std::ifstream("inputs/day18.input");
		while (getline(file, line)) {
			equations.push_back(line + ')');
		}
	}
	auto sum = u64(0);
	for (auto i = usize(0); i < equations.size(); ++i) {
		auto index = usize(0);
		sum += evaluate_part1(equations[i], index);
	}
	print(sum);

	sum = u64(0);
	for (auto i = usize(0); i < equations.size(); ++i) {
		auto index = usize(0);
		sum += evaluate_part2_factor('(' + equations[i], index);
	}
	print(sum);
}
