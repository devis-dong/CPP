/*** 
 * @Author: devis dong
 * @Date: 2021-07-21 13:08:48
 * @LastEditTime: 2021-07-22 00:37:20
 * @LastEditors: devis dong
 * @Description: 
 * @FilePath: \C++\test\dssift\test_dssift.cpp
 */


#include <iostream>
#include "dswatch.h"
#include "dssift.cpp"

using namespace ds;

int main()
{
    printf("running...\n");

    Image<unsigned char> img_ori("E:/Coding/C++/bin/imgs/lenna.jpg", 0);
    show_image(img_ori, string("img_ori: ") + to_string(img_ori._h) + " x " + to_string(img_ori._w) + " x " + to_string(img_ori._c));
    Watch mywatch;
    mywatch.start_clock();
    Pyramid<unsigned char> gauss_pyr;
    gauss_pyr.octvs = 5;
    gauss_pyr.intvs = 6;
    gauss_pyr.imgs = new Image<unsigned char>[gauss_pyr.octvs*gauss_pyr.intvs];
    assert (nullptr != gauss_pyr.imgs);
    create_gauss_pyramid<unsigned char>(img_ori, gauss_pyr, 1.6);
    // vector<vector<Image<unsigned char>>> gauss_pyr = create_gauss_pyramid<unsigned char>(img_ori, octvs, intvs, sigma);
    Pyramid<unsigned char> diff_pyr;
    diff_pyr.octvs = 5;
    diff_pyr.intvs = gauss_pyr.intvs-1;
    diff_pyr.imgs = new Image<unsigned char>[diff_pyr.octvs*diff_pyr.intvs];
    create_diff_pyramid<unsigned char>(gauss_pyr, diff_pyr);
    vector<KeyPoint> extrema;
    double contr_thr = 0.03, curv_thr = 10;
    detect_local_extrema(diff_pyr, contr_thr, curv_thr, extrema);
    vector<KeyPoint> feats;
    assign_orient(gauss_pyr, extrema, feats);
    generate_descriptor(feats, gauss_pyr, DESCR_HIST_BINS, DESCR_WINDOW_WIDTH);
    mywatch.stop_clock();
    cout<<"time cost: "<<mywatch.get_duration()<<"s"<<" frame rate:"<<1 / mywatch.get_duration()<<endl;
    cout<<"extrema num: "<<extrema.size()<<endl;
    cout<<"feats num: "<<feats.size()<<endl;
    // for(int i = 0, id = 0; i < gauss_pyr.octvs; ++i)
    // {
    //     for(int j = 0; j < gauss_pyr.intvs; ++j)
    //     {
    //         string winname = "gauss_pyr[";
    //         winname = winname + to_string(i) + "," + to_string(j) + "]";
    //         show_image(gauss_pyr.imgs[id], winname);
    //     }
    // }
    // for(int i = 0, id = 0; i < diff_pyr.octvs; ++i)
    // {
    //     for(int j = 0; j < diff_pyr.intvs; ++j, ++id)
    //     {
    //         string winname = "diff_pyr[";
    //         winname = winname + to_string(i) + "," + to_string(j) + "]";
    //         show_image(diff_pyr.imgs[id], winname);
    //     }
    // }
    wait_key();
    close_all();
    printf("...done.\n");
    system("pause");
    return 0;
}
