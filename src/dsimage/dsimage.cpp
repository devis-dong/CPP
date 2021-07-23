/*** 
 * @Author: devis dong
 * @Date: 2021-07-19 21:01:59
 * @LastEditTime: 2021-07-23 11:27:31
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

     
    Image::Image()
    : _h(0), _w(0), _c(0), _len(0), _data(nullptr)
    {
    }

    Image::Image(I const int h, I const int w, I const int c)
    : _h(h), _w(w), _c(c), _len(h * w * c)
    {
        _data = new double[_len];
        assert (_data != nullptr);
        memset(_data, 0, _len*sizeof(double));
    }

     
    Image::Image(I const int h, I const int w, I const int c, I const double val)
    : _h(h), _w(w), _c(c), _len(h * w * c)
    {
        _data = new double[_len];
        assert (_data != nullptr);
        for(int i = 0; i < _len; ++i) _data[i] = val;
    }

     
    Image::Image(I const string& filepath, I const int flag)
    {
        cv::Mat cvimg = cv::imread(filepath, flag);
        // cv::Mat cvimg;
        // img.convertTo(cvimg, CV_64FC(img.channels()));
        assert (!cvimg.empty());
        init();
        _h = cvimg.rows; _w = cvimg.cols; _c = cvimg.channels();
        _len = _h*_w*_c;
        _data = new double[_len];
        assert (_data != nullptr);
        for(int i = 0; i < _len; ++i) _data[i] = (double)(cvimg.data[i]/255.0);
    }

     
    void Image::init(I const int h, I const int w, I const int c, I double* data)
    {
        _h = h;
        _w = w;
        _c = c;
        _len = _h*_w*_c;
        _data = data;

    }

     
    void Image::deinit()
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

     
    Image::Image(I const Image& obj)
    {
        init();
        _len = obj._len;
        _h = obj._h; _w = obj._w; _c = obj._c;
        _data = new double[_len];
        assert (_data != nullptr);
        memcpy(_data, obj._data, _len*sizeof(double));
    }

     
    Image::~Image()
    {
        deinit();
    }

     
    Image& Image::operator=(I const Image& obj)
    {
        // if(this == &obj) return *this;
        deinit();
        _len = obj._len;
        _h = obj._h; _w = obj._w; _c = obj._c;
        _data = new double[_len];
        assert (_data != nullptr);
        memcpy(_data, obj._data, _len*sizeof(double));
        return *this;
    }

     
    double& Image::at(I const unsigned int y, I const unsigned int x, I const unsigned int z)
    {
        return _data[y*_w*_c + x*_c + z];
    }

    //  
    // Image Image::subimage(I const PixelPos& start, I const PixelPos& end)
    // {
    //     PixelPos minpos(min(start._y, end._y), min(start._x, end._x), min(start._z, end._z));
    //     PixelPos maxpos(max(start._y, end._y), max(start._x, end._x), max(start._z, end._z));
    //     Image subimg(maxpos._y-minpos._y, maxpos._x-minpos._x, maxpos._z-minpos._z);
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

    //  
    // Image Image::subimage(I const PixelPos& start, I const PixelPos& len)
    // {
    //     Image subimg(len._y, len._x, len._z);
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

     
    Image Image::subimage(I const int start[3], I const int len[3])
    {
        Image subimg(len[0], len[1], len[2]);
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

     
    void Image::resize(I const int h, I const int w, I const int c)
    {
        Image sampleimg(h, w, 0==c?_c:c);
        double r[3] = {double(sampleimg._h)/double(_h), double(sampleimg._w)/double(_w), double(sampleimg._c)/double(_c)};
        double y_prime, x_prime, z_prime;
        int y, x, z, i;
        for(y = 0, i = 0; y < sampleimg._h; ++y)
        {
            y_prime = double(y) / r[0];
            for(x = 0; x < sampleimg._w; ++x)
            {
                x_prime = double(x) / r[1];
                for(z = 0; z < sampleimg._c; ++z)
                {
                    z_prime = double(z) / r[2];
                    sampleimg._data[i++] = linear_interp_val(*this, y_prime, x_prime, z_prime);
                }
            }
        }
        *this = sampleimg;
    }

     
    void Image::reset(I const int h, I const int w, I const int c)
    {
        deinit();
        _h = h; _w = w; _c = c; _len = h*w*c;
        _data = new double[_len];
        assert (nullptr != _data);
        memset(_data, 0, _len*sizeof(double));
    }

     
    void Image::reset(I const int h, I const int w, I const int c, I const double val)
    {
        deinit();
        _h = h; _w = w; _c = c; _len = h*w*c;
        _data = new double[_len];
        assert (nullptr != _data);
        for(int i = 0; i < _len; ++i) _data[i] = val;
    }

     
    double Image::get_sum()
    {
        double sum = 0;
        for(int i = 0; i < _len; ++i)
        {
            sum += _data[i];
        }
        return sum;
    }

     
    Image& Image::operator+=(I const Image& img0)
    {
        assert (_h == img0._h && _w == img0._w && _c == img0._c);
        for(int i = 0; i < _len; ++i)
        {
            _data[i] += img0._data[i];
        }
        return *this;
    }

     
    Image& Image::operator+=(I const double a)
    {
        for(int i = 0; i < _len; ++i)
        {
            _data[i] += a;
        }
        return *this;
    }

     
    Image& Image::operator-=(I const Image& img0)
    {
        assert (_h == img0._h && _w == img0._w && _c == img0._c);
        for(int i = 0; i < _len; ++i)
        {
            _data[i] -= img0._data[i];
        }
        return *this;
    }

     
    Image& Image::operator-=(I const double a)
    {
        for(int i = 0; i < _len; ++i)
        {
            _data[i] -= a;
        }
        return *this;
    }

     
    Image& Image::operator*=(I const Image& img0)
    {
        assert (_h == img0._h && _w == img0._w && _c == img0._c);
        for(int i = 0; i < _len; ++i)
        {
            _data[i] *= img0._data[i];
        }
        return *this;
    }

     
    Image& Image::operator*=(I const double a)
    {
        for(int i = 0; i < _len; ++i)
        {
            _data[i] *= a;
        }
        return *this;
    }

     
    Image& Image::operator/=(I const Image& img0)
    {
        assert (_h == img0._h && _w == img0._w && _c == img0._c);
        for(int i = 0; i < _len; ++i)
        {
            _data[i] /= img0._data[i];
        }
        return *this;
    }

     
    Image& Image::operator/=(I const double a)
    {
        for(int i = 0; i < _len; ++i)
        {
            _data[i] /= a;
        }
        return *this;
    }

     
    void show_image(I Image& img, I string winname)
    {
        cv::Mat cvimg(img._h, img._w, CV_8UC(img._c));
        for(int i = 0; i < img._len; ++i)
        {
            cvimg.data[i] = img._data[i]*255.0;
        }
        cv::imshow(winname, cvimg);
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

     
    void print_image(I Image& img)
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

     
    Image bgr2gray(I Image& bgr_img)
    {
        if(bgr_img._len <= 0 || 1 == bgr_img._c) return bgr_img;
        assert (3 == bgr_img._c);
        Image gray_img(bgr_img._h, bgr_img._w, 1);
        for(int y = 0, i = 0, j = 0; i < gray_img._h; ++y)
        {
            for(int x = 0; x < gray_img._w; ++x)
            {
                double sum = 0;
                double b = bgr_img._data[i++]/255.0;
                double g = bgr_img._data[i++]/255.0;
                double r = bgr_img._data[i++]/255.0;
                // gray_img._data[j++] =  r*0.299 +  g*0.587 +  b*0.114;
                gray_img._data[j++] =  (r + g + b)/3.0;
            }
        }
        return gray_img;
    }

     
    int bgr2gray(I Image& bgr_img, O Image& gray_img)
    {
        if(3 != bgr_img._c) return -1;
        gray_img.reset(bgr_img._h, bgr_img._w, 1);
        for(int y = 0, i = 0, j = 0; y < gray_img._h; ++y)
        {
            for(int x = 0; x < gray_img._w; ++x)
            {
                double b = bgr_img._data[i++];
                double g = bgr_img._data[i++];
                double r = bgr_img._data[i++];
                // gray_img._data[j++] =  r*0.299 +  g*0.587 +  b*0.114;
                gray_img._data[j++] =  (r + g + b)/3.0;
            }
        }
        return 0;
    }

     
    Image operator+(I const Image& img0, I const Image& img1)
    {
        Image img_prime(img0);
        for(int i = 0; i < img_prime._len; ++i)
        {
            img_prime._data[i] += img1._data[i];
        }
        return img_prime;
    }

     
    Image operator+(I const Image& img0, I const double a)
    {
        Image img_prime(img0);
        for(int i = 0; i < img_prime._len; ++i)
        {
            img_prime._data[i] += a;
        }
        return img_prime;
    }

     
    Image operator+(I const double a, I const Image& img0)
    {
        Image img_prime(img0);
        for(int i = 0; i < img_prime._len; ++i)
        {
            img_prime._data[i] += a;
        }
        return img_prime;
    }

     
    Image operator-(I const Image& img0, I const Image& img1)
    {
        Image img_prime(img0);
        for(int i = 0; i < img_prime._len; ++i)
        {
            img_prime._data[i] -= img1._data[i];
        }
        return img_prime;
    }

     
    Image operator-(I const Image& img0, I const double a)
    {
        Image img_prime(img0);
        for(int i = 0; i < img_prime._len; ++i)
        {
            img_prime._data[i] -= a;
        }
        return img_prime;
    }

     
    Image operator-(I const double a, I const Image& img0)
    {
        Image img_prime(img0);
        for(int i = 0; i < img_prime._len; ++i)
        {
            img_prime._data[i] = a - img_prime._data[i];
        }
        return img_prime;
    }

     
    Image operator*(I const Image& img0, I const Image& img1)
    {
        Image img_prime(img0);
        for(int i = 0; i < img_prime._len; ++i)
        {
            img_prime._data[i] *= img1._data[i];
        }
        return img_prime;
    }

     
    Image operator*(I const Image& img0, I const double a)
    {
        Image img_prime(img0);
        for(int i = 0; i < img_prime._len; ++i)
        {
            img_prime._data[i] *= a;
        }
        return img_prime;
    }

     
    Image operator*(I const double a, I const Image& img0)
    {
        Image img_prime(img0);
        for(int i = 0; i < img_prime._len; ++i)
        {
            img_prime._data[i] *= a;
        }
        return img_prime;
    }

     
    Image operator/(I const Image& img0, I const Image& img1)
    {
        Image img_prime(img0);
        for(int i = 0; i < img_prime._len; ++i)
        {
            img_prime._data[i] /= img1._data[i];
        }
        return img_prime;
    }

     
    Image operator/(I const Image& img0, I const double a)
    {
        Image img_prime(img0);
        for(int i = 0; i < img_prime._len; ++i)
        {
            img_prime._data[i] /= a;
        }
        return img_prime;
    }

     
    Image operator/(I const double a, I const Image& img0)
    {
        Image img_prime(img0);
        for(int i = 0; i < img_prime._len; ++i)
        {
            img_prime._data[i] = a / img_prime._data[i];
        }
        return img_prime;
    }

    double sumproduct(I Image& img, I Image& ker, I const int offset[3])
    {
        double sum = 0;
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

    Image convolve(I Image& img, I Image& ker, I const int step[3], I const int pad_size[3])
    {
        int con_shape[3] = {(img._h+2*pad_size[0]-ker._h)/step[0]+1, (img._w+2*pad_size[1]-ker._w)/step[1]+1, (img._c+2*pad_size[2]-ker._c)/step[2]+1};
        int start[3] = {-pad_size[0], -pad_size[1], -pad_size[2]};
        int end[3] = {start[0] + con_shape[0], start[1] + con_shape[1], start[2] + con_shape[2]};
        Image con(con_shape[0], con_shape[1], con_shape[2]);
        int offset[3] = {0}, i = 0;
        for(offset[0] = start[0]; offset[0] < end[0]; offset[0] += step[0])
        {
            for(offset[1] = start[1]; offset[1] < end[1]; offset[1] += step[1])
            {
                for(offset[2] = start[2]; offset[2] < end[2]; offset[2] += step[2])
                {
                    con._data[i++] = sumproduct(img, ker, offset);
                }
            }
        }
        return con;
    }

    void convolve(I Image& img, I Image& ker, I const int step[3], I O Image& con)
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
                    con._data[i++] = sumproduct(img, ker, offset);
                }
            }
        }
    }

     
    double linear_interp_val(I Image& img, I const double y, I const double x, I const double z)
    {
        int y0 = floor(y), x0 = floor(x), z0 = floor(z);
        double dy = y-y0, dx = x-x0, dz = z-z0;
        double val = 0.0;
        int i, j, k, yt, xt, zt;
        double v_y, v_x, v_z;
        for(i = 0; i <= 1; ++i)
        {
            yt = y0 + i;
            if(0 <= yt && yt < img._h)
            {
                v_y = ( (i == 0)? 1.0 - dy : dy );
                for(j = 0; j <= 1; ++j)
                {
                    xt = x0 + j;
                    if(0 <= xt && xt < img._w)
                    {
                        v_x = v_y * ( (j == 0)? 1.0 - dx : dx );
                        for(k = 0; k <= 1; ++k)
                        {
                            zt = z0 + k;
                            if(0 <= zt && zt < img._c)
                            {
                                v_z = v_x * ( ( k == 0 )? 1.0 - dz : dz );
                                val += img.at(yt, xt, zt) * v_z;
                            }
                        }
                    }
                }
            }
        }
        return val;
    }


    Image sample_image(I Image& img, I const double rate[3])
    {
        Image sampleimg(int(img._h*rate[0]), int(img._w*rate[1]), int(img._c*rate[2]));
        double r[3] = {double(sampleimg._h)/double(img._h), double(sampleimg._w)/double(img._w), double(sampleimg._c)/double(img._c)};
        double y_prime, x_prime, z_prime;
        int y, x, z, i;
        for(y = 0, i = 0; y < sampleimg._h; ++y)
        {
            y_prime = double(y) / r[0];
            for(x = 0; x < sampleimg._w; ++x)
            {
                x_prime = double(x) / r[1];
                for(z = 0; z < sampleimg._c; ++z)
                {
                    z_prime = double(z) / r[2];
                    sampleimg._data[i++] = linear_interp_val(img, y_prime, x_prime, z_prime);
                }
            }
        }
        return sampleimg;
    }


    Image generate_gaussian_mat(I const int shape[3], I const double sigma, I const bool norm)
    {
        Image g_mat(shape[0], shape[1], shape[2]);
        double A = 0.5/(PI*sigma*sigma);
        double o[3] = {(g_mat._h-1)/2.0, (g_mat._w-1)/2.0, (g_mat._c-1)/2.0};
        int y = 0, x = 0, z = 0, i = 0;
        for(y = 0; y < g_mat._h; ++y)
        {
            for(x = 0; x < g_mat._w; ++x)
            {
                double val = A * exp(-0.5*((y-o[0])*(y-o[0]) + (x-o[1])*(x-o[1]))/(sigma*sigma));
                for(z = 0; z < g_mat._c; ++z)
                {
                    g_mat._data[i++] = val;
                }
            }
        }
        if(norm) g_mat /= g_mat.get_sum();
        return g_mat;
    }

    void img2cvmat(I Image& img, O cv::Mat& mat)
    {
        if(mat.empty())
        {
            mat.create(img._h, img._w, CV_8UC(img._c));
        }
        for(int i = 0; i < img._len; ++i)
        {
            mat.data[i] = img._data[i]*255.0;
        }
    }

 
    void cvmat2img(I cv::Mat& mat, O Image& img)
    {
        // cv::Mat fmat;
        mat.convertTo(mat, CV_8UC(mat.channels()));
        img.reset(mat.rows, mat.cols, mat.channels());
        for(int i = 0; i < img._len; ++i)
        {
            img._data[i] = mat.data[i]/255.0;
        }
    }

     
    Image gaussian_blur(I Image& img, I const int ker_shape[3], I const double sigma)
    {
        cv::Mat mat;
        img2cvmat(img, mat);
        if(3 == mat.channels()) cv::cvtColor(mat, mat, cv::COLOR_BGR2GRAY);
        mat.convertTo(mat, CV_64F);
        GaussianBlur(mat, mat, cv::Size(0,0), sigma, sigma);
        Image gimg;
        cvmat2img(mat, gimg);
        return gimg;
        // Image ker = generate_gaussian_mat(ker_shape, sigma, false);
        // int step[3] = {1, 1, 1};
        // int pad_size[3] = {int(0.5*((img._h-1)*step[0]+ker_shape[0]-img._h)), int(0.5*((img._w-1)*step[1]+ker_shape[1]-img._w)), int(0.5*((img._c-1)*step[2]+ker_shape[2]-img._c))};
        // return convolve(img, ker, step, pad_size);
    }


}

