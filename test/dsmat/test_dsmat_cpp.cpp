/*** 
 * @Author: devis dong
 * @Date: 2021-07-16 14:32:00
 * @LastEditTime: 2021-07-20 00:15:47
 * @LastEditors: devis dong
 * @Description: 
 * @FilePath: \C++\test\dsmat\test_dsmat_cpp.cpp
 */

#include <iostream>
#include "dswatch.h"
#include "dsmat_cpp.cpp"

using namespace ds;

int main()
{
    printf("running...\n");

    Mat<unsigned char> img("E:/Coding/C++/bin/imgs/lenna.jpg", 1);
    printf("%d x %d x %d\n", (*(img._shape))[0], (*(img._shape))[1], (*(img._shape))[2]);
    Mat<unsigned char>::show(img, "lenna");
    Mat<int> ker({3, 3, 1}, 1);
    Vec<int> step({1, 1, 1});
    Watch mywatch;
    mywatch.start_clock();
    Mat<unsigned char> con = convolve<unsigned char, int, unsigned char>(img, ker, step);
    mywatch.stop_clock();
    cout<<"time cost: "<<mywatch.get_duration()<<"s"<<" frame rate:"<<1/mywatch.get_duration()<<endl;
    Mat<unsigned char> con_c;
    mywatch.start_clock();
    convolve<unsigned char, int, unsigned char>(img, ker, step, con_c);
    mywatch.stop_clock();
    cout<<"time cost: "<<mywatch.get_duration()<<"s"<<" frame rate:"<<1/mywatch.get_duration()<<endl;
    Mat<unsigned char>::show(con_c, "conv");
    Mat<unsigned char>::waitkey();
    Mat<unsigned char>::close();
    printf("...done.\n");
    system("pause");
    return 0;
}
