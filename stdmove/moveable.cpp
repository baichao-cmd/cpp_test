/*================================================================
*   Copyright (C) 2022 baichao All rights reserved.
*
*   文件名称：moveable.cpp
*   创 建 者：baichao
*   创建日期：2022年05月14日
*   描    述：
*
================================================================*/

#include <iostream>

class Moveable
{
public:
    Moveable() : i(new int(3)) { std::cout << "Moveable()" << std::endl; }
    ~Moveable()
    {
        delete i;
        std::cout << "~Moveable()" << std::endl;
    }
    Moveable(const Moveable &m) : i(new int(*m.i)) { std::cout << "Moveable(const Moveable &m)" << std::endl; }
    Moveable(Moveable &&m) : i(m.i)
    {
        m.i = nullptr;
        std::cout << "Moveable(Moveable &&m) " << std::endl;
    }

    int *i;
};

int main()
{
    Moveable a;
    Moveable c(std::move(a));
    //std::cout<<*a.i<<std::endl;  //a.i此时已经为nullptr
    return 0;
}
