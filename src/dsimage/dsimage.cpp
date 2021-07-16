/*** 
 * @Author: devis dong
 * @Date: 2021-07-14 11:20:57
 * @LastEditTime: 2021-07-16 20:07:25
 * @LastEditors: devis dong
 * @Description: 
 * @FilePath: \C++\src\dsimage\dsimage.cpp
 */

#include "dsimage.h"
#include "dslogger.h"

namespace ds
{
    #ifndef logger_init
    #define logger_init
        logger(Logger::target_all, Logger::level_all, "");
    #endif

    template <typename T>
    Image<T>::Image()
    : Mat<T>()
    {

    }
    template <typename T>
    Image<T>::Image(I const int height, I const int width, I const int channels)
    : Mat<T>({height, width, channels})
    {
    }

    template <typename T>
    template <typename R>
    Image<T>::Image(I const int height, I const int width, I const int channels, I const R* const pdata)
    : Mat<T>({height, width, channels}, pdata)
    {
    }

    template <typename T>
    template <typename R>
    Image<T>::Image(I const Image<R> &img)
    : Mat<T>(img._shape, img._pdata)
    {
    }

    template <typename T>
    int Image<T>::reset(I const int height, I const int width, I const int channels)
    {
        return Mat<T>::reset({height, width, channels});
    }

    template <typename T>
    Image<T>::~Image()
    {
    }

    template <typename T>
    int Image<T>::height() const
    {
        return this->_shape[0];
    }

    template <typename T>
    int Image<T>::width() const
    {
        return this->_shape[1];
    }

    template <typename T>
    int Image<T>::channels() const
    {
        return this->_shape[2];
    }

    template <typename T>
    T& Image<T>::at(I const int y, I const int x, I const int c)
    {
        return Mat<T>::at({y, x, c});
    }

    template <typename T>
    T& Image<T>::at(I const int idx)
    {
        return Mat<T>::at(idx);
    }

    template <typename T>
    T& Image<T>::operator()(I const int y, I const int x, I const int c)
    {
        return Mat<T>::at({y, x, c});
    }

    template <typename T>
    T* Image<T>::ptr(I const int y, I const int x, I const int c)
    {
        return Mat<T>::ptr({y, x, c});
    }

    template <typename T>
    T* Image<T>::ptr(I const int idx)
    {
        return Mat<T>::ptr(idx);
    }

    template <typename T>
    void Image<T>::randomize(I O Image<T> &img)
    {
        int height = img.height(), width = img.width(), channels = img.channels();
        for(int y = 0; y < height; ++y)
        {
            for(int x = 0; x < width; ++x)
            {
                for(int c = 0; c < channels; ++c)
                {
                    img._pdata[y*width*channels + x*channels + c] = (T)rand();
                }
            }
        }
    }

    template <typename T>
    vector<Image<T>> Image<T>::channel_images(I const bool keep_channels_num)
    {
        int height = this->height(), width = this->width(), channels = this->channels();
        vector<Image<T>> imgs(channels);
        for(int c = 0; c < channels; ++c)
        {
            imgs[c].reset(height, width, keep_channels_num?channels:1);
            for(int y = 0, idx = c, idx_c = keep_channels_num?c:0; y < height; ++y)
            {
                for(int x = 0; x < width; ++x, idx+=channels)
                {
                    imgs[c].at(y, x, idx_c) = Mat<T>::at(idx);
                }
            }
        }

        return imgs;
    }

    template <typename T>
    vector<int> Image<T>::histogram(I const int bins, I const float range_min, I const float range_max)
    {
        int height = this->height(), width = this->width(), channels = this->channels();
        float bin_width = (float)(range_max - range_min + 1) / (float)bins;
        vector<int> hist(bins*channels);
        for(int c = 0, offset = 0; c < channels; ++c, offset+=bins)
        {
            for(int y = 0, idx = c; y < height; ++y)
            {
                for(int x = 0; x < width; ++x, idx+=channels)
                {
                    float value = (float)min(max(range_min, (float)this->_pdata[idx]), range_max);
                    hist[offset + (int)(value / bin_width)] += 1;
                }
            }
        }
        return hist;
    }

    template class Image<char>;
    template class Image<int>;
    template class Image<long>;
    template class Image<long long>;
    template class Image<float>;
    template class Image<double>;
    template class Image<unsigned char>;
    template class Image<unsigned int>;
    template class Image<unsigned long>;
    template class Image<unsigned long long>;

}
