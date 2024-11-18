#include "gtest/gtest.h"
#include <MyUMap.hpp>


TEST(UMapTest, addTEST)
{
    UMap<std::string,int> map;
    map.add("Hello",1);
    EXPECT_EQ(map.getValue("Hello"),1);
}

TEST(UMapTest, addTEST2)
{
    UMap<std::string,int> map;
    map.add("Hello",1);
    map.add("World",2);
    map.add("!",3);
    EXPECT_EQ(map.getValue("Hello"),1);
    EXPECT_EQ(map.getValue("World"),2);
    EXPECT_EQ(map.getValue("World"),3);

}

TEST(UMapTest, updateTEST)
{
    UMap<std::string,int> map;
    map.add("Hello",1);
    map.add("Hello",2);
    EXPECT_EQ(map.getValue("Hello"),2);
    EXPECT_EQ(map.size(),1);
}

TEST(UMapTest, updateTEST2)
{
    // TODO: if the size in`t multiple of 10 - the structure breaks down! HOW TO FIX IT?
    UMap<std::string,int> map;
    //MyUMap<std::string,int> map(2);
    map.add("Hello",1);
    map.add("Hello",2);
    EXPECT_EQ(map.getValue("Hello"),2);
    EXPECT_EQ(map.size(),1);
}

TEST(UMapTest, updateTEST3)
{
    UMap<std::string,int> map;
    map.add("Hello",1);
    map.add("Hello",2);
    map.add("Hello",3);
    EXPECT_EQ(map.getValue("Hello"),3);
    EXPECT_EQ(map.size(),1);
}

TEST(UMapTest, updateTEST4)
{
    UMap<std::string,int> map;
    std::vector<std::string> arr = {"word1","word2","word3","word4","word5",
                                    "word6","word7","word8","word9","word10",
                                    "word11", "word12"  };

    int counter = 1;
    for(const auto word : arr)
    {
        map.add(word,counter);
        ++counter;
    }

    map.add("word1",100);
    EXPECT_EQ(map.getValue("word1"),100);



}

TEST(UMapTest, getTEST)
{
    UMap<std::string,int> map;
    std::vector<std::string> arr = {"word1","word2","word3","word4","word5",
                                    "word6","word7","word8","word9","word10",
                                    "word11", "word12"  };

    std::size_t counter = 1;
    for(const auto word : arr)
    {
        map.add(word,counter);
        ++counter;
    }

    counter = 1;
    for(const auto word : arr)
    {
        auto value = map.getPair(word);
        EXPECT_EQ(value.value().first,word);
        EXPECT_EQ(value.value().first,counter);
        ++counter;
    }
    EXPECT_EQ(map.size(),12);
}


TEST(UMapTest, getPairTEST)
{
    UMap<std::string,int> map;
    map.add("Hello",1);
    auto pair = map.getPair("Hello");

    EXPECT_EQ(pair.value().first,"Hello");
    EXPECT_EQ(pair.value().first,1);
}


