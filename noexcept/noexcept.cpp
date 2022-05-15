/*================================================================
*   Copyright (C) 2022 baichao All rights reserved.
*
*   文件名称：noexcept.cpp
*   创 建 者：baichao
*   创建日期：2022年05月14日
*   描    述：
*
================================================================*/

#include <iostream>
#include <utility>
#include <vector>

void may_throw();
void no_throw() noexcept;
auto lmay_throw = [] {};
auto lno_throw = []() noexcept {};
class T
{
public:
    ~T() {} // 因为显式声明了析构函数，所以不会隐式提供移动构造函数，从右值构造的时候会使用复制构造函数
            // 复制构造函数为 noexcept
};
class U
{
public:
    ~U() {} // 因为显式声明了析构函数，所以不会隐式提供移动构造函数，从右值构造的时候会使用复制构造函数
            // 复制构造函数为 noexcept(false),因为std::vector<int> v的存在
    std::vector<int> v;
};
class V
{
public:
    std::vector<int> v;
};

int main()
{
    T t;
    U u;
    V v;

    std::cout << std::boolalpha
              << "Is may_throw() noexcept? " << noexcept(may_throw()) << '\n'     // false
              << "Is no_throw() noexcept? " << noexcept(no_throw()) << '\n'       // true
              << "Is lmay_throw() noexcept? " << noexcept(lmay_throw()) << '\n'   // false
              << "Is lno_throw() noexcept? " << noexcept(lno_throw()) << '\n'     // true
              << "Is ~T() noexcept? " << noexcept(std::declval<T>().~T()) << '\n' //从c++11起析构函数默认带有noexcept属性
              // 注：以下各项测试也默认 ~T() 为 noexcept
              // 因为 noexccept 中的表达式构造并销毁了临时量
              << "Is T(rvalue T) noexcept? " << noexcept(T(std::declval<T>())) << '\n' //移动构造被显式析构阻挡，但是复制构造依旧为noexcept
              << "Is T(lvalue T) noexcept? " << noexcept(T(t)) << '\n'                 //复制构造为noexcept
              << "Is U(rvalue U) noexcept? " << noexcept(U(std::declval<U>())) << '\n' //移动构造被显式析构阻挡，复制构造为noexcept(false),因为std::vector<int> v的存在
              << "Is U(lvalue U) noexcept? " << noexcept(U(u)) << '\n'                 //复制构造为noexcept(false),因为std::vector<int> v的存在
              << "Is V(rvalue V) noexcept? " << noexcept(V(std::declval<V>())) << '\n' //移动构造隐式存在，且为noexcept
              << "Is V(lvalue V) noexcept? " << noexcept(V(v)) << '\n';                //复制构造为noexcept(false),因为std::vector<int> v的存在
}
