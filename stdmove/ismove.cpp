/*================================================================
*   Copyright (C) 2022 baichao All rights reserved.
*   
*   文件名称：ismove.cpp
*   创 建 者：baichao
*   创建日期：2022年05月14日
*   描    述：
*
================================================================*/


// is_move_constructible example
#include <iostream>
#include <type_traits>

struct A { };
struct B { B(B&&) = delete; };

int main() {
  std::cout << std::boolalpha;
  std::cout << "is_move_constructible:" << std::endl;
  std::cout << "int: " << std::is_move_constructible<int>::value << std::endl;
  std::cout << "A: " << std::is_move_constructible<A>::value << std::endl;
  std::cout << "B: " << std::is_move_constructible<B>::value << std::endl;
  return 0;
}