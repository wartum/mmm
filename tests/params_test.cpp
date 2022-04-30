#include <gtest/gtest.h>
#include <stdexcept>
#include <string.h>
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

TEST_F(ParamsTest, negative_no_params)
{
	setup_testing_args({});
	EXPECT_THROW(read_params(argc, argv), std::invalid_argument);
}

TEST_F(ParamsTest, negative_file_path_missing)
{
	setup_testing_args({"--print-title", "--print-author", "--print-album"});
	EXPECT_THROW(read_params(argc, argv), std::invalid_argument);
}

TEST_F(ParamsTest, negative_param_not_prefixed)
{
	setup_testing_args({"file-path"});
	EXPECT_THROW(read_params(argc, argv), std::invalid_argument);
}

TEST_F(ParamsTest, positive_get_file_path)
{
	setup_testing_args({"--file-path", "music.mp3"});
	auto params = read_params(argc, argv);
	EXPECT_EQ(params.size(), 1);
	EXPECT_EQ(params["file-path"], "music.mp3");
}

TEST_F(ParamsTest, positive_get_print_title)
{
	setup_testing_args({"--file-path", "music.mp3", "--print-title"});
	auto params = read_params(argc, argv);
	EXPECT_EQ(params.size(), 2);
	EXPECT_EQ(params["print-title"], "true");
}
