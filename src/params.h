#pragma once
#include "pch.h"

using std::string;
using std::map;
using std::tuple;
using std::vector;

const tuple<map<string, string>, vector<string>> read_args(int argc, char** argv);
void print_usage();
