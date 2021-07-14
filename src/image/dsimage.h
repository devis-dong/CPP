/*** 
 * @Author: devis dong
 * @Date: 2021-07-13 12:53:01
 * @LastEditTime: 2021-07-14 18:36:21
 * @LastEditors: devis dong
 * @Description: 
 * @FilePath: \C++\src\Image\dsimage.h
 */

#ifndef DSIMAGE_H
#define DSIMAGE_H

#include "mat/dsmat.h"


template<typename T>
class ds_image: public Mat<T>
{
  public:
    ds_image(I const int width=0, I const int height=1, I const int channels=1);
    // template<typename R>
    // ds_image(I const int &width, I const int &height, I const int &channels, I const R data);
    template<typename R>
    ds_image(I const int width, I const int height, I const int channels, I const R* const pdata);
    template<typename R>
    ds_image(I const ds_image<R> &img);
    ~ds_image();
    int reset(I const int width, I const int height, I const int channels);
    int width() const;
    int height() const;
    int channels() const;
    T& at(I const int y, I const int x, I const int c=0);
    T& at(I const int idx);
    T* ptr(I const int y, I const int x, I const int c=0);
    T* ptr(I const int idx=0);
    T& operator()(I const int y, I const int x, I const int c=0);
    static void randomize(I O ds_image<T> &img);
    vector<ds_image<T>> channel_images(I const bool same_channel_num=true);
    vector<int> histogram(I const int bins, I const float range_min, I const float range_max);
};


#endif