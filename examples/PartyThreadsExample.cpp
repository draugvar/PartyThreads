#include <iostream>
#include "PartyThreads.h"

PartyThreads::Pool pt;

void init()
{
    auto lambda = [] (const int i)
    {
        std::cout << "Hello, " << i << std::endl;
    };
    pt.push(lambda, 1);
}

int main()
{
    auto future = std::async(std::launch::async, init);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    pt.stop();
    return 0;
}
