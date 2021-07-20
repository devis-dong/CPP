/*** 
 * @Author: devis dong
 * @Date: 2021-07-19 00:48:35
 * @LastEditTime: 2021-07-19 23:22:25
 * @LastEditors: devis dong
 * @Description: 
 * @FilePath: \C++\src\dsmat\dsmat_cpp.cpp
 */


#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "dsmat_cpp.h"
#include "opencv.hpp"
#include "dsvec.cpp"


namespace ds
{
    template <typename M, typename K>
    Vec<int> get_convoled_shape(Mat<M>& mat, Mat<K>& ker, Vec<int>& step)
    {
        assert (mat._dims == ker._dims);
        Vec<int> shape_con(mat._dims, 0);
        for(int i = 0; i < mat._dims; ++i)
        {
            shape_con._data[i] = (mat._shape->_data[i] - ker._shape->_data[i])/step._data[i] + 1;
        }
        return shape_con;
    }

    Vec<int> get_step(Vec<int>& start, Vec<int>& end)
    {
        Vec<int> step(start._dims, 0);
        for(int i = 0; i < start._dims; ++i)
        {
            step._data[i] = start._data[i] < end._data[i] ? 1 : -1;
        }
        return step;
    }

    template <typename U, typename V, typename T>
    T sumproduct(Mat<U>& mat, Mat<V>& ker, Vec<int>& offset)
    {
        Vec<int> start(offset), end(offset+*(ker._shape));
        Vec<int> step = get_step(start, end);
        T sum = 0;
        Vec<int> p(offset);
        int i = -1, j = -1;
        do
        {
            ++i;
            // printvec(p);
            j = vec2idx(p, *(mat._shape));
            sum += mat._data[j]*ker._data[i];
        }while(move2next(p, start, step, end) && i < ker._len);
        return sum;
    }

    template <typename U, typename V, typename T>
    Mat<T> convolve(I Mat<U>& mat, I Mat<V>& ker, I Vec<int>& step)
    {
        assert (mat._dims == ker._dims && ker._dims == step._dims);
        Vec<int> offset(mat._dims, 0), start(mat._dims, 0);
        Vec<int> end = ++(*(mat._shape) - *(ker._shape));
        Vec<int> shape_con = get_convoled_shape(mat, ker, step);
        Mat<T> con(shape_con);
        int idx = 0;
        do
        {
            con._data[idx] = sumproduct<U, V, T>(mat, ker, offset);
        }while(move2next(offset, start, step, end) && idx++ < con._len);
        return con;
    }

    template <typename U, typename V, typename T>
    void convolve(I Mat<U>& mat, I Mat<V>& ker,  I Vec<int>& step, O Mat<T>& con)
    {
        assert (mat._dims == ker._dims);
        Vec<int> offset(mat._dims, 0), start(mat._dims, 0);
        Vec<int> end = ++(*(mat._shape) - *(ker._shape));
        Vec<int> shape_con = get_convoled_shape(mat, ker, step);
        con.reset(shape_con, 0);
        int idx = 0;
        do
        {
            con._data[idx] = sumproduct<U, V, T>(mat, ker, offset);
        }while(move2next(offset, start, step, end) && idx++ < con._len);
    }

    // template <typename T>
    // Mat<T> sample(I Mat<T>& mat, I Vec<double> rate)
    // {
    //     Vec<double> shape_dst = vec_mul();
    // }


//==============================================================================================


    template <typename T>
    void Mat<T>::init()
    {
        _data = nullptr;
        _shape = nullptr;
        _steps = nullptr;
        _dims = 0;
        _len = 0;
    }

    template <typename T>
    void Mat<T>::deinit()
    {
        _len = 0;
        _dims = 0;

        if(nullptr != _steps)
        {
            delete _steps;
            _steps = nullptr;
        }

        if(nullptr != _shape)
        {
            delete _shape;
            _shape = nullptr;
        }
        
        if(nullptr != _data)
        {
            delete[] _data;
            _data = nullptr;
        }
    }

    template<typename T>
    Mat<T>::Mat()
    {
        init();
    }

    template<typename T>
    Mat<T>::Mat(I const string& filepath, I const int flag)
    {
        cv::Mat cvimg = cv::imread(filepath, flag);
        assert (!cvimg.empty());
        init();
        _dims = 3;
        _shape = new Vec<int>({cvimg.cols, cvimg.rows, cvimg.channels()});
        assert (nullptr != _shape);
        _steps = new Vec<int>(_dims);
        assert (nullptr != _shape);
        _len = 1;
        for(int i = _dims-1; i >= 0; _steps->_data[i] = _len, _len *= _shape->_data[i], --i);
        _data = new T[_len];
        assert (_data != nullptr);
        for(int i = 0; i < _len; ++i) _data[i] = (T)cvimg.data[i];
    }

    template <typename T>
    Mat<T>::Mat(I initializer_list<T> shape, I const T val)
    {
        assert (shape.size() > 0);
        init();
        _dims = shape.size();
        _shape = new Vec<int>(shape);
        assert (nullptr != _shape);
        _steps = new Vec<int>(_dims);
        assert (nullptr != _shape);
        _len = 1;
        for(int i = _dims-1; i >= 0; _steps->_data[i] = _len, _len *= _shape->_data[i], --i);
        _data = new T[_len];
        assert (_data != nullptr);
        for(int i = 0; i < _len; ++i) _data[i] = val;
    }

    template <typename T>
    Mat<T>::Mat(I Vec<int>& shape, I const T val)
    {
        assert (shape.size() > 0);
        init();
        _dims = shape.size();
        _shape = new Vec<int>(shape);
        assert (nullptr != _shape);
        _steps = new Vec<int>(_dims);
        assert (nullptr != _shape);
        _len = 1;
        for(int i = _dims-1; i >= 0; _steps->_data[i] = _len, _len *= _shape->_data[i], --i);
        _data = new T[_len];
        assert (_data != nullptr);
        for(int i = 0; i < _len; ++i) _data[i] = val;
    }

    // template <typename T>
    // template <typename R>
    // Mat<T>::Mat(I Vec<int> shape, I const R* data)
    // {
    //     assert (shape.size() > 0);
    //     init();
    //     _dims = shape.size();
    //     _shape = new Vec<int>(shape);
    //     assert (nullptr != _shape);
    //     _steps = new Vec<int>(_dims);
    //     assert (nullptr != _shape);
    //     _len = 1;
    //     for(int i = _dims-1; i >= 0; _steps->_data[i] = _len, _len *= _shape->_data[i], --i);
    //     _data = new T[_len];
    //     assert (_data != nullptr);
    //     if(typeid(T) == typeid(R)) memcpy(_data, data, _len*sizeof(T));
    //     else for(int i = 0; i < _len; ++i) _data[i] = (T)data[i];
    // }

    template <typename T>
    Mat<T>::Mat(I const Mat<T> &obj)
    {
        init();
        _dims = obj._dims;
        _shape = new Vec<int>(*(obj._shape));
        assert (nullptr != _shape);
        _steps = new Vec<int>(*(obj._steps));
        _len = obj._len;
        _data = new T[_len];
        assert (_data != nullptr);
        memcpy(_data, obj._data, _len*sizeof(T));
    }

    template <typename T>
    T& Mat<T>::operator=(I const Mat<T>& obj)
    {
        if(this == &obj) return *this;
        deinit();
        _dims = obj._dims;
        _shape = new Vec<int>(*(obj._shape));
        assert (nullptr != _shape);
        _steps = new Vec<int>(*(obj._steps));
        _len = obj._len;
        _data = new T[_len];
        assert (_data != nullptr);
        memcpy(_data, obj._data, _len*sizeof(T));
        return *this;
    }

    template <typename T>
    Mat<T>::~Mat()
    {
        deinit();
    }

    template <typename T>
    T& Mat<T>::at(Vec<int> pos)
    {
        assert (pos.size() == _dims);
        int idx = 0;
        for(int i = 0; i < pos.size(); ++i)
        {
            assert (pos._data[i] < _shape->_data[i]);
            idx += (pos._data[i] * _steps->_data[i]);
        }
        return _data[idx];
    }

    template <typename T>
    T* Mat<T>::ptr(Vec<int> pos)
    {
        assert (pos.size() == _dims);
        int idx = 0;
        for(int i = 0; i < pos.size(); ++i)
        {
            assert (pos._data[i] < _shape->_data[i]);
            idx += (pos._data[i] * _steps->_data[i]);
        }
        return _data + idx;
    }


    template <typename T>
    int Mat<T>::reset(I Vec<int> shape, I const T val)
    {
        assert (shape.size() > 0);
        deinit();
        _dims = shape.size();
        _shape = new Vec<int>(shape);
        assert (nullptr != _shape);
        _steps = new Vec<int>(_dims);
        assert (nullptr != _shape);
        _len = 1;
        for(int i = _dims-1; i >= 0; _steps->_data[i] = _len, _len *= _shape->_data[i], --i);
        _data = new T[_len];
        assert (_data != nullptr);
        for(int i = 0; i < _len; ++i) _data[i] = val;
        return 0;
    }

    template <typename T>
    void Mat<T>::show(I Mat<T>& mat, I const string winname)
    {
        assert (mat._dims >= 3);
        uchar* data = nullptr;
        if(typeid(T) != typeid(uchar))
        {
            data = new uchar[mat._len];
            assert (nullptr != data);
            for(int i = 0; i < mat._len; ++i)
            {
                data[i] = (uchar)mat._data[i];
            }
            cv::Mat cvimg(mat._shape->_data[0], mat._shape->_data[1], CV_8UC(mat._shape->_data[2]), data);
            cv::imshow(winname, cvimg);
        }
        else
        {
            cv::Mat cvimg(mat._shape->_data[0], mat._shape->_data[1], CV_8UC(mat._shape->_data[2]), mat._data);
            cv::imshow(winname, cvimg);
        }

        if(nullptr != data)
        {
            delete[] data;
        }
    }

    template <typename T>
    void Mat<T>::waitkey(I const int delay)
    {
        cv::waitKey(delay);
    }

    template <typename T>
    void Mat<T>::close(I const string winname)
    {
        cv::destroyWindow(winname);
    }

    template <typename T>
    void Mat<T>::close()
    {
        cv::destroyAllWindows();
    }

}

