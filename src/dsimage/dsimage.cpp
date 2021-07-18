/*** 
 * @Author: devis dong
 * @Date: 2021-07-14 11:20:57
 * @LastEditTime: 2021-07-17 22:16:57
 * @LastEditors: devis dong
 * @Description: 
 * @FilePath: \C++\src\dsimage\dsimage.cpp
 */

#include <typeinfo>
#include "dsimage.h"
#include "opencv.hpp"
#include "dsmat.cpp"

namespace ds
{
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
    Image<T>::Image(I const string& filepath, I const int flag)
    : Mat<T>(filepath, flag)
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
    void Image<T>::show(I const string winname)
    {
        uchar* pdata = nullptr;
        if(typeid(T) != typeid(uchar))
        {
            int n = Mat<T>::get_elements_num();
            pdata = new uchar[n];
            assert (nullptr != pdata);
            for(int i = 0; i < n; ++i)
            {
                pdata[i] = (uchar)this->at(i);
            }
            cv::Mat cvimg(this->height(), this->width(), CV_8UC(this->channels()), pdata);
            cv::imshow(winname, cvimg);
        }
        else
        {
            cv::Mat cvimg(this->height(), this->width(), CV_8UC(this->channels()), this->data());
            cv::imshow(winname, cvimg);
        }

        if(nullptr != pdata)
        {
            delete[] pdata;
        }
    }

    template <typename T>
    void Image<T>::waitkey(I const int delay)
    {
        cv::waitKey(delay);
    }

    template <typename T>
    void Image<T>::close(I const string winname)
    {
        cv::destroyWindow(winname);
    }

    template <typename T>
    void Image<T>::close()
    {
        cv::destroyAllWindows();
    }

    template <typename T>
    int Image<T>::height() const
    {
        return Mat<T>::shape()[0];
    }

    template <typename T>
    int Image<T>::width() const
    {
        return Mat<T>::shape()[1];
    }

    template <typename T>
    int Image<T>::channels() const
    {
        return Mat<T>::shape()[2];
    }

    template <typename T>
    T* Image<T>::data()
    {
        return this->ptr(0);
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
