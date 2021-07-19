/*** 
 * @Author: devis dong
 * @Date: 2021-07-19 00:48:35
 * @LastEditTime: 2021-07-19 14:05:59
 * @LastEditors: devis dong
 * @Description: 
 * @FilePath: \C++\src\dsmat\dsmat.cpp
 */


#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "dsmat.h"
#include "opencv.hpp"


namespace ds
{
    void coord_add(int* coor0, int* coor1, int* coor2, int dims)
    {
        for(int i = 0; i < dims; ++i)
        {
            coor2[i] = coor0[i] + coor1[i];
        }
    }

    void coord_add_one(int* coord, int dims)
    {
        for(int i = 0; i < dims; ++i)
        {
            coord[i] += 1;
        }
    }

    void coord_sub(int* coor0, int* coor1, int* coor2, int dims)
    {
        for(int i = 0; i < dims; ++i)
        {
            coor2[i] = coor0[i] - coor1[i];
        }
    }

    void coord_sub_one(int* coord, int dims)
    {
        for(int i = 0; i < dims; ++i)
        {
            coord[i] -= 1;
        }
    }

    int coord2idx(int* p, int* shape, int dims)
    {
        int idx = 0, interval = 1;
        for(int i = dims-1; i >= 0; --i)
        {
            idx += interval * p[i];
            interval *= shape[i];
        }
        return idx;
    }

    void idx2coord(int idx, int* coord, int* shape, int dims)
    {
        for(int i = dims-1; i >= 0; --i)
        {
            coord[i] = idx % shape[i];
            idx /= shape[i];
        }
    }

    template <typename M, typename K>
    void get_convoled_shape(Mat<M>& mat, Mat<K>& ker, int* step, int* shape_con)
    {
        assert (mat._dims == ker._dims);
        for(int i = 0; i < mat._dims; ++i)
        {
            shape_con[i] = (mat._shape[i] - ker._shape[i])/step[i] + 1;
        }
    }

    bool move2next(int* p, int* start, int* step, int* end, const int n)
    {
        for(int i = n-1; i >= 0; --i)
        {
            p[i] += step[i];
            // assert ((start[i] <= p[i] && p[i] <= end[i]) || (end[i] <= p[i] && p[i] <= start[i]));
            if(end[i] != p[i])
            {
                return true;
            }
            else
            {
                p[i] = start[i];
            }
        }
        return false;
    }

    int get_step(int* start, int* end, int* step, int n)
    {
        for(int i = 0; i < n; ++i)
        {
            step[i] = start[i] < end[i] ? 1 : -1;
        }
        return 0;
    }

    template <typename U, typename V, typename T>
    T sumproduct(Mat<U>& mat, Mat<V>& ker, int* offset=nullptr)
    {
        int pstart[64] = {0}, pend[64] = {0}, p[64] = {0}, pstep[64] = {0}, dims = mat._dims;
        if(nullptr != offset) coord_add(pstart, offset, pstart, dims);
        coord_add(pstart, ker._shape, pend, dims);
        memcpy(p, pstart, dims*sizeof(int));
        get_step(pstart, pend, pstep, dims);
        T sum = 0;
        int i = -1, j = -1;
        do
        {
            ++i;
            j = coord2idx(p, mat._shape, dims);
            sum += mat._data[j]*ker._data[i];
        }while(move2next(p, pstart, pstep, pend, dims) && i < ker._len);
        return sum;
    }

    template <typename U, typename V, typename T>
    Mat<T> convolve(Mat<U>& mat, Mat<V>& ker, int* step)
    {
        assert (mat._dims == ker._dims);
        int offset[64] = {0}, start[64] = {0}, end[64] = {0}, shape_con[64] = {0};
        coord_sub(mat._shape, ker._shape, end, mat._dims);
        coord_add_one(end, mat._dims);
        get_convoled_shape(mat, ker, step, shape_con);
        Mat<T> con(shape_con, mat._dims);
        int idx = 0;
        do
        {
            con._data[idx] = sumproduct<U, V, T>(mat, ker, offset);
        }while(move2next(offset, start, step, end, mat._dims) && idx++ < con._len);
        return con;
    }

    template <typename U, typename V, typename T>
    void convolve(I Mat<U>& mat, I Mat<V>& ker, I int* step, O Mat<T>& con)
    {
        assert (mat._dims == ker._dims);
        int offset[64] = {0}, start[64] = {0}, end[64] = {0}, shape_con[64] = {0};
        coord_sub(mat._shape, ker._shape, end, mat._dims);
        coord_add_one(end, mat._dims);
        get_convoled_shape(mat, ker, step, shape_con);
        con.reset(shape_con, mat._dims, 0);
        int idx = 0;
        do
        {
            con._data[idx] = sumproduct<U, V, T>(mat, ker, offset);
        }while(move2next(offset, start, step, end, mat._dims) && idx++ < con._len);
    }


//==============================================================================================


    template <typename T>
    void Mat<T>::init()
    {
        _data = nullptr;
        memset(_shape, 0, 64*sizeof(int));
        memset(_steps, 0, 64*sizeof(int));
        _dims = 0;
    }

    template <typename T>
    void Mat<T>::deinit()
    {
        _dims = 0;
        memset(_steps, 0, 64*sizeof(int));
        memset(_shape, 0, 64*sizeof(int));
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
        _shape[0] = cvimg.cols; _shape[1] = cvimg.rows; _shape[2] = cvimg.channels();
        _len = 1;
        for(int i = _dims-1; i >= 0; _steps[i] = _len, _len *= _shape[i], --i);
        _data = new T[_len];
        assert (_data != nullptr);
        for(int i = 0; i < _len; ++i) _data[i] = (T)cvimg.data[i];
    }

    template <typename T>
    Mat<T>::Mat(I const int* shape, I const int dims, I const T val)
    {
        init();
        _dims = dims;
        memcpy(_shape, shape, dims*sizeof(int));
        _len = 1;
        for(int i = _dims-1; i >= 0; _steps[i] = _len, _len *= _shape[i], --i);
        _data = new T[_len];
        assert (_data != nullptr);
        for(int i = 0; i < _len; ++i) _data[i] = val;
    }

    template <typename T>
    Mat<T>::Mat(I initializer_list<int> shape, I const T val)
    {
        assert (shape.size() > 0);
        init();
        _dims = shape.size();
        int id = 0;
        for(auto it = shape.begin(); it != shape.end(); ++it, ++id) _shape[id] = *it;
        _len = 1;
        for(int i = _dims-1; i >= 0; _steps[i] = _len, _len *= _shape[i], --i);
        _data = new T[_len];
        assert (_data != nullptr);
        for(int i = 0; i < _len; ++i) _data[i] = val;
    }

    template <typename T>
    template <typename R>
    Mat<T>::Mat(I initializer_list<int> shape, I const R* data)
    {
        assert (shape.size() > 0);
        init();
        _dims = shape.size();
        int id = 0;
        for(auto it = shape.begin(); it != shape.end(); ++it, ++id) _shape[id] = *it;
        _len = 1;
        for(int i = _dims-1; i >= 0; _steps[i] = _len, _len *= _shape[i], --i);
        _data = new T[_len];
        assert (_data != nullptr);
        if(typeid(T) == typeid(R)) memcpy(_data, data, _len*sizeof(T));
        else for(int i = 0; i < _len; ++i) _data[i] = (T)data[i];
    }

    template <typename T>
    template <typename R>
    Mat<T>::Mat(I const Mat<R> &obj)
    {
        init();
        _dims = obj._dims;
        _len = obj._len;
        memcpy(_shape, obj._shape, _dims*sizeof(int));
        memcpy(_steps, obj._steps, _dims*sizeof(int));
        _data = new T[_len];
        assert (_data != nullptr);
        if(typeid(T) == typeid(R)) memcpy(_data, obj._data, _len*sizeof(T));
        else for(int i = 0; i < _len; ++i) _data[i] = (T)obj._data[i];
    }

    template <typename T>
    template <typename R>
    T& Mat<T>::operator=(I const Mat<R>& obj)
    {
        if(this == &obj) return *this;
        deinit();
        _dims = obj._dims;
        _len = obj._len;
        memcpy(_shape, obj._shape, _dims*sizeof(int));
        memcpy(_steps, obj._steps, _dims*sizeof(int));
        _data = new T[_len];
        assert (_data != nullptr);
        if(typeid(T) == typeid(R)) memcpy(_data, obj._data, _len*sizeof(T));
        else for(int i = 0; i < _len; ++i) _data[i] = (T)obj._data[i];
    }

    template <typename T>
    Mat<T>::~Mat()
    {
        deinit();
    }

    template <typename T>
    T& Mat<T>::at(initializer_list<int> pos)
    {
        assert (pos.size() == _dims);
        int idx = 0, i = 0, *step = _steps;
        for(initializer_list<int>::iterator it = pos.begin(); it != pos.end(); ++it, ++step)
        {
            assert ((*it) < _shape[i]);
            idx += ((*it) * (*step));
        }
        return _data[idx];
    }

    template <typename T>
    T* Mat<T>::ptr(initializer_list<int> pos)
    {
        assert (pos.size() == _dims);
        int idx = 0, i = 0, *step = _steps;
        for(initializer_list<int>::iterator it = pos.begin(); it != pos.end(); ++it, ++step)
        {
            assert ((*it) < _shape[i]);
            idx += ((*it) * (*step));
        }
        return _data + idx;
    }


    template <typename T>
    int Mat<T>::reset(I initializer_list<int> shape, I const T val)
    {
        assert (shape.size() > 0);
        deinit();
        _dims = shape.size();
        int id = 0;
        for(auto it = shape.begin(); it != shape.end(); ++it, ++id) _shape[id] = *it;
        _len = 1;
        for(int i = _dims-1; i >= 0; _steps[i] = _len, _len *= _shape[i], --i);
        _data = new T[_len];
        assert (_data != nullptr);
        for(int i = 0; i < _len; ++i) _data[i] = val;
        return 0;
    }

    template <typename T>
    int Mat<T>::reset(I const int* shape, I const int dims, I const T val)
    {
        deinit();
        _dims = dims;
        memcpy(_shape, shape, dims*sizeof(int));
        _len = 1;
        for(int i = _dims-1; i >= 0; _steps[i] = _len, _len *= _shape[i], --i);
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
            cv::Mat cvimg(mat._shape[0], mat._shape[1], CV_8UC(mat._shape[2]), data);
            cv::imshow(winname, cvimg);
        }
        else
        {
            cv::Mat cvimg(mat._shape[0], mat._shape[1], CV_8UC(mat._shape[2]), mat._data);
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

