/*** 
 * @Author: devis dong
 * @Date: 2021-07-19 22:34:28
 * @LastEditTime: 2021-07-20 19:30:38
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

    Watch mywatch;
    mywatch.start_clock();
    Image<unsigned char> img_prime;
    // int ker_shape[3] = {3, 3, 1};
    // Image<double> ker = generate_gaussian_mat<double>(ker_shape, 0.8, true);
    // print_image(ker);
    // int pad_size[3] = {1, 1, 0};
    // int step[3] = {1, 1, 1};
    // img_prime = convolve<unsigned char, double, unsigned char>(img_ori, ker, step, pad_size);
    int g_shape[3] = {3, 3, 1};
    img_prime = gaussian_blur(img_ori, g_shape, 0.8);
    // convolve<unsigned char, double, unsigned char>(img_ori, ker, step, img_prime);
    // int offset[3] = {0, 0, 0};
    // int sub_len[3] = {img_ori._h, img_ori._w, 1};
    // Image<unsigned char> subimg = img_ori.subimage(offset, sub_len);
    // double rate[3] = {0.5, 0.5, 1};
    // img_prime = sample(img_ori, rate);
    mywatch.stop_clock();
    cout<<"time cost: "<<mywatch.get_duration()<<"s"<<" frame rate:"<<1 / mywatch.get_duration()<<endl;
    show_image(img_prime, "img_prime: " + to_string(img_prime._h) + " x " + to_string(img_prime._w) + " x " + to_string(img_prime._c));
    // show_image(subimg, "subimg");
    wait_key();
    close_all();
    printf("...done.\n");
    system("pause");
    return 0;
}
