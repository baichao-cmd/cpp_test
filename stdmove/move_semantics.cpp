/*================================================================
*   Copyright (C) 2022 baichao All rights reserved.
*   
*   文件名称：move_semantics.cpp
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
	HasPtrMem(HasPtrMem &&h) : d(h.d) {
		h.d = nullptr;     //将临时值得指针置为null
		cout << "Move construct: " << ++n_mvtr << endl;
	}
	~HasPtrMem() {
		delete d;
		cout << "Destruct: " << ++n_dstr << endl;
	}

	int * d;
	static int n_cstr;
	static int n_dstr;
	static int n_cptr;
	static int n_mvtr;
};

int HasPtrMem::n_cstr = 0;
int HasPtrMem::n_dstr = 0;
int HasPtrMem::n_cptr = 0;
int HasPtrMem::n_mvtr = 0;

HasPtrMem GetTemp() {
	HasPtrMem h;
	     cout << "Resource from " << __func__ << ":" << hex << h.d << endl;
	return h;
}



int main() {
	HasPtrMem a = GetTemp();

	return 0;
}
