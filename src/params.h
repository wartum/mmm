#pragma once
#include "pch.h"

const std::tuple<std::map<std::string, std::string>, std::vector<std::string>> read_args(int argc, char** argv);
void print_usage();
