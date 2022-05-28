#include "pch.h"
#include "groups.h"

using std::vector;
using std::string;

vector<string> get_groups(string file, string pattern)
{
	vector<string> groups;
	std::smatch m;
	std::regex regex(pattern);
	auto pos = file.find_last_of("/");
	file = file.substr(pos + 1);

	if (std::regex_search(file, m, regex))
	{
		for (auto it = m.begin() + 1; it != m.end(); it++)
		{
			groups.push_back(*it);
		}
	}
	return groups;
}

const string get_from_group(const string original, vector<string> groups)
{
	std::string input = original;
	std::smatch m;
	std::regex regex("\\(\\d+\\)");
	while (std::regex_search(input, m, regex))
	{
		auto pos = input.find(m[0]);
		auto len = m[0].length();
		auto num_str = m[0].str().substr(1, len - 2);
		auto num_int = std::stoi(num_str);
		
		if (groups.size() >= (long unsigned int)num_int)
		{
			input.replace(pos, len, groups[num_int - 1]);
		}
		else
		{
			input.replace(pos, len, "");
		}
	}
	return input;
}
