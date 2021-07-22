/*** 
 * @Author: devis dong
 * @Date: 2021-07-21 13:05:14
 * @LastEditTime: 2021-07-23 01:44:17
 * @LastEditors: devis dong
 * @Description: 
 * @FilePath: \C++\src\dssift\dssift.h
 */

#include "dsimage.cpp"

namespace ds
{
    #define INIT_SIGMA 0.5                                      // initial value of sigma, wchic is intrinsic for the image
    #define SIFT_SIGMA 1.6                                      // sigam value for gaussian blur
    #define SIFT_INTVS 3                                        // number of images per octave(group)
    #define SIFT_CURV_THR 10                                    // main curvature threshold
    #define SIFT_MAX_INTERP_STEPS 5                             // max times for interpolation
    #define SIFT_CONTR_THR 0.07                                 // contrast threshold
    #define SIFT_IMG_UPSAMPLE 1                                 // whther to upsample the original image
    #define SIFT_ORI_HIST_BINS 36                               // orientation hitogram bins number
    #define SIFT_ORI_SIGMA_TIMES 1.5                            //
    #define SIFT_ORI_WINDOW_RADIUS 3.0 * SIFT_ORI_SIGMA_TIMES 
    #define SIFT_ORI_SMOOTH_TIMES 2                             // times for gaussain smoothing
    #define SIFT_ORI_PEAK_RATIO 0.8                             // ratio to the peak of the orientation histogram so that those bins of which magnitude is over this line are to be remained.
    #define SIFT_FEAT_LEN 128                                   // the length of the descriptor
    #define SIFT_DESCR_HIST_BINS 8                              // bins number of each block in the 4x4 block window
    #define SIFT_IMG_BORDER 5                                   // only the pixels inside the border are valid
    #define SIFT_DESCR_WINDOW_WIDTH 4                           // block number in each dimension
    #define SIFT_DESCR_SCALE_ADJUST 3                           // used to determine the width of each block
    #define SIFT_DESCR_MAG_THR 0.2                                   // descriptors magnitude is up to this threshold
    #define SIFT_INT_DESCR_FCTR 512.0                                // used to integeralize the descriptor

    // struct define for the gaussian and dog pyramid
    struct Pyramid
    {
        Image* imgs;
        int octvs, intvs;
    };

    struct KeyPoint
    {  
        int    octv, intv, y, x;                // location of keypoint
        double offset_intv, offset_y, offset_x; // offset to extremum
        double sigma;                           // global sigma
        double dy, dx;                          // coordinate of keypoint in original image
        double octv_sigma;                      // sigma inside the octave, for the same intv image of different octv, their octv_sigma is equal.
        double ori;                             // orientation of keypoint
        int    descr_length;                    // length of descriptor
        double descriptor[SIFT_FEAT_LEN];       // descriptor for the feature
        double val;                             // value of pixel
    };

    struct Hist
    {
        int bins;
        double min_mag, max_mag;
        double mag[256];
    };

    void get_sift_features(I Image& img_ori, O vector<KeyPoint>& feats, I const int intvs=SIFT_INTVS, I const double sigma=SIFT_SIGMA, I const double contr_thr=SIFT_CONTR_THR, I const double curv_thr=SIFT_CURV_THR, I const int upsample=SIFT_IMG_UPSAMPLE, I const int ori_hist_bins=SIFT_ORI_HIST_BINS, I const int descr_win_width=SIFT_DESCR_WINDOW_WIDTH, I const int descr_hist_bins=SIFT_DESCR_HIST_BINS);

    int create_init_smooth_gray(I Image &src, O Image &dst, double sigma, I const int upsample);

    // vector<vector<Image>> create_gauss_pyramid(I Image& img, I const int octvs, I const int intvls, I const double sigma);

    void create_gauss_pyramid(I Image& img, I O Pyramid& pyr, I const double sigma=SIFT_SIGMA);

    void create_diff_pyramid(I const Pyramid& gauss_pyr, I O Pyramid& diff_pyr);

    bool is_extremum(I const Pyramid& pyr, I const int octv, I const int intv, I const int y, I const int x);

    void detect_local_extrema(I const Pyramid& pyr, I const double contr_thr, I const int curv_thr, O vector<KeyPoint>& keypoints);

    int interplate_extremum(I const Pyramid& pyr, I const int octv, I const int intv, I const int y, I const int x, I const double contr_thr, O KeyPoint& keypoint);

    void get_interp_offset(I const Pyramid& pyr, I const int octv, I int intv, I int y, I int x, O double offset[3]);

    void get_interp_value(I const Pyramid& pyr, I const int octv, I int intv, I int y, I int x, I double offset[3], O double &val);

    bool like_edge_toomuch(I const Pyramid& pyr, I const int octv, I int intv, I const int y, I const int x, I const int curv_thr);

    void calculate_scale(I O vector<KeyPoint>& keypoints, I const double sigma, I const int intvs);

    void downsize_feats(I O vector<KeyPoint>& feats);

    void derive3d(I const Pyramid& pyr, I const int octv, I int intv, I const int y, I const int x, O double derivative[3]);

    void hessian3d(I const Pyramid& pyr, I const int octv, I int intv, I const int y, I const int x, O double hessian[9]);

    bool inverse3D(I const double H[9], O double H_inv[9]);

    void assign_orient(I const Pyramid& gauss_pyr, I vector<KeyPoint>& extrema, I const int bins, O vector<KeyPoint>& feats);

    void create_ori_hist(I Image& img, I const int y, I const int x, I const int radius, I const double sigma, I O Hist& hist);

    void gauss_smooth_hist(I O Hist& hist);

    void add_feats_by_ori(I const KeyPoint& keypoint, I const Hist& hist, I O vector<KeyPoint>& feats);

    bool calc_mag_ori(I Image& img, I const int y, I const int x, O double &mag, O double &ori);

    void copy_key_point(I const KeyPoint& src, O KeyPoint& dst);

    void generate_descriptor(I O vector<KeyPoint>& feats, I const Pyramid& gauss_pyr, I const int bins, I const int width);

    void create_descr_hist(I Image& img, I O KeyPoint& feat, I const int bins, I const int width);

    void interp_hist_entry(I O KeyPoint& feat, I const double ybin, I const double xbin, I const double zbin, I const double mag, I const int bins, I const int width);

    void normalize_descr(I O KeyPoint& feat);

    void draw_key_points(Image &img, vector<KeyPoint>& keypoints);

    void draw_sift_features(I O Image& img, I vector<KeyPoint>& features);

    void draw_sift_feature(I O cv::Mat& src, I KeyPoint& feat, I cv::Scalar color);

}


