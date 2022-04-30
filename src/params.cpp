#include <iostream>
#include <string.h>
#include <stdexcept>
#include <sstream>
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
	{ "file-path"    , "path to mp3 file"            , true  , false } ,
	{ "print-title"  , "prints mp3 title to STDOUT"  , false , true  } ,
	{ "print-author" , "prints mp3 author to STDOUT" , false , true  } ,
	{ "print-album"  , "prints mp3 album to STDOUT"  , false , true  } ,
	{ "help"         , "prints help message"         , false , true  } ,
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

const map<string, string> read_params(int argc, char** argv)
{
	map<string,string> params;
	uint16_t i=1;
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
			std::stringstream ss;
			ss << "Invalid argument \"" << argv[i] << "\"";
			throw std::invalid_argument(ss.str());
		}
	}
	for (auto& p : supportedParameters)
	{
		if (p.is_mandatory && params.find(p.name) == params.end())
		{
			std::stringstream ss;
			ss << "Mandatory field \"" << p.name << "\" is not provided";
			throw std::invalid_argument(ss.str());
		}
	}
	return params;
}

void print_usage()
{
	std::cout << "Mp3 Metadata Modifier usage\n";
	for (auto& p : supportedParameters)
	{
		auto mandatory = p.is_mandatory ?
			" [Mandatory]" :
			"\t";

		std::cout
			<< "--"
			<< p.name 
			<< mandatory
			<< "\t- "
			<< p.description
			<< std::endl;
	}
	std::cout << std::endl << std::endl;
}
