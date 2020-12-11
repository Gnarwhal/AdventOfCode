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

struct TreeVector{ usize horz;    usize vert;    };
struct Coordinate{ usize x_index; usize y_index; };

auto read_field_and_count_trees(const std::vector<TreeVector> & vectors) -> std::vector<u64> {
	auto tree_counts = std::vector<u64>(vectors.size());
	auto coords      = std::vector<Coordinate>(vectors.size());
	for (auto i = usize(0); i < coords.size(); ++i) {
		coords[i] = { usize(-vectors[i].horz), usize(-1) };
	}

	auto line = std::string();
	auto file = std::ifstream("inputs/day3.input");

	while (getline(file, line)) {
		for (auto i = usize(0); i < vectors.size(); ++i) {
			auto & vector = vectors[i];
			auto & coord  = coords[i];
			
			auto vertical_check = (++coord.y_index % vector.vert == 0);
			tree_counts[i] += vertical_check * (line[(coord.x_index += (vertical_check * vector.horz)) % line.size()] == '#');
		}
	}

	return std::move(tree_counts);
}

auto day3() -> void {
	auto trees       = std::vector<std::string>();
	auto tree_counts = read_field_and_count_trees(
		std::vector<TreeVector>{
			{ 3, 1 },
			{ 1, 1 },
			{ 5, 1 },
			{ 7, 1 },
			{ 1, 2 },
		}
	);

	print(tree_counts[0]);

	auto tree_count_product = u64(1);
	for (auto tree_count : tree_counts) {
		tree_count_product *= tree_count;
	}

	print(tree_count_product);
}
