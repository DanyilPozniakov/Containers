#include "gtest/gtest.h"
#include "List.h"

//constructor tests
TEST(ListTest, DefaultConstructorTest){
    List<int> list;
    EXPECT_TRUE(list.isEmpty());
    EXPECT_EQ(list.size(),0);
    EXPECT_FALSE(list.begin());
}

TEST(ListTest,InitializerListConstructorTest){
    List<int> list = {1,2,3,4,5};
    EXPECT_EQ(list.size(),5);
    EXPECT_TRUE(list.begin());
    EXPECT_FALSE(list.isEmpty());
}

TEST(ListTest,CopyConstructorTest){
    List<int> list = {1,2,3,4,5};
    List<int> list2 = List<int>(list);

    //list
    EXPECT_FALSE(list2.isEmpty());
    EXPECT_EQ(list2.size(),5);
    EXPECT_TRUE(list2.begin());

    //list2
    EXPECT_FALSE(list2.isEmpty());
    EXPECT_EQ(list2.size(),5);
    EXPECT_TRUE(list2.begin());

    //
    EXPECT_EQ(*list.begin(),*list2.begin());
}

TEST(ListTest,MoveConstructorTest){
    List<int> list = {1,2,3,4,5};
    List<int> list2 = std::move(list);

    //list is empty
    EXPECT_TRUE(list.isEmpty());
    EXPECT_EQ(list.size(),0);
    EXPECT_FALSE(list.begin());

    //list2
    EXPECT_FALSE(list2.isEmpty());
    EXPECT_EQ(list2.size(),5);
    EXPECT_TRUE(list2.begin());
}

TEST(ListTest,PushBack){
    List<int> list = {1,2,3,4};
    list.push_back(5);

    EXPECT_EQ(list.size(),5);
    EXPECT_EQ(list.back(),5);
}

TEST(ListTest,PopFront){
    List<int> list = {1,2,3,4,5};
    list.pop_front();

    EXPECT_EQ(list.size(),4);
    EXPECT_EQ(list.front(),2);
}

TEST(ListTest,InsertTest){
    List<int> list = {1,2,4,5};
    auto iter =  std::lower_bound(list.begin(),list.end(),4);
    list.insert(iter,3);
    int n = 1;
    for(auto num : list)
    {
        EXPECT_EQ(num,n);
        ++n;
    }
    EXPECT_EQ(list.size(),5);
}

TEST(ListTest,EraseTest){
    List<int> list = {1,2,3,4,5};
    auto iter =  std::lower_bound(list.begin(),list.end(),4);
    list.erase(iter);
    EXPECT_EQ(list.size(),4);
    EXPECT_FALSE(std::find(list.begin(),list.end(),4));
}



