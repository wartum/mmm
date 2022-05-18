#include <iostream>
#include <string.h>
#include <stdexcept>
#include <sstream>
#include <tuple>
#include <unistd.h>
#include "params.h"

struct SupportedParameter
{
	string name;
	string description;
	bool is_mandatory;
	bool is_flag;
};

const SupportedParameter supportedParameters[] 
{
	{ "help"         ,"Prints this message"                            ,false ,true  },
	{ "file-path"    ,"Path to mp3 file"                               ,true  ,false },
	{ "print-title"  ,"Prints mp3 title to STDOUT"                     ,false ,true  },
	{ "print-author" ,"Prints mp3 author to STDOUT"                    ,false ,true  },
	{ "print-album"  ,"Prints mp3 album to STDOUT"                     ,false ,true  },
	{ "set-title"    ,"Sets file title to given value"                 ,false ,false },
	{ "set-author"   ,"Sets file author to given value"                ,false ,false },
	{ "set-album"    ,"Sets file album to given value"                 ,false ,false },
	{ "groups"       ,"Applies regex on file name and matches groups"  ,false ,false },
};

static const bool is_param_supported(const string name)
{
	for (auto& p : supportedParameters)
	{
		if (p.name == name)
		{
			return true;
		}
	}
	return false;
};

static const bool is_param_a_flag(const string name)
{
	for (auto& p : supportedParameters)
	{
		if (p.name == name)
		{
			return p.is_flag;
		}
	}
	return false;
}

const tuple<map<string, string>, vector<string>> read_args(int argc, char** argv)
{
	map<string,string> params;
	vector<string> files;
	int i=1;
	while(i<argc)
	{
		if (argv[i][0] == '-' && argv[i][1] == '-')
		{
			char* unprefixed_key = argv[i] + 2;
			if (is_param_supported(unprefixed_key) == false)
			{
				std::stringstream ss;
				ss << "Unsupported parameter \"" << unprefixed_key << "\"";
				throw std::invalid_argument(ss.str());
			}
			if (is_param_a_flag(unprefixed_key))
			{
				params[unprefixed_key] = "true";
				i++;
				continue;
			}
			if (argc == i+1)
			{
				std::stringstream ss;
				ss << "No value provided for key \"" << unprefixed_key << "\"";
				throw std::invalid_argument(ss.str());
			}
			else
			{
				params[unprefixed_key] = argv[i+1];
				i+=2;
				continue;
			}
		}
		else
		{
			if (access(argv[i], F_OK) == 0)
			{
				files.push_back(string(argv[i]));
				i += 1;
			}
			else
			{
				std::stringstream ss;
				ss << "File " << argv[i] << " doesn't exist";
				throw std::invalid_argument(ss.str());
			}
		}
	}
	return std::make_tuple(params, files);
}

void print_usage()
{
	std::cout << "Mp3 Metadata Modifier usage\n";
	for (auto& p : supportedParameters)
	{
		auto mandatory = p.is_mandatory ?
			" [Mandatory]" :
			"";

		std::cout
			<< "--"
			<< p.name 
			<< mandatory
			<< " - "
			<< p.description
			<< std::endl;
	}
}
