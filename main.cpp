#include <iostream>
#include <stdexcept>
#include <string>
#include <map>
#include <taglib/fileref.h>
#include <taglib/tstring.h>

#include "params.h"

using std::string;

int main(int argc, char** argv)
{
	try
	{
		auto params = read_params(argc, argv);
		for (auto it=params.begin(); it != params.end(); it++)
		{
			std::cout << it->first << " : " << it->second << std::endl;
		}
	}
	catch (std::invalid_argument& e)
	{
		std::cerr << e.what() << std::endl << std::endl;
		print_usage();
		return -1;
	}

	return 0;
}
