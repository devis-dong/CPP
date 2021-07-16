/*** 
 * @Author: devis dong
 * @Date: 2021-07-13 12:53:01
 * @LastEditTime: 2021-07-16 19:34:13
 * @LastEditors: devis dong
 * @Description: 
 * @FilePath: \C++\src\image\dsimage.h
 */

#ifndef DSIMAGE_H
#define DSIMAGE_H

#include "dsmat.h"

namespace ds
{
    template<typename T>
    class Image: public Mat<T>
    {
        public:
            Image();
            Image(I const int height, I const int width, I const int channels=1);
            template<typename R>
            Image(I const int height, I const int width, I const int channels, I const R* const pdata);
            template<typename R>
            Image(I const Image<R> &img);
            ~Image();
            int reset(I const int height, I const int width, I const int channels);
            int width() const;
            int height() const;
            int channels() const;
            T& at(I const int y, I const int x, I const int c=0);
            T& at(I const int idx);
            T* ptr(I const int y, I const int x, I const int c=0);
            T* ptr(I const int idx=0);
            T& operator()(I const int y, I const int x, I const int c=0);
            static void randomize(I O Image<T> &img);
            vector<Image<T>> channel_images(I const bool keep_channels_num=true);
            vector<int> histogram(I const int bins, I const float range_min, I const float range_max);
    };

}



#endif