/*================================================================
*   Copyright (C) 2022 baichao All rights reserved.
*
*   文件名称：huge_mem.cpp
*   创 建 者：baichao
*   创建日期：2022年05月14日
*   描    述：
*
================================================================*/

#include <iostream>

using namespace std;

class HugeMem
{
public:
    HugeMem(int size) : sz(size > 0 ? size : 1)
    {
        c = new int[sz];
    }
    ~HugeMem()
    {
        delete[] c;
    };
    HugeMem(HugeMem &&hm) : sz(hm.sz), c(hm.c)
    {
        hm.c = nullptr;
    }
    int *c;
    int sz;
};
class Moveable
{
public:
    Moveable() : i(new int(3)), h(1024){}
    ~Moveable(){delete i;}
    Moveable(Moveable &&m) : i(m.i), h(move(m.h))
    {
        m.i = nullptr;
        std::cout << "Moveable(Moveable &&m)" << std::endl;
    }
    int *i;
    HugeMem h;
};
Moveable GetTemp()
{
    Moveable tmp = Moveable();
    cout << hex << "Huge Mem from " << __func__
         << " @" << tmp.h.c << endl;
    return tmp;
}

int main()
{
    Moveable a(GetTemp());
    cout << hex << "Huge Mem from " << __func__
         << " e" << a.h.c << endl;
}
