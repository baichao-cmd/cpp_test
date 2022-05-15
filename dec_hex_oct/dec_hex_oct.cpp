/*================================================================
*   Copyright (C) 2022 baichao All rights reserved.
*   
*   文件名称：dec_hex_oct.cpp
*   创 建 者：baichao
*   创建日期：2022年05月09日
*   描    述：
*
================================================================*/


#include <iostream>

int main () {
  int n = 20;
  std::cout << std::dec << n << std::endl;   //10进制
  std::cout << std::hex << n << std::endl;   //16进制
  std::cout << std::oct << n << std::endl;   //8进制
  return 0;
}
