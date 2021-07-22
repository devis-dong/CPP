/*** 
 * @Author: devis dong
 * @Date: 2021-07-21 13:08:48
 * @LastEditTime: 2021-07-23 01:45:46
 * @LastEditors: devis dong
 * @Description: 
 * @FilePath: \C++\test\dssift\test_dssift.cpp
 */


#include <iostream>
#include "dswatch.h"
#include "dssift.cpp"
// #include "xfeatures2d.hpp"

using namespace ds;
// using namespace cv;

int main()
{
    loginfo("running...\n");

    // Image img_ori("E:/Coding/C++/bin/imgs/conan0.jpg", 1);
    // show_image(img_ori, string("img_ori: ") + to_string(img_ori._h) + " x " + to_string(img_ori._w) + " x " + to_string(img_ori._c));
    Watch mywatch;
    mywatch.start_clock();
    // double rate[3] = {4, 4, 1};
    // Image simg = sample_image(img_ori, rate);
    // show_image(simg, "simg");
    // Image img_gray;
    // bgr2gray(img_ori, img_gray);
    // show_image(img_gray, "img_gray");
    // int shape[3] = {3, 3, 1};
    // Image gimg = gaussian_blur(img_ori, shape, SIFT_SIGMA);
    // show_image(gimg, "gimg");
    /*=======================================================================================*/
    // Image img_gray;
    // create_init_smooth_gray(img_ori, img_gray, SIFT_SIGMA, SIFT_IMG_UPSAMPLE);
    // show_image(img_gray, string("img_gray: ") + to_string(img_gray._h) + " x " + to_string(img_gray._w) + " x " + to_string(img_gray._c));
    // loginfo("step 1: building gaussian pyramid.");
    // Pyramid gauss_pyr;
    // gauss_pyr.octvs = log2(min(img_gray._h, img_gray._w))-3;
    // gauss_pyr.intvs = SIFT_INTVS+3;
    // gauss_pyr.imgs = new Image[gauss_pyr.octvs*gauss_pyr.intvs];
    // assert (nullptr != gauss_pyr.imgs);
    // create_gauss_pyramid(img_gray, gauss_pyr, SIFT_SIGMA);
    // // for(int i = 0, id = 0; i < gauss_pyr.octvs; ++i)
    // // {
    // //     for(int j = 0; j < gauss_pyr.intvs; ++j)
    // //     {
    // //         string winname = "gauss_pyr[";
    // //         winname = winname + to_string(i) + "," + to_string(j) + "]";
    // //         show_image(gauss_pyr.imgs[id], winname);
    // //     }
    // // }

    // loginfo("step 2: building difference of gaussian pyramid.");
    // Pyramid diff_pyr;
    // diff_pyr.octvs = gauss_pyr.octvs;
    // diff_pyr.intvs = gauss_pyr.intvs-1;
    // diff_pyr.imgs = new Image[diff_pyr.octvs*diff_pyr.intvs];
    // create_diff_pyramid(gauss_pyr, diff_pyr);
    // // for(int i = 0, id = 0; i < diff_pyr.octvs; ++i)
    // // {
    // //     for(int j = 0; j < diff_pyr.intvs; ++j, ++id)
    // //     {
    // //         string winname = "diff_pyr[";
    // //         winname = winname + to_string(i) + "," + to_string(j) + "]";
    // //         show_image(diff_pyr.imgs[id], winname);
    // //     }
    // // }

    // loginfo("step 3: detect the local extrema of the dog.");
    // vector<KeyPoint> extrema;
    // detect_local_extrema(diff_pyr, SIFT_CONTR_THR, SIFT_CURV_THR, extrema);
    // calculate_scale(extrema, SIFT_SIGMA, diff_pyr.intvs);
    // if(SIFT_IMG_UPSAMPLE) downsize_feats(extrema);
    // loginfo("local extema num: %d", extrema.size());

    // loginfo("step 4: intially generate keypoints.");
    // vector<KeyPoint> feats;
    // assign_orient(gauss_pyr, extrema, SIFT_ORI_HIST_BINS, feats);

    // loginfo("step 5: generate descriptor for each keypoint.");
    // generate_descriptor(feats, gauss_pyr, SIFT_DESCR_HIST_BINS, SIFT_DESCR_WINDOW_WIDTH);
    // delete[] gauss_pyr.imgs;
    // delete[] diff_pyr.imgs;

    /*=======================================================================================*/
    Image img0("E:/Coding/C++/bin/imgs/conan0.jpg", 1);
    vector<KeyPoint> feats0;
    get_sift_features(img0, feats0);
    mywatch.stop_clock();
    loginfo("img0 feats num: %d", feats0.size());
    loginfo("img0 time cost: %fs, frame rate: %f.", mywatch.get_duration(), 1 / mywatch.get_duration());
    draw_key_points(img0, feats0);
    draw_sift_features(img0, feats0);
    show_image(img0, "img0");

    Image img1("E:/Coding/C++/bin/imgs/conan1.jpg", 1);
    vector<KeyPoint> feats1;
    get_sift_features(img1, feats1);
    mywatch.stop_clock();
    loginfo("img1 feats num: %d", feats1.size());
    loginfo("img1 time cost: %fs, frame rate: %f.", mywatch.get_duration(), 1 / mywatch.get_duration());
    draw_key_points(img1, feats1);
    draw_sift_features(img1, feats1);
    show_image(img1, "img1");

    wait_key();
    close_all();
    loginfo("...done.\n");
    system("pause");
    return 0;
}
