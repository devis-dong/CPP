/*** 
 * @Author: devis dong
 * @Date: 2021-07-19 22:34:28
 * @LastEditTime: 2021-07-20 22:48:29
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

    Image<unsigned char> img_ori("E:/Coding/C++/bin/imgs/lenna.jpg", 0);
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
    // int g_shape[3] = {3, 3, 1};
    // img_prime = gaussian_blur(img_ori, g_shape, 0.8);
    int octvs = 5, intvs = 3; double sigma = 1.6;

    Pyramid<unsigned char> gauss_pyr = create_gauss_pyramid<unsigned char>(img_ori, octvs, intvs, sigma);
    // vector<vector<Image<unsigned char>>> gauss_pyr = create_gauss_pyramid<unsigned char>(img_ori, octvs, intvs, sigma);
    Pyramid<unsigned char> diff_pyr = create_diff_pyramid<unsigned char>(gauss_pyr);
    // convolve<unsigned char, double, unsigned char>(img_ori, ker, step, img_prime);
    // int offset[3] = {0, 0, 0};
    // int sub_len[3] = {img_ori._h, img_ori._w, 1};
    // Image<unsigned char> subimg = img_ori.subimage(offset, sub_len);
    // double rate[3] = {0.5, 0.5, 1};
    // img_prime = sample_image(img_ori, rate);
    mywatch.stop_clock();
    cout<<"time cost: "<<mywatch.get_duration()<<"s"<<" frame rate:"<<1 / mywatch.get_duration()<<endl;
    // show_image(img_prime, "img_prime: " + to_string(img_prime._h) + " x " + to_string(img_prime._w) + " x " + to_string(img_prime._c));
    // show_image(subimg, "subimg");
    // for(int i = 0; i < gauss_pyr.octvs; ++i)
    // {
    //     for(int j = 0; j < gauss_pyr.intvs; ++j)
    //     {
    //         string winname = "pyr[";
    //         winname = winname + to_string(i) + "," + to_string(j) + "]";
    //         show_image(gauss_pyr.imgs[i][j], winname);
    //     }
    // }
    for(int i = 0; i < diff_pyr.octvs; ++i)
    {
        for(int j = 0; j < diff_pyr.intvs; ++j)
        {
            string winname = "pyr[";
            winname = winname + to_string(i) + "," + to_string(j) + "]";
            show_image(diff_pyr.imgs[i][j], winname);
        }
    }
    destroy_pyramid(gauss_pyr);
    destroy_pyramid(diff_pyr);
    wait_key();
    close_all();
    printf("...done.\n");
    system("pause");
    return 0;
}
