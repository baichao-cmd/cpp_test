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

class HasPtrMem {
public:
	HasPtrMem() : d(new int(0)) {
		cout << "Construct: " << ++n_cstr << endl;
	}
	HasPtrMem(const HasPtrMem &h) : d(new int(*h.d)) {
		cout << "Copy construct: " << ++n_cptr << endl;
	}
	~HasPtrMem() {
		cout << "Destruct: " << ++n_dstr << endl;
	}

	int * d;
	static int n_cstr;
	static int n_dstr;
	static int n_cptr;
};

int HasPtrMem::n_cstr = 0;
int HasPtrMem::n_dstr = 0;
int HasPtrMem::n_cptr = 0;

HasPtrMem GetTemp() {
	return HasPtrMem();
}

int main() {
	HasPtrMem a = GetTemp();	
	return 0;
}
