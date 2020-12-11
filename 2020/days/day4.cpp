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
#include <fstream>
#include <iostream>

#include "../misc/types.hpp"
#include "../misc/print.hpp"

struct KeyValue {
	std::string key;
	bool (*func)(const std::string & passport, usize index);
};

template <usize Min, usize Max>
auto try_num(const std::string & passport, usize index) -> bool {
	auto num = usize(0);
	--index;
	while (++index < passport.size() && '0' <= passport[index] && passport[index] <= '9') {
		num = (num * 10) + passport[index] - '0';
	}
	return Min <= num && num <= Max;
};

auto day4() -> void {
	auto valid_count1 = usize(0);
	auto valid_count2 = usize(0);

	auto passport = std::string();
	auto line     = std::string();
	auto file     = std::ifstream("inputs/day4.input");
	while (getline(file, line)) {
		if (line == "") {
			auto elements = std::vector<KeyValue>{
				{ "byr", try_num<1920, 2002> },
				{ "iyr", try_num<2010, 2020> },
				{ "eyr", try_num<2020, 2030> },
				{ "hgt", [](const std::string & passport, usize index) -> bool {
					return (try_num<150, 193>(passport, index) && passport.find("cm", index + 3) == index + 3)
						|| (try_num<59,  76 >(passport, index) && passport.find("in", index + 2) == index + 2);
				}},
				{ "hcl", [](const std::string & passport, usize index) -> bool {
					if (index < passport.size() && passport[index] == '#') {
						auto length = usize(0);
						auto true_index = usize(0);
						while ((true_index = index + ++length) < passport.size() && (
							   ('0' <= passport[true_index] && passport[true_index] <= '9')
							|| ('a' <= passport[true_index] && passport[true_index] <= 'f')
							|| ('A' <= passport[true_index] && passport[true_index] <= 'F')
						));
						return length == 7;
					}
					return false;
				}},
				{ "ecl", [](const std::string & passport, usize index) -> bool {
					const static auto eye_colors = std::vector<std::string>{ "amb", "blu", "brn", "gry", "grn", "hzl", "oth" };
					auto i = usize(0);
					for (; i < eye_colors.size() && passport.find(eye_colors[i], index) != index; ++i);
					return i < eye_colors.size();
				}},
				{ "pid", [](const std::string & passport, usize index) -> bool {
					auto length     = usize(-1);
					auto true_index = usize( 0);
					while ((true_index = index + ++length) < passport.size()
						&& ('0' <= passport[true_index] && passport[true_index] <= '9')
					);
					return length == 9;
				}},
			};
			auto valid1 = true;
			auto valid2 = true;
			for (auto i = usize(0); i < elements.size() && valid1; ++i) {
				auto index = usize(0);
				valid2 =
					(valid1 = ((index = passport.find(elements[i].key)) != std::string::npos))
					&& valid2
					&& elements[i].func(passport, index + elements[i].key.size() + 1);
			}
			valid_count1 += valid1;
			valid_count2 += valid2;
			passport = "";
		} else {
			passport += line + ' ';
		}
	}

	print(valid_count1);
	print(valid_count2);
}
