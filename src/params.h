#pragma once
#include <string>
#include <map>
#include <tuple>
#include <vector>

using std::string;
using std::map;
using std::tuple;
using std::vector;

const tuple<map<string, string>, vector<string>> read_args(int argc, char** argv);
void print_usage();
