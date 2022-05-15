/*================================================================
*   Copyright (C) 2022 baichao All rights reserved.
*
*   文件名称：lock_guard.cpp
*   创 建 者：baichao
*   创建日期：2022年05月25日
*   描    述：
*
================================================================*/

#include <iostream>
#include <mutex>

std::mutex mutex;

void safe_thread()
{
    try
    {
        std::lock_guard<std::mutex> _guard(mutex);
        throw std::logic_error("logic error");
    }
    catch (std::exception &ex)
    {
        std::cerr << "[caught] " << ex.what() << std::endl;
    }
}
int main()
{
    safe_thread();
    // 此处仍能上锁
    mutex.lock();
    std::cout << "OK, still locked" << std::endl;
    mutex.unlock();

    return 0;
}
