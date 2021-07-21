/*** 
 * @Author: devis dong
 * @Date: 2021-07-21 13:05:14
 * @LastEditTime: 2021-07-22 00:35:13
 * @LastEditors: devis dong
 * @Description: 
 * @FilePath: \C++\src\dssift\dssift.h
 */

#include "dsimage.cpp"

namespace ds
{
    #define INIT_SIGMA 0.5
    #define SIGMA 1.6
    #define INTERVALS 3
    
    #define RATIO 10
    #define MAX_INTERPOLATION_STEPS 5
    #define DXTHRESHOLD 0.03                             //【6】|D(x^)| < 0.03   0.03极值点太多  
    
    #define ORI_HIST_BINS 36
    #define ORI_SIGMA_TIMES 1.5  
    #define ORI_WINDOW_RADIUS 3.0 * ORI_SIGMA_TIMES 
    #define ORI_SMOOTH_TIMES 2  
    #define ORI_PEAK_RATIO 0.8  
    #define FEATURE_ELEMENT_LENGTH 128
    #define DESCR_HIST_BINS 8
    #define IMG_BORDER 5
    #define DESCR_WINDOW_WIDTH 4
    #define DESCR_SCALE_ADJUST 3
    #define DESCR_MAG_THR 0.2
    #define INT_DESCR_FCTR 512.0
    
    template <typename T>
    struct Pyramid
    {
        Image<T>* imgs;
        int octvs, intvs;
    };

    struct KeyPoint
    {  
        int    octv, intv, y, x; // location of keypoint
        double offset_intv, offset_y, offset_x; // offset to extremum
        double sigma;
        double dy, dx;  // coordinate of keypoint in original image
        double octv_sigma;
        double ori;
        int descr_length;
        double descriptor[FEATURE_ELEMENT_LENGTH];
        double val;
    };

    // template <typename T>
    // vector<vector<Image<T>>> create_gauss_pyramid(I Image<T>& img, I const int octvs, I const int intvls, I const double sigma);

    template <typename T>
    void create_gauss_pyramid(I Image<T>& img, I O Pyramid<T>& pyr, I const double sigma=SIGMA);

    template <typename T>
    void create_diff_pyramid(I const Pyramid<T>& gauss_pyr, I O Pyramid<T>& diff_pyr);

    template <typename T>
    bool is_extremum(I const Pyramid<T>& pyr, I const int octv, I const int intv, I const int y, I const int x);

    template <typename T>
    void detect_local_extrema(I const Pyramid<T>& pyr, I const double contr_thr, I const int curv_thr, O vector<KeyPoint>& keypoints);

    template <typename T>
    int interplate_extremum(I const Pyramid<T>& pyr, I const int octv, I const int intv, I const int y, I const int x, O KeyPoint& keypoint);

    template <typename T>
    void get_interp_offset(I const Pyramid<T>& pyr, I const int octv, I int intv, I int y, I int x, O double offset[3]);

    template <typename T>
    void get_interp_value(I const Pyramid<T>& pyr, I const int octv, I int intv, I int y, I int x, I double offset[3], O T& val);

    template <typename T>
    bool like_edge_toomuch(I const Pyramid<T>& pyr, I const int octv, I int intv, I const int y, I const int x, I const int curv_thr);

    template <typename T>
    void derive3d(I const Pyramid<T>& pyr, I const int octv, I int intv, I const int y, I const int x, O double derivative[3]);

    template <typename T>
    void hessian3d(I const Pyramid<T>& pyr, I const int octv, I int intv, I const int y, I const int x, O double hessian[9]);

    bool inverse3D(I const double H[9], O double H_inv[9]);

    template <typename T>
    void assign_orient(I const Pyramid<T>& gauss_pyr, I vector<KeyPoint>& extrema, O vector<KeyPoint>& feats);


    struct Hist
    {
        int bins;
        double min_mag, max_mag;
        double mag[256];
    };

    template <typename T>
    void create_ori_hist(I Image<T>& img, I const int y, I const int x, I const int radius, I const double sigma, I O Hist& hist);

    void gauss_smooth_hist(I O Hist& hist);

    void add_feats_by_ori(I const KeyPoint& keypoint, I const Hist& hist, I O vector<KeyPoint>& feats);

    template <typename T>
    bool calc_mag_ori(I Image<T>& img, I const int y, I const int x, O double &mag, O double &ori);

    void copy_key_point(I const KeyPoint& src, O KeyPoint& dst);

    template <typename T>
    void generate_descriptor(I O vector<KeyPoint>& feats, I const Pyramid<T>& gauss_pyr, I const int bins, I const int width);

    template <typename T>
    void create_descr_hist(I Image<T>& img, I O KeyPoint& feat, I const int bins, I const int width);

    void interp_hist_entry(I O KeyPoint& feat, I const double ybin, I const double xbin, I const double zbin, I const double mag, I const int bins, I const int width);

    void normalize_descr(I O KeyPoint& feat);
}


