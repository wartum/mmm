#include "pch.h"
#include "groups.h"

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

const string get_from_group( string original, vector<string> groups)
{
	std::smatch m;
	std::regex regex("^\\(\\d\\)$");
	if (std::regex_search(original, m, regex))
	{
		return groups[std::stoi(string(&m[0].str()[1]))-1];
	}
	return original;
}