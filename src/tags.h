#include <string>

using std::string;

enum TagType
{
	Title,
	Author,
	Album,
};

const string get_tag(const string file_path, TagType tags);
const void set_tag(const string file_path, TagType tags, const string value);
