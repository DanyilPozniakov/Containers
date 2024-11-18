#include <iostream>
#include "../lib/MyUMap.hpp"
#include <unordered_map>
#include <set>
#pragma pack(1)


int main()
{

    std::vector<std::string> set = {"Word1", "Word2", "Word3", "Word4", "Word5",
        "Word6","Word7","Word8","Word9","Word10","Word11","Word12","Word13",
        "Word14","Word15","Word16","Word17","Word18","Word19" };

    UMap<std::string,int> map{};



    // map.Add("Hello",1);
    // map.Add("World",2);


    // for(auto [key,value] : map)
    // {
    //     std::cout << key << "\t" << value << "\n";
    // }
    // std::cout << map.size();



    map.add("Word2",2);
    map.add("Word3",3);
    map.add("Word4",4);
    map.add("Word5",5);
    map.add("Word6",6);
    map.add("Word7",7);
    map.add("Word8",8);
    map.add("Word9",9);
    map.add("Word10",10);
    map.add("Word11",11);
    map.add("Word12",12);
    map.add("Word13",13);
    map.add("Word14",14);
    map.add("Word15",15);
    map.add("Word16",16);
    map.add("Word17",17);
    map.add("Word18",18);
    map.add("Word19",19);

    for(auto [key,value] : map)
    {
        std::cout << key << "\t" << value << "\n";
    }
    std::cout << "size:" <<  map.size() << "cap:" << map.capacity() << "\n";

    for(auto word : set)
    {
        std::cout << map.getValue(word).value() << "\n";
    }
    return 0;
}
