/*================================================================
*   Copyright (C) 2022 baichao All rights reserved.
*
*   文件名称：virtual_table.cpp
*   创 建 者：baichao
*   创建日期：2022年05月28日
*   描    述：
*
================================================================*/

/*——参考自C++ primer一书中的案例——*/
#include "iostream"
using namespace std;
class Base
{
public:
    int a;
    virtual void print1(){};
    virtual void print2() { cout << "Base" << endl; };
};
class Derived : public Base
{
public:
    int b;
    // void print2() { cout << "Derived" << endl; }; // redefined
    //  virtual void print3(){};                      // new
};
int main()
{
    Derived A;
    Base *B = &A; //调用派生类Derived的成员函数 输出Derived
    B->print2();
    //验证虚表指针占空间32位时输出8,12
    cout << sizeof(Base) << "," << sizeof(Derived) << endl;
    return 0;
}
