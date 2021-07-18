/*** 
 * @Author: devis dong
 * @Date: 2021-07-13 12:55:05
 * @LastEditTime: 2021-07-17 20:54:12
 * @LastEditors: devis dong
 * @Description: 
 * @FilePath: \C++\src\dsmat\dsmat.cpp
 */


#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "dsmat.h"
#include "opencv.hpp"

using namespace std;

namespace ds
{
    template <typename T>
    void Mat<T>::init()
    {
        _pdata = nullptr;
        _shape.clear();
        _interval.clear();
        _elements_num = 0;
        _elements_size = 0;
    }

    template <typename T>
    void Mat<T>::deinit()
    {
        _elements_size = 0;
        _elements_num = 0;
        _shape.clear();
        _interval.clear();
        if(nullptr != _pdata)
        {
            delete [] _pdata;
            _pdata = nullptr;
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
        _shape.push_back(cvimg.cols); _shape.push_back(cvimg.rows); _shape.push_back(cvimg.channels());
        _interval.resize(_shape.size());
        _elements_num = 1;
        for(int i = _shape.size()-1; i >= 0; _interval[i] = _elements_num, _elements_num *= _shape[i], --i);
        _elements_size = _elements_num * sizeof(T);
        _pdata = new T[_elements_num];
        assert (_pdata != nullptr);
        for(int i = 0; i < _elements_num; ++i) _pdata[i] = (T)cvimg.data[i];
    }

    template <typename T>
    Mat<T>::Mat(I initializer_list<int> shape)
    {
        assert (shape.size() > 0);
        init();
        _shape = shape;
        _interval.resize(_shape.size());
        _elements_num = 1;
        for(int i = _shape.size()-1; i >= 0; _interval[i] = _elements_num, _elements_num *= _shape[i], --i);
        _elements_size = _elements_num * sizeof(T);
        if(_elements_num)
        _pdata = new T[_elements_num];
        assert (_pdata != nullptr);
    }

    template <typename T>
    template <typename R>
    Mat<T>::Mat(I initializer_list<int> shape, I const R* pdata)
    {
        assert (shape.size() > 0);
        init();
        _shape = shape;
        _interval.resize(_shape.size());
        _elements_num = 1;
        for(int i = _shape.size()-1; i >= 0; _interval[i] = _elements_num, _elements_num *= _shape[i], --i);
        _elements_size = _elements_num * sizeof(T);
        _pdata = new T[_elements_num];
        assert (_pdata != nullptr);
        if(nullptr != pdata) for(int i = 0; i < _elements_num; ++i) _pdata[i] = (T)pdata[i];
    }

    template <typename T>
    template <typename R>
    Mat<T>::Mat(I const Mat<R> &obj)
    {
        init();
        _shape = obj._shape;
        _interval = obj._interval;
        _elements_num = obj._elements_num;
        _elements_size = _elements_num * sizeof(T);
        _pdata = new T[_elements_num];
        assert (_pdata != nullptr);
        for(int i = 0; i < _elements_num; ++i) _pdata[i] = (T)obj._pdata[i];
    }

    template <typename T>
    template <typename R>
    T& Mat<T>::operator=(I const Mat<R>& obj)
    {
        if(this == &obj)
        {
            return *this;
        }
        deinit();
        _shape = obj._shape;
        _interval = obj._interval;
        _elements_num = obj._elements_num;
        _elements_size = _elements_num * sizeof(T);
        _pdata = new T[_elements_num];
        assert (_pdata != nullptr);
        for(int i = 0; i < _elements_num; ++i) _pdata[i] = (T)obj._pdata[i];
    }

    template <typename T>
    Mat<T>::~Mat()
    {
        deinit();
    }

    template <typename T>
    vector<int> Mat<T>::shape() const
    {
        return _shape;
    }

    template <typename T>
    int Mat<T>::get_elements_num() const
    {
        return _elements_num;
    }

    template <typename T>
    int Mat<T>::get_dims_num() const
    {
        return _shape.size();
    }

    template <typename T>
    T& Mat<T>::at(initializer_list<int> pos)
    {
        assert (0 < pos.size() && pos.size() <= _shape.size());
        int idx = 0, i = 0, *step = &_interval[0];
        for(initializer_list<int>::iterator it = pos.begin(); it != pos.end(); ++it, ++step)
        {
            assert ((*it) < _shape[i]);
            idx += ((*it) * (*step));
        }
        return _pdata[idx];
    }

    template <typename T>
    T& Mat<T>::at(I const int idx)
    {
        assert (idx < _elements_num);
        return _pdata[idx];
    }

    template <typename T>
    T* Mat<T>::ptr(initializer_list<int> pos)
    {
        assert (0 < pos.size() && pos.size() <= _shape.size());
        int idx = 0, i = 0;
        for(initializer_list<int>::iterator it = pos.begin(); it != pos.end(); ++it, ++i)
        {
            assert ((*it) < _shape[i]);
            idx += ((*it) * _interval[i]);
        }
        return _pdata + idx;
    }

    template <typename T>
    T* Mat<T>::ptr(I const int idx)
    {
        assert (idx < _elements_num);
        return _pdata + idx;
    }

    template <typename T>
    T& Mat<T>::operator()(I initializer_list<int> pos)
    {
        return this->at(pos);
    }

    template <typename T>
    T& Mat<T>::operator[](I const int idx)
    {
        assert (idx < _elements_num);
        return _pdata[idx];
    }

    template <typename T>
    int Mat<T>::reset(I initializer_list<int> shape)
    {
        assert (shape.size() > 0);
        deinit();
        _shape = shape;
        _interval.resize(_shape.size());
        _elements_num = 1;
        for(int i = _shape.size()-1; i >= 0; _interval[i] = _elements_num, _elements_num *= _shape[i], --i);
        _elements_size = _elements_num * sizeof(T);
        _pdata = new T[_elements_num];
        assert (_pdata != nullptr);
        return 0;
    }

    template class Mat<char>;
    template class Mat<int>;
    template class Mat<long>;
    template class Mat<long long>;
    template class Mat<float>;
    template class Mat<double>;
    template class Mat<unsigned char>;
    template class Mat<unsigned int>;
    template class Mat<unsigned long>;
    template class Mat<unsigned long long>;

}

