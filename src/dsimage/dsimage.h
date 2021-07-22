/*** 
 * @Author: devis dong
 * @Date: 2021-07-19 21:01:48
 * @LastEditTime: 2021-07-22 23:22:43
 * @LastEditors: devis dong
 * @Description: 
 * @FilePath: \C++\src\dsimage\dsimage.h
 */


#ifndef DSIMAGE_H
#define DSIMAGE_H

#include <vector>
#include <string>
#include "dsdefine.h"
#include "opencv.hpp"
using namespace std;

namespace ds
{
    #define DTYPE_8U   0
    #define DTYPE_8S   1
    #define DTYPE_16U  2
    #define DTYPE_16S  3
    #define DTYPE_32S  4
    #define DTYPE_32F  5
    #define DTYPE_64F  6

    class PixelPos
    {
        public:
            PixelPos(I const int y=0, I const int x=0, I const int z=0);

            int _y, _x, _z;
    };

    class Image
    {
        public:
            void init(I const int h=0, I const int w=0, I const int c=0, I double* data=nullptr);
            void deinit();
            Image();
            Image(I const int h, I const int w, I const int c);
            Image(I const int h, I const int w, I const int c, I const double val);
            Image(I const string& filepath, I const int flag=1);
            Image(I const Image& obj);
            ~Image();
            Image& operator=(I const Image& obj);
            double& at(I const unsigned int h, I const unsigned int w, I const unsigned int c=0);
            // Image subimage(I const PixelPos& start, I const PixelPos& end);
            // Image subimage(I const PixelPos& start, I const PixelPos& len);
            Image subimage(I int const start[3], I const int len[3]);
            void resize(I const int h, I const int w, I const int c);
            void reset(I const int h, I const int w, I const int c);
            void reset(I const int h, I const int w, I const int c, I const double val);
            double get_sum();
            Image& operator+=(I const Image& img0);
            Image& operator+=(I const double a);
            Image& operator-=(I const Image& img0);
            Image& operator-=(I const double a);
            Image& operator*=(I const Image& img0);
            Image& operator*=(I const double a);
            Image& operator/=(I const Image& img0);
            Image& operator/=(I const double a);
            template <typename R>
            friend Image operator+(I const Image& img0, I const Image& img1);
            template <typename R>
            friend Image operator+(I const Image& img0, I const R a);
            template <typename R>
            friend Image operator+(I const R a, I const Image& img0);
            template <typename R>
            friend Image operator-(I const Image& img0, I const Image& img1);
            template <typename R>
            friend Image operator-(I const Image& img0, I const R a);
            template <typename R>
            friend Image operator-(I const R a, I const Image& img0);
            template <typename R>
            friend Image operator*(I const Image& img0, I const Image& img1);
            template <typename R>
            friend Image operator*(I const Image& img0, I const R a);
            template <typename R>
            friend Image operator*(I const R a, I const Image& img0);
            template <typename R>
            friend Image operator/(I const Image& img0, I const Image& img1);
            template <typename R>
            friend Image operator/(I const Image& img0, I const R a);
            template <typename R>
            friend Image operator/(I const R a, I const Image& img0);
            
            double* _data;
            int _h, _w, _c, _len;
    };

    Image operator+(I const Image& img0, I const Image& img1);
    Image operator+(I const Image& img0, I const double a);
    Image operator+(I const double a, I const Image& img0);

    Image operator-(I const Image& img0, I const Image& img1);
    Image operator-(I const Image& img0, I const double a);
    Image operator-(I const double a, I const Image& img0);

    Image operator*(I const Image& img0, I const Image& img1);
    Image operator*(I const Image& img0, I const double a);
    Image operator*(I const double a, I const Image& img0);

    Image operator/(I const Image& img0, I const Image& img1);
    Image operator/(I const Image& img0, I const double a);
    Image operator/(I const double a, I const Image& img0);

    void print_image(I Image& img);
    void show_image(I Image& img, I const string winname="");
    void wait_key(I const int delay=0);
    void close_win(I const string winname="");
    void close_all();

    void convert_dtype(I Image& src, O Image& dst);
    
    Image bgr2gray(I Image& bgr_img);

    int bgr2gray(I Image& bgr_img, O Image& gray_img);

    double sumproduct(I Image& img, I Image& ker, I const int offset[3]);

    Image convolve(I Image& img, I Image& ker, I const int step[3], I const int pad_size[3]={0});

    void convolve(I Image& img, I Image& ker, I const int step[3], I O Image& con);

    double linear_interp_val(I Image& img, I const double y, I const double x, I const double z);

    Image sample_image(I Image& img, I const double rate[3]);

    Image generate_gaussian_mat(I const int shape[3], I const double sigma=0.8, I const bool norm=false);

    Image gaussian_blur(I Image& img, I const int ker_shape[3], I const double sigma=0.8);

    void img2cvmat(I Image& img, O cv::Mat& mat);

    void cvmat2img(I cv::Mat& mat, O Image& img);

} // namespace ds







#endif
