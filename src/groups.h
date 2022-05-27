#pragma once
#include "pch.h"

std::vector<std::string> get_groups(std::string file, std::string pattern);
const std::string get_from_group(const std::string original, std::vector<std::string> groups);