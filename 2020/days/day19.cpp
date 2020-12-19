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
#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>

#include "../misc/types.hpp"
#include "../misc/print.hpp"

enum RuleType { Char, Sequence, Alternator };

struct Rule {
	RuleType type;
	char c;
	std::vector<u64> list;
	std::vector<std::vector<u64>> or_list;

	explicit Rule(char c) noexcept : type(Char), c(c) {}
	explicit Rule(std::vector<u64> && list) noexcept : type(Sequence), list(std::move(list)) {}
	explicit Rule(std::vector<std::vector<u64>> && or_list) noexcept : type(Alternator), or_list(std::move(or_list)) {}
};

auto extract_numbers(const std::string & list) -> std::vector<u64> {
	auto nums  = std::vector<u64>();
	auto end   = usize(0);
	auto start = usize(0);
	while ((end = list.find(" ", ++end)) != std::string::npos) {
		nums.push_back(std::stoll(list.substr(start, end - start)));
		start = end + 1;
	}
	return std::move(nums);
}

auto matches(const std::string & string, usize & index, std::unordered_map<u64, Rule> & rules, u64 rule_id, bool sub) -> bool;

auto matches_list(const std::string & string, usize & index, std::unordered_map<u64, Rule> & rules, const std::vector<u64> & rule_ids, bool sub) -> bool {
	auto local_index = index;
	for (auto i = usize(0); i < rule_ids.size(); ++i) {
		if (!matches(string, local_index, rules, rule_ids[i], true)) {
			return false;
		}
	}
	index = local_index;
	return (sub || index == string.size());
}

auto matches(const std::string & string, usize & index, std::unordered_map<u64, Rule> & rules, u64 rule_id, bool sub) -> bool {
	if (index >= string.size()) {
		return false;
	}
	auto & rule = rules.find(rule_id)->second;
	switch (rule.type) {
		case Char: {
			if (string[index] == rule.c) {
				++index;
				return (sub || index == string.size());
			} else {
				return false;
			}
		}
		case Sequence: {
			return matches_list(string, index, rules, rule.list, sub);
		}
		case Alternator: {
			for (auto i = usize(0); i < rule.or_list.size(); ++i) {
				auto local_index = index;
				if (matches_list(string, local_index, rules, rule.or_list[i], sub)) {
					index = local_index;
					return true;
				}
			}
			return false;
		}
	}
	// むだ！makes the compiler happy though
	return false;
}

auto min_length(std::unordered_map<u64, Rule> & rules, u64 rule_id) -> usize;

auto min_length_list(std::unordered_map<u64, Rule> & rules, const std::vector<u64> & rule_ids) -> usize {
	auto len = usize(0);
	for (auto i = usize(0); i < rule_ids.size(); ++i) {
		len += min_length(rules, rule_ids[i]);
	}
	return len;
}

auto min_length(std::unordered_map<u64, Rule> & rules, u64 rule_id) -> usize {
	auto & rule = rules.find(rule_id)->second;
	switch (rule.type) {
		case Char:     return 1;
		case Sequence: return min_length_list(rules, rule.list);
		case Alternator: {
			auto min = min_length_list(rules, rule.or_list[0]);
			for (auto i = usize(1); i < rule.or_list.size(); ++i) {
				auto len = min_length_list(rules, rule.or_list[i]);
				if (len < min) {
					min = len;
				}
			}
			return min;
		}
	}
	// このもむだ！
	return 0;
}

auto day19() -> void {
	auto rules   = std::unordered_map<u64, Rule>();
	auto strings = std::vector<std::string>();
	{
		auto line = std::string();
		auto file = std::ifstream("inputs/day19.input");
		getline(file, line);
		while (line != "") {
			auto end = line.find(":");
			auto id = std::stoll(line.substr(0, end));
			if ((end = line.find("\"")) != std::string::npos) {
				rules.insert_or_assign(id, Rule(line[end + 1]));
			} else if (line.find("|") != std::string::npos) {
				end = line.find(":") + 2;
				line = line.substr(end, line.size() - end) + " |";
				auto sequences = std::vector<std::vector<u64>>();
				end = usize(0);
				auto start = usize(0);
				while ((end = line.find("|", ++end)) != std::string::npos) {
					sequences.push_back(extract_numbers(line.substr(start, end - start)));
					start = end + 2;
				}
				rules.insert_or_assign(id, Rule(std::move(sequences)));
			} else {
				end = line.find(":") + 2;
				rules.insert_or_assign(id, Rule(extract_numbers(line.substr(end, line.size() - end) + ' ')));
			}
			getline(file, line);
		}
		while (getline(file, line)) {
			strings.push_back(std::move(line));
		}
	}

	auto successful = usize(0);
	for (auto i = usize(0); i < strings.size(); ++i) {
		auto index = usize(0);
		successful += matches(strings[i], index, rules, 0, false);
	}
	print(successful);
	
	successful = usize(0);
	auto min_length42 = min_length(rules, 42);
	auto min_length31 = min_length(rules, 31);
	for (auto i = usize(0); i < strings.size(); ++i) {
		auto unsuccessful = true;
		auto base = min_length42 * 2 + min_length31;
		auto list = std::vector<u64>{ 42, 42, 31 };
		for (auto j = usize(0); unsuccessful && j * min_length42 + base <= strings[i].size(); ++j) {
			auto copy = list;
			for (auto k = usize(0); unsuccessful && k <= j; ++k) {
				auto index = usize(0);
				unsuccessful = !matches_list(strings[i], index, rules, copy, false);
				copy.push_back(31);
			}
			list.insert(list.begin(), 42);
		}
		successful += !unsuccessful;
	}
	print(successful);
}
