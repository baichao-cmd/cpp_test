/*================================================================
*   Copyright (C) 2022 baichao All rights reserved.
*
*   文件名称：const_left_value.cpp
*   创 建 者：baichao
*   创建日期：2022年05月10日
*   描    述：
*
================================================================*/

#include <iostream>

using namespace std;

struct Copyable
{
	Copyable() {}
	Copyable(const Copyable &c)
	{
		cout << "Copied" << endl;
	}
	int a{180817};

public:
	int setA(int a) { this->a = a; }
	int getA() { return a; }
};
Copyable ReturnRvalue() { return Copyable(); }
void AcceptVal(Copyable) {}

void AcceptRef(Copyable &&c)
{
	int a = 1123;
	c.setA(a);
	cout << c.getA() << endl;
}

int main()
{
	cout << "Passbyvalue:" << endl;
	AcceptVal(ReturnRvalue());
	cout << "Pass by reference: " << endl;
	AcceptRef(ReturnRvalue());
}
