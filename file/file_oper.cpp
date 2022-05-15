/*================================================================
*   Copyright (C) 2022 baichao All rights reserved.
*
*   文件名称：file_oper.cpp
*   创 建 者：baichao
*   创建日期：2022年06月17日
*   描    述：
*
================================================================*/

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    char *c = (char *)malloc(5);
    int fd = open("data.txt", O_RDWR | O_CREAT, S_IRWXU | S_IRWXG);
    int w_size = write(fd, "01234567890123456789", 20);
    if (w_size == -1 || w_size != 20)
    {
        std::cout << "write file failed." << std::endl;
    }
    int newOffset = lseek(fd, 9, SEEK_SET);
    int r_size = read(fd, c, 5);
    if (r_size == -1 || r_size != 5)
    {
        std::cout << "read file failed." << std::endl;
    }
    std::cout << c << std::endl;
    return 0;
}
