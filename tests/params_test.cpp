#include <gtest/gtest.h>
#include <stdexcept>
#include <string.h>
#include <fstream>
#include <stdio.h>
#include "../src/params.h"

class ParamsTest : public ::testing::Test
{
protected:
	const int max_params = 10;
	int argc;
	char** argv;

	ParamsTest()
	{
		argv = new char*[max_params];
	}

	~ParamsTest()
	{
		for(int i = 0; i < max_params; i++)
		{
			delete[] argv[i];
			argv[i] = nullptr;
		}
		delete[] argv;
	}

	void SetUp() override
	{
		for (auto& file_name : {"tests/music.mp3", "tests/music2.mp3"})
		{
			std::ofstream f(file_name, std::ios::out);
			f << "";
			f.close();
		}
	}

	void TearDown() override
	{
		for (auto& file_name : {"tests/music.mp3", "tests/music2.mp3"})
		{
			remove(file_name);
		}
	}

	void setup_testing_args(std::vector<string> args)
	{
		argv[0] = new char[4];
		strcpy(argv[0], "mmm");
		int current_arg = 1;
		argc = args.size() + 1;

		for (auto& a : args)
		{
			argv[current_arg] = new char[50];
			strcpy(argv[current_arg], a.c_str());
			current_arg++;
		}
	}
};

TEST_F(ParamsTest, negative_file_not_exist)
{
	setup_testing_args({"non-existing-file"});
	EXPECT_THROW(read_args(argc, argv), std::invalid_argument);
}

TEST_F(ParamsTest, positive_provide_files)
{
	setup_testing_args({"music.mp3", "music2.mp3"});
	auto files = std::get<1>(read_args(argc, argv));
	EXPECT_EQ(files.size(), 2);
	EXPECT_EQ(files[0], "music.mp3");
	EXPECT_EQ(files[1], "music2.mp3");
}

TEST_F(ParamsTest, positive_print_title)
{
	setup_testing_args({"--print-title", "music.mp3"});
	auto res = read_args(argc, argv);
	auto params = std::get<0>(res);
	auto files = std::get<1>(res);
	EXPECT_EQ(params.size(), 1);
	EXPECT_EQ(params["print-title"], "true");
	EXPECT_EQ(files.size(), 1);
	EXPECT_EQ(files[0], "music.mp3");
}

TEST_F(ParamsTest, positive_print_title_file_name_first)
{
	setup_testing_args({"music.mp3", "--print-title"});
	auto res = read_args(argc, argv);
	auto params = std::get<0>(res);
	auto files = std::get<1>(res);
	EXPECT_EQ(params.size(), 1);
	EXPECT_EQ(params["print-title"], "true");
	EXPECT_EQ(files.size(), 1);
	EXPECT_EQ(files[0], "music.mp3");
}
