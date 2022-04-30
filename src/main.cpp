#include <iostream>
#include <stdexcept>
#include <string>
#include <map>

#include "params.h"
#include "tags.h"

using std::string;

static map<string, string> params;

static int handle_params(int argc, char** argv);

int main(int argc, char** argv)
{
	auto status = handle_params(argc, argv);
	if (status != 0) return status;

	if (params.find("help") != params.end())
	{
		print_usage();
		return 0;
	}
	for (auto it=params.begin(); it != params.end(); it++)
	{
		std::cout << it->first << " : " << it->second << std::endl;
	}

	return 0;
}

static int handle_params(int argc, char** argv)
{
	try
	{
		auto p = read_params(argc, argv);
		params = std::move(p);
	}
	catch (std::invalid_argument& e)
	{
		std::cerr << e.what() << std::endl << "use --help parameter for available parameters" << std::endl;
		return -1;
	}
	return 0;
}

