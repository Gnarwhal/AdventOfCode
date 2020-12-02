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

struct Password {
	u32 min;
	u32 max;
	char c;
	std::string password;
};

auto extract_num(usize & index, const std::string & string) -> u32 {
	auto num = u32(0);
	--index;
	while ('0' <= string[++index] && '9' >= string[index]) {
		num = (num * 10) + (string[index] - '0');
	}
	return num;
}

auto count_valid_sled(const std::vector<Password> & passwords) -> u32 {
	auto valid = u32(0);
	for (auto password : passwords) {
		auto count = u32(0);
		for (auto c : password.password) {
			if (c == password.c) {
				++count;
			}
		}
		valid += (password.min <= count && count <= password.max);
	}
	return valid;
}

auto count_valid_toboggan(const std::vector<Password> & passwords) -> u32 {
	auto valid = u32(0);
	for (auto password : passwords) {
		if ((password.password[password.min - 1] == password.c)
		  ^ (password.password[password.max - 1] == password.c)) {
			++valid;
		}
	}
	return valid;
}

auto main(i32 argc, char * argv[]) -> i32 {
	auto passwords = std::vector<Password>();
	{
		auto line = std::string();
		auto file = std::ifstream("day2.input");
		while (getline(file, line)) {
			auto index = usize(0);
			auto password = Password{};
			password.min      = extract_num(  index, line);
			password.max      = extract_num(++index, line);
			password.c        = line[++index];
			password.password = line.substr(index + 3, line.size() - index - 3);
			passwords.push_back(password);
		}
	}

	std::cout << count_valid_sled(passwords)     << std::endl;
	std::cout << count_valid_toboggan(passwords) << std::endl;

	return 0;
}
