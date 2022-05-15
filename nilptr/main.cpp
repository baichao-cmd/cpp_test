#include<iostream>

using namespace std;

int* func(){
    int *a = new int(1);
    return a;
} 

int main(){
    cout<<"好久不见"<<endl;
    int* a = func();
    cout<<*a<<endl;
    cout<<*a<<endl;
    cout<<*a<<endl;
    cout<<*a<<endl;
    return 0;
}