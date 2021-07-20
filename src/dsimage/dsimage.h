/*** 
 * @Author: devis dong
 * @Date: 2021-07-19 21:01:48
 * @LastEditTime: 2021-07-20 10:49:32
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
            T* _data;
            int _h, _w, _c, _len;
    };
    
    template <typename T>
    void show_image(I Image<T>& img, I const string winname="");

    void wait_key(I const int delay=0);

    void close_win(I const string winname="");

    void close_all();

    template <typename U, typename V, typename T>
    T sumproduct(I Image<U>& img, I Image<V>& ker, I const int offset[3]);

    template <typename U, typename V, typename T>
    Image<T> convolve(I Image<U>& img, I Image<V>& ker, I const int step[3]);

    template <typename U, typename V, typename T>
    void convolve(I Image<U>& img, I Image<V>& ker, I const int step[3], I O Image<T>& con);

    template <typename T>
    Image<T> sample(I Image<T>& img, I const double rate[3]);


} // namespace ds







#endif
