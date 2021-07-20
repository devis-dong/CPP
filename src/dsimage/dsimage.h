/*** 
 * @Author: devis dong
 * @Date: 2021-07-19 21:01:48
 * @LastEditTime: 2021-07-20 19:29:32
 * @LastEditors: devis dong
 * @Description: 
 * @FilePath: \C++\src\dsimage\dsimage.h
 */


#ifndef DSIMAGE_H
#define DSIMAGE_H

#include <string>
#include "dsdefine.h"
using namespace std;

namespace ds
{

    class PixelPos
    {
        public:
            PixelPos(I const int y=0, I const int x=0, I const int z=0);

            int _y, _x, _z;
    };

    template <typename T>
    class Image
    {
        public:
            void init();
            void deinit();
            Image();
            Image(I const int h, I const int w, I const int c);
            Image(I const int h, I const int w, I const int c, I const T val);
            Image(I const string& filepath, I const int flag=1);
            Image(I const Image<T>& obj);
            ~Image();
            Image<T>& operator=(I const Image<T>& obj);
            T& at(I const unsigned int h, I const unsigned int w, I const unsigned int c);
            // Image<T> subimage(I const PixelPos& start, I const PixelPos& end);
            // Image<T> subimage(I const PixelPos& start, I const PixelPos& len);
            Image<T> subimage(I int const start[3], I const int len[3]);
            void resize(I const int h, I const int w, I const int c);
            void reset(I const int h, I const int w, I const int c);
            void reset(I const int h, I const int w, I const int c, I const T val);
            T get_sum();
            Image<T>& operator+=(I const Image<T>& img0);
            Image<T>& operator+=(I const T a);
            Image<T>& operator-=(I const Image<T>& img0);
            Image<T>& operator-=(I const T a);
            Image<T>& operator*=(I const Image<T>& img0);
            Image<T>& operator*=(I const T a);
            Image<T>& operator/=(I const Image<T>& img0);
            Image<T>& operator/=(I const T a);
            template <typename R>
            friend Image<R> operator+(I const Image<R>& img0, I const Image<R>& img1);
            template <typename R>
            friend Image<R> operator+(I const Image<R>& img0, I const R a);
            template <typename R>
            friend Image<R> operator+(I const R a, I const Image<R>& img0);
            template <typename R>
            friend Image<R> operator-(I const Image<R>& img0, I const Image<R>& img1);
            template <typename R>
            friend Image<R> operator-(I const Image<R>& img0, I const R a);
            template <typename R>
            friend Image<R> operator-(I const R a, I const Image<R>& img0);
            template <typename R>
            friend Image<R> operator*(I const Image<R>& img0, I const Image<R>& img1);
            template <typename R>
            friend Image<R> operator*(I const Image<R>& img0, I const R a);
            template <typename R>
            friend Image<R> operator*(I const R a, I const Image<R>& img0);
            template <typename R>
            friend Image<R> operator/(I const Image<R>& img0, I const Image<R>& img1);
            template <typename R>
            friend Image<R> operator/(I const Image<R>& img0, I const R a);
            template <typename R>
            friend Image<R> operator/(I const R a, I const Image<R>& img0);
            
            T* _data;
            int _h, _w, _c, _len;
    };

    template <typename T>
    Image<T> operator+(I const Image<T>& img0, I const Image<T>& img1);
    template <typename T>
    Image<T> operator+(I const Image<T>& img0, I const T a);
    template <typename T>
    Image<T> operator+(I const T a, I const Image<T>& img0);

    template <typename T>
    Image<T> operator-(I const Image<T>& img0, I const Image<T>& img1);
    template <typename T>
    Image<T> operator-(I const Image<T>& img0, I const T a);
    template <typename T>
    Image<T> operator-(I const T a, I const Image<T>& img0);

    template <typename T>
    Image<T> operator*(I const Image<T>& img0, I const Image<T>& img1);
    template <typename T>
    Image<T> operator*(I const Image<T>& img0, I const T a);
    template <typename T>
    Image<T> operator*(I const T a, I const Image<T>& img0);

    template <typename T>
    Image<T> operator/(I const Image<T>& img0, I const Image<T>& img1);
    template <typename T>
    Image<T> operator/(I const Image<T>& img0, I const T a);
    template <typename T>
    Image<T> operator/(I const T a, I const Image<T>& img0);

    template <typename T>
    void print_image(I Image<T>& img);
    template <typename T>
    void show_image(I Image<T>& img, I const string winname="");
    void wait_key(I const int delay=0);
    void close_win(I const string winname="");
    void close_all();

    template <typename U, typename V, typename T>
    T sumproduct(I Image<U>& img, I Image<V>& ker, I const int offset[3]);

    template <typename U, typename V, typename T>
    Image<T> convolve(I Image<U>& img, I Image<V>& ker, I const int step[3], I const int pad_size[3]={0});

    template <typename U, typename V, typename T>
    void convolve(I Image<U>& img, I Image<V>& ker, I const int step[3], I O Image<T>& con);

    template <typename T>
    Image<T> sample(I Image<T>& img, I const double rate[3]);

    template <typename T>
    Image<T> generate_gaussian_mat(I const int shape[3], I const double sigma=0.8, I const bool norm=false);

    template <typename T>
    Image<T> gaussian_blur(I Image<T>& img, I const int ker_shape[3], I const double sigma=0.8);

} // namespace ds







#endif
