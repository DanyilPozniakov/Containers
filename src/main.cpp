#include <iostream>
#include "PriorityQueue.h"


int main()
{
    Queue<int> q;
    q.push(1);
    std::cout << "Capacity: " << q.capacity() << "\t Size: " << q.size() << std::endl;
    q.push(2);
    std::cout << "Capacity: " << q.capacity() << "\t Size: " << q.size() << std::endl;
    return 0;
}