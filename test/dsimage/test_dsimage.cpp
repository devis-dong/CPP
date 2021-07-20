/*** 
 * @Author: devis dong
 * @Date: 2021-07-19 22:34:28
 * @LastEditTime: 2021-07-20 11:04:26
 * @LastEditors: devis dong
 * @Description: 
 * @FilePath: \C++\test\dsimage\test_dsimage.cpp
 */

#include <iostream>
#include "dswatch.h"
#include "dsimage.cpp"

using namespace ds;

int main()
{
    printf("running...\n");

    Image<unsigned char> img_ori("E:/Coding/C++/bin/imgs/lenna.jpg", 1);
    show_image(img_ori, string("img_ori: ") + to_string(img_ori._h) + " x " + to_string(img_ori._w) + " x " + to_string(img_ori._c));
    Image<double> ker(7, 7, 1, 1.0/49.0);
    int step[3] = {3, 3, 1}, offset[3] = {0, 0, 0}, sub_len[3] = {img_ori._h, img_ori._w, 1};
    Image<unsigned char> img_prime;
    Watch mywatch;
    mywatch.start_clock();
    // img_prime = convolve<unsigned char, double, unsigned char>(img, ker, step);
    // convolve<unsigned char, double, unsigned char>(img, ker, step, img_prime);
    // Image<unsigned char> subimg = img.subimage(offset, sub_len);
    double rate[3] = {0.5, 0.5, 1};
    img_prime = sample(img_ori, rate);
    mywatch.stop_clock();
    cout<<"time cost: "<<mywatch.get_duration()<<"s"<<" frame rate:"<<1 / mywatch.get_duration()<<endl;
    show_image(img_prime, "img_prime" + to_string(img_prime._h) + " x " + to_string(img_prime._w) + " x " + to_string(img_prime._c));
    // show_image(subimg, "subimg");
    wait_key();
    close_all();
    printf("...done.\n");
    system("pause");
    return 0;
}
