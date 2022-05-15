/*================================================================
*   Copyright (C) 2022 baichao All rights reserved.
*
*   文件名称：forward.cpp
*   创 建 者：baichao
*   创建日期：2022年05月15日
*   描    述：
*
================================================================*/

// forward example
#include <utility>  // std::forward
#include <iostream> // std::cout

// function with lvalue and rvalue reference overloads:
void overloaded(const int &x) { std::cout << "[lvalue]"; }
void overloaded(int &&x) { std::cout << "[rvalue]"; }

// function template taking rvalue reference to deduced type:
template <class T>
void fn(T &&x)
{
    overloaded(x);                  // always an lvalue
    overloaded(std::forward<T>(x)); // rvalue if argument is rvalue
}

int main()
{
    int a;

    std::cout << "calling fn with lvalue: ";
    fn(a);
    std::cout << '\n';

    std::cout << "calling fn with rvalue: ";
    fn(std::move(a));
    std::cout << '\n';

    return 0;
}