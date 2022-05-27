#include "pch.h"
#include "params.h"
#include "groups.h"
#include "tags.h"

using std::string;
using std::vector;
using std::map;

static map<string, string> params;
static vector<string> files;

static int handle_params(int argc, char** argv);
static void print_tags(const string file_path, const bool print_title, const bool print_author, const bool print_album);
static void modify_tags(const string file_path, const string new_title, const string new_author, const string new_album);

int main(int argc, char** argv)
{
	auto status = handle_params(argc, argv);
	if (status != 0) return status;

	if (params.find("help") != params.end())
	{
		print_usage();
		return 0;
	}

	for (auto& file : files)
	{
		auto groups = get_groups(file, params["groups"]);
		modify_tags(file,
			params.find("set-title")  != params.end() ? get_from_group(params["set-title"], groups)  : string(),
			params.find("set-author") != params.end() ? get_from_group(params["set-author"], groups) : string(),
			params.find("set-album")  != params.end() ? get_from_group(params["set-album"], groups)  : string());
		print_tags(file,
			params.find("print-title")  != params.end(),
			params.find("print-author") != params.end(),
			params.find("print-album")  != params.end());
	}

	return 0;
}

static int handle_params(int argc, char** argv)
{
	try
	{
		auto ret = read_args(argc, argv);
		params = std::move(std::get<0>(ret));
		files = std::move(std::get<1>(ret));
	}
	catch (std::invalid_argument& e)
	{
		std::cerr << e.what()
			<< std::endl
			<< "use --help parameter for available parameters"
			<< std::endl;
		return -1;
	}
	return 0;
}

static void print_tags(const string file_path, const bool print_title, const bool print_author, const bool print_album)
{
	if(print_title) std::cout  << file_path << ": " << "Title: "  << get_tag(file_path, TagType::Title)  << std::endl;
	if(print_author) std::cout << file_path << ": " << "Author: " << get_tag(file_path, TagType::Author) << std::endl;
	if(print_album) std::cout  << file_path << ": " << "Album: "  << get_tag(file_path, TagType::Album)  << std::endl;
}

static void modify_tags(const string file_path, const string new_title, const string new_author, const string new_album)
{
	if (new_title.empty() == false)  set_tag(file_path, TagType::Title, new_title);
	if (new_author.empty() == false) set_tag(file_path, TagType::Author, new_author);
	if (new_album.empty() == false)  set_tag(file_path, TagType::Album, new_album);
}