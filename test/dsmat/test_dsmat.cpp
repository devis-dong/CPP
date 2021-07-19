/*** 
 * @Author: devis dong
 * @Date: 2021-07-16 14:32:00
 * @LastEditTime: 2021-07-19 14:06:59
 * @LastEditors: devis dong
 * @Description: 
 * @FilePath: \C++\test\dsmat\test_dsmat.cpp
 */

#include <iostream>
#include "dswatch.h"
#include "dsmat.cpp"

using namespace ds;

int main()
{
    printf("running...\n");

    Mat<unsigned char> img("E:/Coding/C++/bin/imgs/lenna.jpg", 0);
    printf("%d x %d x %d\n", img._shape[0], img._shape[1], img._shape[2]);
    Mat<unsigned char>::show(img, "lenna");
    Mat<double> ker({3, 3, 1}, 1.0);
    int step[3] = {1, 1, 1};
    Watch mywatch;
    mywatch.start_clock();
    Mat<unsigned char> con = convolve<unsigned char, double, unsigned char>(img, ker, step);
    mywatch.stop_clock();
    cout<<"time cost: "<<mywatch.get_duration()<<"s"<<" frame rate:"<<1/mywatch.get_duration()<<endl;
    Mat<unsigned char> con_c;
    mywatch.start_clock();
    convolve<unsigned char, double, unsigned char>(img, ker, step, con_c);
    mywatch.stop_clock();
    cout<<"time cost: "<<mywatch.get_duration()<<"s"<<" frame rate:"<<1/mywatch.get_duration()<<endl;
    Mat<unsigned char>::show(con_c, "conv");
    Mat<unsigned char>::waitkey();
    Mat<unsigned char>::close();
    printf("...done.\n");
    system("pause");
    return 0;
}
