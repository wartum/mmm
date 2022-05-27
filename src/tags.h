#pragma once
#include "pch.h"

enum TagType
{
	Title,
	Author,
	Album,
};

const std::string get_tag(const std::string file_path, TagType tags);
const void set_tag(const std::string file_path, TagType tags, const std::string value);
