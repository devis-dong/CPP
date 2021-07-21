/*** 
 * @Author: devis dong
 * @Date: 2021-07-19 21:01:59
 * @LastEditTime: 2021-07-21 13:08:08
 * @LastEditors: devis dong
 * @Description: 
 * @FilePath: \C++\src\dsimage\dsimage.cpp
 */


#include <math.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "dsimage.h"
#include "opencv.hpp"
using namespace std;

namespace ds
{

    PixelPos::PixelPos(I const int y, I const int x, I const int c)
    : _y(y), _x(x), _z(c)
    {
        
    }

    template <typename T>
    Image<T>::Image()
    : _h(0), _w(0), _c(0), _len(0), _data(nullptr)
    {
    }

    template <typename T>
    Image<T>::Image(I const int h, I const int w, I const int c)
    : _h(h), _w(w), _c(c), _len(h * w * c)
    {
        _data = new T[_len];
        assert (_data != nullptr);
        memset(_data, 0, _len*sizeof(T));
    }

    template <typename T>
    Image<T>::Image(I const int h, I const int w, I const int c, I const T val)
    : _h(h), _w(w), _c(c), _len(h * w * c)
    {
        _data = new T[_len];
        assert (_data != nullptr);
        for(int i = 0; i < _len; ++i) _data[i] = val;
    }

    template <typename T>
    Image<T>::Image(I const string& filepath, I const int flag)
    {
        cv::Mat cvimg = cv::imread(filepath, flag);
        assert (!cvimg.empty());
        init();
        _h = cvimg.rows; _w = cvimg.cols; _c = cvimg.channels();
        _len = _h*_w*_c;
        _data = new T[_len];
        assert (_data != nullptr);
        if(typeid(uchar) == typeid(T)) memcpy(_data, cvimg.data, _len);
        else for(int i = 0; i < _len; ++i) _data[i] = (T)cvimg.data[i];
    }

    template <typename T>
    void Image<T>::init()
    {
        _data = nullptr;
        _len = 0;
        _h = 0;
        _w = 0;
        _c = 0;

    }

    template <typename T>
    void Image<T>::deinit()
    {
        _h = 0;
        _w = 0;
        _c = 0;
        _len = 0;
        if(nullptr != _data)
        {
            delete[] _data;
            _data = nullptr;
        }
    }

    template <typename T>
    Image<T>::Image(I const Image<T>& obj)
    {
        init();
        _len = obj._len;
        _h = obj._h; _w = obj._w; _c = obj._c;
        _data = new T[_len];
        assert (_data != nullptr);
        memcpy(_data, obj._data, _len*sizeof(T));
    }

    template <typename T>
    Image<T>::~Image()
    {
        deinit();
    }

    template <typename T>
    Image<T>& Image<T>::operator=(I const Image<T>& obj)
    {
        if(this == &obj) return *this;
        deinit();
        _len = obj._len;
        _h = obj._h; _w = obj._w; _c = obj._c;
        _data = new T[_len];
        assert (_data != nullptr);
        memcpy(_data, obj._data, _len*sizeof(T));
        return *this;
    }

    template <typename T>
    T& Image<T>::at(I const unsigned int y, I const unsigned int x, I const unsigned int z)
    {
        return _data[y*_w*_c + x*_c + z];
    }

    // template <typename T>
    // Image<T> Image<T>::subimage(I const PixelPos& start, I const PixelPos& end)
    // {
    //     PixelPos minpos(min(start._y, end._y), min(start._x, end._x), min(start._z, end._z));
    //     PixelPos maxpos(max(start._y, end._y), max(start._x, end._x), max(start._z, end._z));
    //     Image<T> subimg(maxpos._y-minpos._y, maxpos._x-minpos._x, maxpos._z-minpos._z);
    //     for(int i = 0, j = minpos._y*_w*_c + minpos._x*_c + minpos._z, y = minpos._y; y <= maxpos._y; ++y, j += _w*_c)
    //     {
    //         for(int x = minpos._x; x <= maxpos._x; ++x, j += _c)
    //         {
    //             for(int z = minpos._z; z <= maxpos._z; ++z, ++i, ++j)
    //             {
    //                 subimg._data[i] = _data[j];
    //             }
    //         }
    //     }
    //     return subimg;
    // }

    // template <typename T>
    // Image<T> Image<T>::subimage(I const PixelPos& start, I const PixelPos& len)
    // {
    //     Image<T> subimg(len._y, len._x, len._z);
    //     for(int i = 0, j = start._y*_w*_c + start._x*_c + start._z, y = 0; y < len._y; ++y, j += _w*_c)
    //     {
    //         for(int x = 0; x < len._x; ++x, j += _c)
    //         {
    //             for(int z = 0; z < len._z; ++z, ++i, ++j)
    //             {
    //                 subimg._data[i] = _data[j];
    //             }
    //         }
    //     }
    //     return subimg;
    // }

    template <typename T>
    Image<T> Image<T>::subimage(I const int start[3], I const int len[3])
    {
        Image<T> subimg(len[0], len[1], len[2]);
        for(int y = 0, i = 0, j0 = start[0]*_w*_c+start[1]*_c+start[2]; y < len[0]; ++y, j0 += _w*_c)
        {
            for(int x = 0, j1 = j0; x < len[1]; ++x, j1 += _c)
            {
                for(int z = 0, j = j1; z < len[2]; ++z, ++i, ++j)
                {
                    subimg._data[i] = _data[j];
                }
            }
        }
        return subimg;
    }

    template <typename T>
    void Image<T>::resize(I const int h, I const int w, I const int c)
    {
        
    }

    template <typename T>
    void Image<T>::reset(I const int h, I const int w, I const int c)
    {
        deinit();
        _h = h; _w = w; _c = c; _len = h*w*c;
        _data = new T[_len];
        assert (nullptr != _data);
        memset(_data, 0, _len*sizeof(T));
    }

    template <typename T>
    void Image<T>::reset(I const int h, I const int w, I const int c, I const T val)
    {
        deinit();
        _h = h; _w = w; _c = c; _len = h*w*c;
        _data = new T[_len];
        assert (nullptr != _data);
        for(int i = 0; i < _len; ++i) _data[i] = val;
    }

    template <typename T>
    T Image<T>::get_sum()
    {
        T sum = 0;
        for(int i = 0; i < _len; ++i)
        {
            sum += _data[i];
        }
        return sum;
    }

    template <typename T>
    Image<T>& Image<T>::operator+=(I const Image<T>& img0)
    {
        assert (_h == img0._h && _w == img0._w && _c == img0._c);
        for(int i = 0; i < _len; ++i)
        {
            _data[i] += img0._data[i];
        }
        return *this;
    }

    template <typename T>
    Image<T>& Image<T>::operator+=(I const T a)
    {
        for(int i = 0; i < _len; ++i)
        {
            _data[i] += a;
        }
        return *this;
    }

    template <typename T>
    Image<T>& Image<T>::operator-=(I const Image<T>& img0)
    {
        assert (_h == img0._h && _w == img0._w && _c == img0._c);
        for(int i = 0; i < _len; ++i)
        {
            _data[i] -= img0._data[i];
        }
        return *this;
    }

    template <typename T>
    Image<T>& Image<T>::operator-=(I const T a)
    {
        for(int i = 0; i < _len; ++i)
        {
            _data[i] -= a;
        }
        return *this;
    }

    template <typename T>
    Image<T>& Image<T>::operator*=(I const Image<T>& img0)
    {
        assert (_h == img0._h && _w == img0._w && _c == img0._c);
        for(int i = 0; i < _len; ++i)
        {
            _data[i] *= img0._data[i];
        }
        return *this;
    }

    template <typename T>
    Image<T>& Image<T>::operator*=(I const T a)
    {
        for(int i = 0; i < _len; ++i)
        {
            _data[i] *= a;
        }
        return *this;
    }

    template <typename T>
    Image<T>& Image<T>::operator/=(I const Image<T>& img0)
    {
        assert (_h == img0._h && _w == img0._w && _c == img0._c);
        for(int i = 0; i < _len; ++i)
        {
            _data[i] /= img0._data[i];
        }
        return *this;
    }

    template <typename T>
    Image<T>& Image<T>::operator/=(I const T a)
    {
        for(int i = 0; i < _len; ++i)
        {
            _data[i] /= a;
        }
        return *this;
    }

    template <typename T>
    void show_image(I Image<T>& img, I string winname)
    {
        uchar* data = nullptr;
        if(typeid(T) != typeid(uchar))
        {
            data = new uchar[img._len];
            assert (nullptr != data);
            for(int i = 0; i < img._len; ++i)
            {
                data[i] = (uchar)img._data[i];
            }
            cv::Mat cvimg(img._h, img._w, CV_8UC(img._c), data);
            cv::imshow(winname, cvimg);
        }
        else
        {
            cv::Mat cvimg(img._h, img._w, CV_8UC(img._c), img._data);
            cv::imshow(winname, cvimg);
        }

        if(nullptr != data)
        {
            delete[] data;
        }
    }

    void wait_key(I const int delay)
    {
        cv::waitKey(delay);
    }

    void close_win(I const string& winname)
    {
        cv::destroyWindow(winname);
    }

    void close_all()
    {
        cv::destroyAllWindows();
    }

    template <typename T>
    void print_image(I Image<T>& img)
    {
        cout<<"["<<endl;
        for(int y = 0, i = 0; y < img._h; ++y)
        {
            cout<<" [ ";
            for(int x = 0; x < img._w; ++x)
            {
                cout<<"[ ";
                for(int z = 0; z < img._c; ++z)
                {
                    cout<<img._data[i++]<<" ";
                }
                cout<<"]";
            }
            cout<<" ]"<<endl;
        }
        cout<<"]"<<endl;
    }

    template <typename T>
    Image<T> operator+(I const Image<T>& img0, I const Image<T>& img1)
    {
        Image<T> img_prime(img0);
        for(int i = 0; i < img_prime._len; ++i)
        {
            img_prime._data[i] += img1._data[i];
        }
        return img_prime;
    }

    template <typename T>
    Image<T> operator+(I const Image<T>& img0, I const T a)
    {
        Image<T> img_prime(img0);
        for(int i = 0; i < img_prime._len; ++i)
        {
            img_prime._data[i] += a;
        }
        return img_prime;
    }

    template <typename T>
    Image<T> operator+(I const T a, I const Image<T>& img0)
    {
        Image<T> img_prime(img0);
        for(int i = 0; i < img_prime._len; ++i)
        {
            img_prime._data[i] += a;
        }
        return img_prime;
    }

    template <typename T>
    Image<T> operator-(I const Image<T>& img0, I const Image<T>& img1)
    {
        Image<T> img_prime(img0);
        for(int i = 0; i < img_prime._len; ++i)
        {
            img_prime._data[i] -= img1._data[i];
        }
        return img_prime;
    }

    template <typename T>
    Image<T> operator-(I const Image<T>& img0, I const T a)
    {
        Image<T> img_prime(img0);
        for(int i = 0; i < img_prime._len; ++i)
        {
            img_prime._data[i] -= a;
        }
        return img_prime;
    }

    template <typename T>
    Image<T> operator-(I const T a, I const Image<T>& img0)
    {
        Image<T> img_prime(img0);
        for(int i = 0; i < img_prime._len; ++i)
        {
            img_prime._data[i] = a - img_prime._data[i];
        }
        return img_prime;
    }

    template <typename T>
    Image<T> operator*(I const Image<T>& img0, I const Image<T>& img1)
    {
        Image<T> img_prime(img0);
        for(int i = 0; i < img_prime._len; ++i)
        {
            img_prime._data[i] *= img1._data[i];
        }
        return img_prime;
    }

    template <typename T>
    Image<T> operator*(I const Image<T>& img0, I const T a)
    {
        Image<T> img_prime(img0);
        for(int i = 0; i < img_prime._len; ++i)
        {
            img_prime._data[i] *= a;
        }
        return img_prime;
    }

    template <typename T>
    Image<T> operator*(I const T a, I const Image<T>& img0)
    {
        Image<T> img_prime(img0);
        for(int i = 0; i < img_prime._len; ++i)
        {
            img_prime._data[i] *= a;
        }
        return img_prime;
    }

    template <typename T>
    Image<T> operator/(I const Image<T>& img0, I const Image<T>& img1)
    {
        Image<T> img_prime(img0);
        for(int i = 0; i < img_prime._len; ++i)
        {
            img_prime._data[i] /= img1._data[i];
        }
        return img_prime;
    }

    template <typename T>
    Image<T> operator/(I const Image<T>& img0, I const T a)
    {
        Image<T> img_prime(img0);
        for(int i = 0; i < img_prime._len; ++i)
        {
            img_prime._data[i] /= a;
        }
        return img_prime;
    }

    template <typename T>
    Image<T> operator/(I const T a, I const Image<T>& img0)
    {
        Image<T> img_prime(img0);
        for(int i = 0; i < img_prime._len; ++i)
        {
            img_prime._data[i] = a / img_prime._data[i];
        }
        return img_prime;
    }

    template <typename U, typename V, typename T>
    T sumproduct(I Image<U>& img, I Image<V>& ker, I const int offset[3])
    {
        T sum = 0;
        int offset_img[3] = {offset[0] > 0 ? offset[0] : 0, offset[1] > 0 ? offset[1] : 0, offset[2] > 0 ? offset[2] : 0};
        int offset_ker[3] = {offset[0] < 0 ? -offset[0] : 0, offset[1] < 0 ? -offset[1] : 0, offset[2] < 0 ? -offset[2] : 0};
        int iy = 0, ix = 0, iz = 0, ky = 0, kx = 0, kz = 0, i = 0, k = 0, i1 = 0, k1 = 0;
        int i0 = offset_img[0]*img._w*img._c + offset_img[1]*img._c + offset_img[2];
        int k0 = offset_ker[0]*ker._w*ker._c + offset_ker[1]*ker._c + offset_ker[2];
        for(iy = offset_img[0], ky = offset_ker[0]; iy < img._h && ky < ker._h; ++iy, ++ky, i0 += img._w*img._c, k0 += ker._w*ker._c)
        {
            for(ix = offset_img[1], kx = offset_ker[1], i1 = i0, k1 = k0; ix < img._w && kx < ker._w; ++ix, ++kx, i1 += img._c, k1 += ker._c)
            {
                for(iz = offset_img[2], kz = offset_ker[2], i = i1, k = k1; iz < img._c && kz < ker._c; ++iz, ++kz, ++i, ++k)
                {
                    sum += img._data[i] * ker._data[k];
                }
            }
        }
        return sum;
    }

    template<typename U, typename V, typename T>
    Image<T> convolve(I Image<U>& img, I Image<V>& ker, I const int step[3], I const int pad_size[3])
    {
        int con_shape[3] = {(img._h+2*pad_size[0]-ker._h)/step[0]+1, (img._w+2*pad_size[1]-ker._w)/step[1]+1, (img._c+2*pad_size[2]-ker._c)/step[2]+1};
        int start[3] = {-pad_size[0], -pad_size[1], -pad_size[2]};
        int end[3] = {start[0] + con_shape[0], start[1] + con_shape[1], start[2] + con_shape[2]};
        Image<T> con(con_shape[0], con_shape[1], con_shape[2]);
        int offset[3] = {0}, i = 0;
        for(offset[0] = start[0]; offset[0] < end[0]; offset[0] += step[0])
        {
            for(offset[1] = start[1]; offset[1] < end[1]; offset[1] += step[1])
            {
                for(offset[2] = start[2]; offset[2] < end[2]; offset[2] += step[2])
                {
                    con._data[i++] = sumproduct<U, V, T>(img, ker, offset);
                }
            }
        }
        return con;
    }

    template <typename U, typename V, typename T>
    void convolve(I Image<U>& img, I Image<V>& ker, I const int step[3], I O Image<T>& con)
    {
        int max_offset[3] = {img._h - ker._h, img._w - ker._w, img._c - ker._c};
        int offset[3] = {0, 0, 0}, i = 0;
        con.reset((img._h-ker._h)/step[0]+1, (img._w-ker._w)/step[1]+1, (img._c-ker._c)/step[2]+1);
        for(offset[0] = 0; offset[0] <= max_offset[0]; offset[0] += step[0])
        {
            for(offset[1] = 0; offset[1] <= max_offset[1]; offset[1] += step[1])
            {
                for(offset[2] = 0; offset[2] <= max_offset[2]; offset[2] += step[2])
                {
                    con._data[i++] = sumproduct<U, V, T>(img, ker, offset);
                }
            }
        }
    }

    template <typename T>
    Image<T> sample_image(I Image<T>& img, I const double rate[3])
    {
        Image<T> sampleimg(img._h*rate[0], img._w*rate[1], img._c*rate[2]);
        double r[3] = {double(sampleimg._h)/double(img._h), double(sampleimg._w)/double(img._w), double(sampleimg._c)/double(img._c)};
        for(int y = 0, i = 0, j0 = 0; y < sampleimg._h; ++y, j0 = int(y/r[0])*img._w*img._c)
        {
            for(int x = 0, j1 = j0; x < sampleimg._w; ++x, j1 = j0+int(x/r[1])*img._c)
            {
                for(int z = 0, j = j1; z < sampleimg._c; ++z, ++i, j = j1 + int(z/r[2]))
                {
                    sampleimg._data[i] = img._data[j];
                }
            }
        }
        return sampleimg;
    }

    template <typename T>
    Image<T> generate_gaussian_mat(I const int shape[3], I const double sigma, I const bool norm)
    {
        Image<T> g_mat(shape[0], shape[1], shape[2]);
        T A = 0.5/(PI*sigma*sigma);
        double o[3] = {(g_mat._h-1)/2.0, (g_mat._w-1)/2.0, (g_mat._c-1)/2.0};
        int y = 0, x = 0, z = 0, i = 0;
        for(y = 0; y < g_mat._h; ++y)
        {
            for(x = 0; x < g_mat._w; ++x)
            {
                T val = A * exp(-0.5*((y-o[0])*(y-o[0]) + (x-o[1])*(x-o[1]))/(sigma*sigma));
                for(z = 0; z < g_mat._c; ++z)
                {
                    g_mat._data[i++] = val;
                }
            }
        }
        if(norm) g_mat /= g_mat.get_sum();
        return g_mat;
    }

    template <typename T>
    Image<T> gaussian_blur(I Image<T>& img, I const int ker_shape[3], I const double sigma)
    {
        Image<double> ker = generate_gaussian_mat<double>(ker_shape, sigma, true);
        int step[3] = {1, 1, 1};
        int pad_size[3] = {int(0.5*((img._h-1)*step[0]+ker_shape[0]-img._h)), int(0.5*((img._w-1)*step[1]+ker_shape[1]-img._w)), int(0.5*((img._c-1)*step[2]+ker_shape[2]-img._c))};
        return convolve<T, double, T>(img, ker, step, pad_size);
    }


}

