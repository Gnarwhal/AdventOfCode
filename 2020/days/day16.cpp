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

struct Rule { u64 r11; u64 r12; u64 r21; u64 r22; };

auto read_ticket(std::vector<u64> & ticket, const std::string & line) -> void {
	auto start = usize(0);
	auto end   = usize(0);
	while ((end = line.find(",", end + 1)) != std::string::npos) {	
		ticket.push_back(std::stoll(line.substr(start, end - start)));
		start = end + 1;
	}
	end = line.size();
	ticket.push_back(std::stoll(line.substr(start, end - start)));
}

auto matches_rule(const Rule & rule, u64 field) -> bool {
	return (rule.r11 <= field && field <= rule.r12) || (rule.r21 <= field && field <= rule.r22);
}

auto remove_if_exists(std::vector<u64> & v, u64 search) -> bool {
	auto low  = usize(0);
	auto high = v.size();
	while (low < high) {
		auto index = (low + high) / 2;
		if (v[index] == search) {
			v.erase(v.begin() + index);
			return true;
		} else if (search > v[index]) {
			low = index + 1;
		} else {
			high = index;
		}
	}
	return false;
}

auto contains(std::vector<u64> & v, u64 search) -> bool {
	auto low  = usize(0);
	auto high = v.size();
	while (low < high) {
		auto index = (low + high) / 2;
		if (v[index] == search) {
			return true;
		} else if (search > v[index]) {
			low = index + 1;
		} else {
			high = index;
		}
	}
	return false;
}

auto day16() -> void {
	auto find        = std::vector<u64>();
	auto rules       = std::vector<Rule>();
	auto your_ticket = std::vector<u64>();
	auto tickets     = std::vector<std::vector<u64>>();
	{
		auto line  = std::string();
		auto file  = std::ifstream("inputs/day16.input");
		auto index = usize(0);
		while (getline(file, line) && line != "") {
			auto rule  = Rule();
			auto start = line.find(":") + 2;
			auto end   = line.find("-");
			rule.r11 = std::stoll(line.substr(start, end - start));
			start = end + 1;
			end   = line.find(" ", end);
			rule.r12 = std::stoll(line.substr(start, end - start));
			start = end + 4;
			end   = line.find("-", end);
			rule.r21 = std::stoll(line.substr(start, end - start));
			start = end + 1;
			end   = line.size();
			rule.r22 = std::stoll(line.substr(start, end - start));
			rules.push_back(rule);
			if (line.find("departure") != std::string::npos) {
				find.push_back(index);
			}
			++index;
		}
		getline(file, line);
		getline(file, line);
		read_ticket(your_ticket, line);
		getline(file, line);
		getline(file, line);
		while (getline(file, line)) {
			auto ticket = std::vector<u64>();
			read_ticket(ticket, line);
			tickets.push_back(std::move(ticket));
		}
	}
	auto valid = std::vector<std::vector<u64>>();
	{
		auto foo = std::vector<u64>(your_ticket.size());
		for (auto i = usize(0); i < your_ticket.size(); ++i) {
			foo[i] = i;
		}
		for (auto i = usize(0); i < rules.size(); ++i) {
			valid.push_back(foo);
		}
	}
	auto sum = u64(0);
	for (auto k = usize(0); k < tickets.size(); ++k) {
		const auto & ticket = tickets[k];
		auto invalid_ticket = false;
		for (auto i = usize(0); i < ticket.size(); ++i) {
			auto invalid_field = true;
			for (auto j = usize(0); invalid_field && j < rules.size(); ++j) {
				if (matches_rule(rules[j], ticket[i])) {
					invalid_field = false;
				}
			}
			if (invalid_field) {
				sum += ticket[i];
			}
			invalid_ticket = invalid_ticket || invalid_field;
		}
		if (invalid_ticket) {
			tickets.erase(tickets.begin() + k);
			--k;
		}
	}
	print(sum);

	for (auto i = usize(0); i < tickets.size(); ++i) {
		const auto & ticket = tickets[i];
		for (auto j = usize(0); j < valid.size(); ++j) {
			auto & v = valid[j];
			for (auto k = usize(0); k < v.size(); ++k) {
				if (!matches_rule(rules[j], ticket[v[k]])) {
					v.erase(v.begin() + k);
					--k;
				}
			}
		}
	}
	for (auto i = usize(0); i < your_ticket.size(); ++i) {
		auto cont_index = usize(0);
		auto contained  = usize(0);
		for (auto j = usize(0); j < valid.size(); ++j) {
			if (contains(valid[j], i)) {
				cont_index = j;
				++contained;
			}
		}
		if (contained == 1) {
			for (auto j = usize(0); j < valid[cont_index].size(); ++j) {
				if (valid[cont_index][j] != i) {
					valid[cont_index].erase(valid[cont_index].begin() + j);
					--j;
				}
			}
		}
	}

	auto loop = true;
	while (loop) {
		loop = false;
		for (auto i = usize(0); i < valid.size(); ++i) {
			if (valid[i].size() == 1) {
				for (auto j = usize(0); j < valid.size(); ++j) {
					if (j != i) {
						auto temp = remove_if_exists(valid[j], valid[i][0]);
						loop = temp || loop;
					}
				}
			}
		}
	}

	auto product = u64(1);
	for (auto i = usize(0); i < find.size(); ++i) {
		product *= your_ticket[valid[find[i]][0]];
	}
	print(product);
}
