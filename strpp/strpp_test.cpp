#include <string>
#include <vector>

#include "strpp/strpp.h"
#include "gtest/gtest.h"

using namespace str;

TEST(Str, Join) {
    std::vector<std::string> strs;

    EXPECT_EQ(join(strs, ""), "");
    EXPECT_EQ(join(strs, " "), "");

    strs.push_back("Sport");
    EXPECT_EQ(join(strs, ""), "Sport");
    EXPECT_EQ(join(strs, " "), "Sport");

    strs.push_back("Club");
    EXPECT_EQ(join(strs, ""), "SportClub");
    EXPECT_EQ(join(strs, " "), "Sport Club");

    strs.push_back("Corinthians");
    EXPECT_EQ(join(strs, ""), "SportClubCorinthians");
    EXPECT_EQ(join(strs, " "), "Sport Club Corinthians");

    strs.push_back("Paulista");
    EXPECT_EQ(join(strs, ""), "SportClubCorinthiansPaulista");
    EXPECT_EQ(join(strs, " "), "Sport Club Corinthians Paulista");
}

TEST(Str, Split) {
    std::vector<std::string> splitted = split("", "");
    EXPECT_EQ(0, int(splitted.size()));

    splitted = split("", " ");
    EXPECT_EQ(0, int(splitted.size()));

    splitted = split("", ",");
    EXPECT_EQ(0, int(splitted.size()));
    
    splitted = split(" ", "");
    EXPECT_EQ(" ", splitted[0]);
    EXPECT_EQ(1, int(splitted.size()));

    splitted = split(" ", " ");
    EXPECT_EQ("", splitted[0]);
    EXPECT_EQ("", splitted[1]);
    EXPECT_EQ(2, int(splitted.size()));

    splitted = split("Sport Club Corinthians Paulista", " ");
    EXPECT_EQ("Sport", splitted[0]);
    EXPECT_EQ("Club", splitted[1]);
    EXPECT_EQ("Corinthians", splitted[2]);
    EXPECT_EQ("Paulista", splitted[3]);
    EXPECT_EQ(4, int(splitted.size()));
}

