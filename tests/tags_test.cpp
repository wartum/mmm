#include <gtest/gtest.h>
#include <stdexcept>
#include <string.h>
#include "../src/tags.h"

class TagsTest : public ::testing::Test
{
protected:
	const string file = "Kuglarze.mp3";
	const string expected_title = "Kuglarze";
	const string expected_author = "Kaczmarski, Gintrowski, Lapins";
	const string expected_album = "Wojna Postu Z Karnawalem";
};

TEST_F(TagsTest, positive_read_title)
{
	auto tag = get_tag(file, TagType::Title);
	ASSERT_EQ(tag, expected_title);
}

TEST_F(TagsTest, positive_read_author)
{
	auto tag = get_tag(file, TagType::Author);
	ASSERT_EQ(tag, expected_author);
}

TEST_F(TagsTest, positive_read_album)
{
	auto tag = get_tag(file, TagType::Album);
	ASSERT_EQ(tag, expected_album);
}
