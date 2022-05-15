/*================================================================
*   Copyright (C) 2022 baichao All rights reserved.
*   
*   文件名称：construct.cpp
*   创 建 者：baichao
*   创建日期：2022年05月09日
*   描    述：
*
================================================================*/


#include  <iostream>

using  namespace std;

class HasPtrMem                  {
public:
	HasPtrMem() : d(new int(1)) { }
	HasPtrMem(HasPtrMem &h) :d(new int(*h.d)) {}
	~HasPtrMem() {
		delete d;
	}

    int Set(int d){
        *(this->d) = d;
        return *(this->d);
    }
	int *d;
};

int main() {
	HasPtrMem a;
	HasPtrMem b(a);
	cout << *a.d << endl;
	cout << *b.d << endl;
    a.Set(2);
    cout << *a.d << endl;
	cout << *b.d << endl;
}
