/*================================================================
*   Copyright (C) 2022 baichao All rights reserved.
*
*   文件名称：call_once.cpp
*   创 建 者：baichao
*   创建日期：2022年05月25日
*   描    述：
*
================================================================*/

#include <iostream>
#include <thread>
#include <mutex>

void initialize()
{
    std::cout << __FUNCTION__ << std::endl;
}

std::once_flag of;
void my_thread()
{
    std::call_once(of, initialize);
}

int main()
{
    std::thread threads[10];
    for (std::thread &thr : threads)
    {
        thr = std::thread(my_thread);
    }
    for (std::thread &thr : threads)
    {
        thr.join();
    }
    return 0;
}
// 仅输出一次：initialize
