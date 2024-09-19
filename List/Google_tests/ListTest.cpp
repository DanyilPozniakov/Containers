#include "gtest/gtest.h"
#include "List.h"

TEST(ListTest, AddElement) {
    List<int> list;
    list.push_back(5);
    EXPECT_EQ(list.size(), 1);
}

TEST(ListTest, AddElement5) {
    List<int> list;
    list.push_back(5);
    list.push_back(5);
    list.push_back(5);
    list.push_back(5);
    list.push_back(5);
    EXPECT_EQ(list.size(), 5);
}

TEST(ListTest, popftont) {
    List<int> list;
    list.push_back(5);
    list.pop_front();
    EXPECT_EQ(list.size(), 0);
    EXPECT_TRUE(list.isEmpty());
}
