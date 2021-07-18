/*** 
 * @Author: devis dong
 * @Date: 2021-07-16 14:32:00
 * @LastEditTime: 2021-07-17 23:38:28
 * @LastEditors: devis dong
 * @Description: 
 * @FilePath: \C++\test\dsimage\test_dsimage.cpp
 */

#include <iostream>
#include "dsimage.h"

using namespace ds;

int main()
{
    printf("running...\n");

    Image<unsigned char> img("E:/Coding/C++/bin/imgs/lenna.jpg");
    printf("%d, %d, %d\n", img.height(), img.width(), img.channels());
    img.show("lenna");
    img.waitkey();
    img.close();
    printf("...done.\n");
    system("pause");
    return 0;
}
