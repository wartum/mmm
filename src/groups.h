#include "pch.h"

using std::vector;
using std::string;

vector<string> get_groups(string file, string pattern);
const string get_from_group(const string original, vector<string> groups);