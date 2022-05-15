/*================================================================
*   Copyright (C) 2022 baichao All rights reserved.
*
*   文件名称：member_function.cpp
*   创 建 者：baichao
*   创建日期：2022年05月24日
*   描    述：
*
================================================================*/
#include <thread>
#include <iostream>

class Greet
{
    const char *owner = "Greet";

public:
    void SayHello(const char *name)
    {
        std::cout << "Hello " << name << " from " << this->owner << std::endl;
    }
};
int main()
{
    Greet greet;

    std::thread thread(&Greet::SayHello, &greet, "C++11");
    thread.join();

    return 0;
}
//输出：Hello C++11 from Greet