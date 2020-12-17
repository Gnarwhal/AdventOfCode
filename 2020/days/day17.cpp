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

constexpr auto CYCLES = 6;
constexpr auto BUFFER = CYCLES + 1;

auto neighbor3d_count(const auto & pocket, i32 x, i32 y, i32 z) -> usize {
	auto count = usize(0);
	for (auto i = i32(-1); i < 2; ++i) {
		for (auto j = i32(-1); j < 2; ++j) {
			for (auto k = i32(-1); k < 2; ++k) {
				count += (i != 0 || j != 0 || k != 0) && pocket[x + i][y + j][z + k];
			}
		}
	}
	return count;
}

auto neighbor4d_count(const auto & pocket, i32 w, i32 x, i32 y, i32 z) -> usize {
	auto count = usize(0);
	for (auto i = i32(-1); i < 2; ++i) {
		for (auto j = i32(-1); j < 2; ++j) {
			for (auto k = i32(-1); k < 2; ++k) {
				for (auto l = i32(-1); l < 2; ++l) {
					count += (i != 0 || j != 0 || k != 0 || l != 0) && pocket[w + l][x + i][y + j][z + k];
				}
			}
		}
	}
	return count;
}

auto day17() -> void {
	auto pocket = std::vector<std::vector<std::vector<std::vector<bool>>>>();
	{
		auto lines = std::vector<std::string>();
		auto line = std::string();
		auto file = std::ifstream("inputs/day17.input");
		while (getline(file, line)) {
			lines.push_back(line);
		}


		pocket = std::vector<std::vector<std::vector<std::vector<bool>>>>(BUFFER * 2 + 1);
		for (auto w = usize(0); w < pocket.size(); ++w) {
			pocket[w] = std::vector<std::vector<std::vector<bool>>>(lines[0].size() + BUFFER * 2);
			for (auto i = usize(0); i < pocket[0].size(); ++i) {
				auto vec = std::vector<std::vector<bool>>(lines.size() + BUFFER * 2);
				for (auto j = usize(0); j < vec.size(); ++j) {
					vec[j] = std::vector<bool>(BUFFER * 2 + 1);
					if (w == BUFFER && i >= BUFFER && i < BUFFER + lines[0].size() && j >= BUFFER && j < BUFFER + lines.size()) {
						vec[j][BUFFER] = lines[j - BUFFER][i - BUFFER] == '#';
					}
				}
				pocket[w][i] = std::move(vec);
			}
		}
	}

	{
		auto pockets = std::array<std::vector<std::vector<std::vector<bool>>>, 2>{ pocket[BUFFER], pocket[BUFFER] };
		auto bit = false;
		for (auto i = usize(0); i < CYCLES; ++i) {
			auto & read  = pockets[bit];
			auto & write = pockets[bit = !bit];
			for (auto x = i32(1); x < read.size() - 1; ++x) {
				for (auto y = i32(1); y < read[0].size() - 1; ++y) {
					for (auto z = i32(1); z < read[0][0].size() - 1; ++z) {
						auto neighbors = neighbor3d_count(read, x, y, z);
						if (read[x][y][z] && (neighbors < 2 || neighbors > 3)) {
							write[x][y][z] = false;
						} else if (!read[x][y][z] && neighbors == 3) {
							write[x][y][z] = true;
						} else {
							write[x][y][z] = read[x][y][z];
						}
					}
				}
			}
		}

		auto & pocket = pockets[bit];
		auto count = usize(0);
		for (auto i = usize(0); i < pocket.size(); ++i) {
			for (auto j = usize(0); j < pocket[0].size(); ++j) {
				for (auto k = usize(0); k < pocket[0][0].size(); ++k) {
					count += pocket[i][j][k];
				}
			}
		}
		print(count);
	}

	{
		auto pockets = std::array<std::vector<std::vector<std::vector<std::vector<bool>>>>, 2>{ pocket, pocket };
		auto bit = false;
		for (auto i = usize(0); i < CYCLES; ++i) {
			auto & read  = pockets[bit];
			auto & write = pockets[bit = !bit];
			for (auto w = i32(1); w < read.size() - 1; ++w) {
				for (auto x = i32(1); x < read[0].size() - 1; ++x) {
					for (auto y = i32(1); y < read[0][0].size() - 1; ++y) {
						for (auto z = i32(1); z < read[0][0][0].size() - 1; ++z) {
							auto neighbors = neighbor4d_count(read, w, x, y, z);
							if (read[w][x][y][z] && (neighbors < 2 || neighbors > 3)) {
								write[w][x][y][z] = false;
							} else if (!read[w][x][y][z] && neighbors == 3) {
								write[w][x][y][z] = true;
							} else {
								write[w][x][y][z] = read[w][x][y][z];
							}
						}
					}
				}
			}
		}

		auto & pocket = pockets[bit];
		auto count = usize(0);
		for (auto i = usize(0); i < pocket.size(); ++i) {
			for (auto j = usize(0); j < pocket[0].size(); ++j) {
				for (auto k = usize(0); k < pocket[0][0].size(); ++k) {
					for (auto l = usize(0); l < pocket[0][0][0].size(); ++l) {
						count += pocket[i][j][k][l];
					}
				}
			}
		}
		print(count);
	}
}
