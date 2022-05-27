#include <gtest/gtest.h>
#include <stdexcept>
#include <string.h>
#include <fstream>
#include <stdio.h>
#include <cstdio>
#include "../src/tags.h"

class TagsTest : public ::testing::Test
{
protected:
	const string original_file = "mine_sample.mp3";
	const string file = "sample.mp3";
	const string original_title = "";
	const string original_author = "";
	const string original_album = "";
	const string new_title = "New title";
	const string new_author = "New author";
	const string new_album = "New album";

	void SetUp() override
	{
		char buff[BUFSIZ];
		auto src = std::ifstream(original_file, std::ios::binary | std::ios::in);
		auto dst = std::ofstream(file, std::ios::binary | std::ios::out);

		while (src.read(buff, BUFSIZ))
		{
			dst.write(buff, BUFSIZ);
		}
		src.close();
		dst.close();
	}

	void TearDown() override
	{
		remove(file.c_str());
	}
};

TEST_F(TagsTest, positive_read_title)
{
	auto tag = get_tag(file, TagType::Title);
	ASSERT_EQ(tag, original_title);
}

TEST_F(TagsTest, positive_read_author)
{
	auto tag = get_tag(file, TagType::Author);
	ASSERT_EQ(tag, original_author);
}

TEST_F(TagsTest, positive_read_album)
{
	auto tag = get_tag(file, TagType::Album);
	ASSERT_EQ(tag, original_album);
}

TEST_F(TagsTest, positive_set_title)
{
	set_tag(file, TagType::Title, new_title);
	auto tag = get_tag(file, TagType::Title);
	ASSERT_EQ(tag, new_title);
}

TEST_F(TagsTest, positive_set_author)
{
	set_tag(file, TagType::Author, new_author);
	auto tag = get_tag(file, TagType::Author);
	ASSERT_EQ(tag, new_author);
}

TEST_F(TagsTest, positive_set_album)
{
	set_tag(file, TagType::Album, new_album);
	auto tag = get_tag(file, TagType::Album);
	ASSERT_EQ(tag, new_album);
}
