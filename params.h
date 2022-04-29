#pragma once
#include <string>
#include <map>

using std::string;
using std::map;

const map<string, string> read_params(int argc, char** argv);
void print_usage();
