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

auto read_field_and_count_trees(std::vector<std::string> & trees, usize horizontal_increment, usize vertical_increment) -> u64 {
	auto tree_count = u64(0);

	auto x_index = usize(-horizontal_increment);
	auto y_index = usize(-1);
	auto line = std::string();
	auto file = std::ifstream("day3.input");

	while (getline(file, line)) {
		auto vertical_check = (++y_index % vertical_increment == 0);
		tree_count += vertical_check * (line[(x_index += (vertical_check * horizontal_increment)) % line.size()] == '#');
	}

	return tree_count;
}

auto main(i32 argc, char ** argv) -> i32 {
	auto trees       = std::vector<std::string>();
	auto tree_counts = std::vector<u64>();

	tree_counts.push_back(read_field_and_count_trees(trees, 3, 1));
	std::cout << tree_counts[0] << std::endl;

	tree_counts.push_back(read_field_and_count_trees(trees, 1, 1));
	tree_counts.push_back(read_field_and_count_trees(trees, 5, 1));
	tree_counts.push_back(read_field_and_count_trees(trees, 7, 1));
	tree_counts.push_back(read_field_and_count_trees(trees, 1, 2));
	auto tree_count_product = u64(1);
	for (auto tree_count : tree_counts) {
		tree_count_product *= tree_count;
	}
	std::cout << tree_count_product << std::endl;

	return 0;
}
