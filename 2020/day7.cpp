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
#include <stack>
#include <string>
#include <map>
#include <set>
#include <iostream>
#include <fstream>

#include "types.hpp"

struct SubBag { std::string type; u32 count; };

auto find_bag(const std::string & line, usize & index, SubBag & new_bag) -> bool {
	while (++index <= line.size() && (line[index] < '0' || line[index] > '9'));
	if (index >= line.size()) {
		return false;
	}
	auto end = line.find(" ", index);
	auto count = std::stoi(line.substr(index, end - index));
	index = end + 1;
	end = line.find("bag", index);
	new_bag = SubBag{ line.substr(index, end - index - 1), u32(count) };
	index = end;
	return true;
}

struct Edges{ std::vector<std::string> from; std::vector<SubBag> to; };

auto count_to(const std::string & search, std::map<std::string, Edges> & map) -> usize {
	auto counted = 1;
	for (auto & bag : map[search].to) {
		counted += bag.count * count_to(bag.type, map);
	}
	return counted;
}

auto main(i32 argc, char * argv[]) -> i32 {
	auto bag_graph = std::map<std::string, Edges>();
	{
		auto line = std::string();
		auto file = std::ifstream("day7.input");
		while (getline(file, line)) {
			auto find = line.find("bag") - 1;
			auto bag_type = line.substr(0, line.find("bag") - 1);
			if (!bag_graph.contains(bag_type)) {
				bag_graph.insert_or_assign(bag_type, Edges());
			}

			auto new_bag = SubBag();
			while (find_bag(line, find, new_bag)) {
				if (!bag_graph.contains(new_bag.type)) {
					bag_graph.insert_or_assign(new_bag.type, Edges());
				}
				bag_graph[new_bag.type].from.push_back(bag_type);
				bag_graph[bag_type].to.push_back(new_bag);
			}
		}
	}

	auto seen = std::set<std::string>();
	auto search = std::stack<std::string>();
	search.push("shiny gold");
	while (search.size() > 0) {
		auto current = search.top();
		search.pop();
		for (const auto & bag_type : bag_graph[current].from) {
			if (!seen.contains(bag_type)) {
				search.push(bag_type);
				seen.insert(bag_type);
			}
		}
	}
	std::cout << seen.size() << std::endl;

	std::cout << (count_to("shiny gold", bag_graph) - 1) << std::endl;

	return 0;
}
