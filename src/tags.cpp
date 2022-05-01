#include <taglib/fileref.h>
#include <taglib/tstring.h>

#include "tags.h"

const string get_tag(const string file_path, TagType tags)
{
	TagLib::FileRef file(file_path.c_str());
	switch (tags)
	{
		case TagType::Title:
			return file.tag()->title().toCString();
			break;
		case TagType::Author:
			return file.tag()->artist().toCString();
			break;
		case TagType::Album:
			return file.tag()->album().toCString();
			break;
	}
	return string();
}

const void set_tag(const string file_path, TagType tags, const string value)
{
	TagLib::FileRef file(file_path.c_str());
	switch (tags)
	{
		case TagType::Title:
			file.tag()->setTitle(value);
			break;
		case TagType::Author:
			file.tag()->setArtist(value);
			break;
		case TagType::Album:
			file.tag()->setAlbum(value);
			break;
	}
	file.save();
}
