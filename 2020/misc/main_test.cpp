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

#include <iostream>
#include <string>
#include <chrono>

#include "types.hpp"

extern auto current_day() -> void;

auto main(i32 argc, char * argv[]) -> i32 {
	auto TEST_CYCLES = 1;
	if (argc >= 2) {
		TEST_CYCLES = std::stoi(argv[1]);
	}

	std::cout << "Starting test with " << TEST_CYCLES << " iterations..." << std::endl;
	auto begin1 = std::chrono::high_resolution_clock::now();

	for (auto i = usize(0); i < TEST_CYCLES; ++i) {
		current_day();
	}

	auto end1 = std::chrono::high_resolution_clock::now();

	if (argc >= 3) {
		if (argv[2] == std::string("millis")) {
			std::cout << "Tests completed in " << std::chrono::duration_cast<std::chrono::milliseconds>(end1 - begin1).count() << " milliseconds"<< std::endl;
		} else if (argv[2] == std::string("nanos")) {
			std::cout << "Tests completed in " << std::chrono::duration_cast<std::chrono::nanoseconds>(end1 - begin1).count() << " nanoseconds"<< std::endl;
		} else if (argv[2] == std::string("micros")) {
			std::cout << "Tests completed in " << std::chrono::duration_cast<std::chrono::microseconds>(end1 - begin1).count() << " microsenconds"<< std::endl;
		} else {
			std::cout << "Unkown time scale '" << argv[2] << "'" << std::endl;
		}
	} else {
			std::cout << "Tests completed in " << std::chrono::duration_cast<std::chrono::microseconds>(end1 - begin1).count() << " microseconds"<< std::endl;
	}

	return 0;
}

