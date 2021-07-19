/*** 
 * @Author: devis dong
 * @Date: 2021-07-19 14:46:42
 * @LastEditTime: 2021-07-19 19:50:11
 * @LastEditors: devis dong
 * @Description: 
 * @FilePath: \C++\src\dsvec\dsvec.cpp
 */


#include <stdlib.h>
#include <assert.h>
#include "dsvec.h"
using namespace std;


namespace ds
{
    template<typename T>
    Vec<T>::Vec()
    {
        init();
    }

    template<typename T>
    Vec<T>::Vec(I const int dims, I const T val)
    {
        init();
        _dims = dims;
        _data = new T[_dims];
        assert (nullptr != _data);
        if(0 == val) memset(_data, 0, _dims*sizeof(T));
        else for (int i = 0; i < _dims; ++i) _data[i] = (T)val;
    }

    // template<typename T>
    // Vec<T>::Vec(I const int dims, I const T* data)
    // {
    //     init();
    //     _dims = dims;
    //     _data = new T[_dims];
    //     assert (nullptr != _data);
    //     if(nullptr == data) memset(_data, 0, _dims*sizeof(T));
    //     else memcpy(_data, data, _dims*sizeof(T));
    // }

    template<typename T>
    Vec<T>::Vec(I initializer_list<T> shape)
    {
        assert (shape.size() > 0);
        init();
        _dims = shape.size();
        _data = new T[_dims];
        assert (nullptr != _data);
        int id = 0;
        for(auto it = shape.begin(); it != shape.end(); ++it, ++id) _data[id] = *it;
    }

    template<typename T>
    Vec<T>::Vec(I const Vec<T>& obj)
    {
        init();
        _dims = obj._dims;
        _data = new T[_dims];
        assert (nullptr != _data);
        memcpy(_data, obj._data, _dims*sizeof(T));
    }

    template <typename T>
    int Vec<T>::size()
    {
        return _dims;
    }

    template <typename T>
    T& Vec<T>::operator=(I const Vec<T>& obj)
    {
        if(this == &obj) return *this;
        deinit();
        _dims = obj._dims;
        _data = new T[_dims];
        assert (nullptr != _data);
        memcpy(_data, obj._data, _dims*sizeof(T));
    }

    template <typename T>
    T& Vec<T>::operator[](I const int idx)
    {
        return _data[idx];
    }

    template<typename T>
    Vec<T>::~Vec()
    {
        deinit();
    }

    template<typename T>
    void Vec<T>::init()
    {
        _dims = 0;
        _data = nullptr;
    }

    template<typename T>
    void Vec<T>::deinit()
    {
        _dims = 0;
        if(nullptr != _data)
        {
            delete _data;
            _data = nullptr;
        }
    }

    template<typename T>
    Vec<T> Vec<T>::operator++()
    {
        for(int i = 0; i < _dims; ++i)
        {
            ++_data[i];
        }
        return *this;
    }

    template<typename T>
    Vec<T> Vec<T>::operator--()
    {
        for(int i = 0; i < _dims; ++i)
        {
            --_data[i];
        }
        return *this;
    }

    template<typename T>
    Vec<T> Vec<T>::operator++(int)
    {
        Vec<T> ori(*this);
        for(int i = 0; i < _dims; ++i)
        {
            ++_data[i];
        }
        return ori;
    }

    template<typename T>
    Vec<T> Vec<T>::operator--(int)
    {
        Vec<T> ori(*this);
        for(int i = 0; i < _dims; ++i)
        {
            --_data[i];
        }
        return ori;
    }

    template<typename T>
    Vec<T> operator+(I const Vec<T>& vec0, I const Vec<T>& vec1)
    {
        assert (vec0._dims == vec1._dims);
        Vec<T> vec2(vec0._dims);
        for(int i = 0; i < vec0._dims; ++i)
        {
            vec2._data[i] = vec0._data[i] + vec1._data[i];
        }
        return vec2;
    }

    template<typename T>
    Vec<T> operator-(I const Vec<T>& vec0, I const Vec<T>& vec1)
    {
        assert (vec0._dims == vec1._dims);
        Vec<T> vec2(vec0._dims);
        for(int i = 0; i < vec0._dims; ++i)
        {
            vec2._data[i] = vec0._data[i] - vec1._data[i];
        }
        return vec2;
    }

    template<typename T>
    Vec<T> operator*(I const Vec<T>& vec0, I const Vec<T>& vec1)
    {
        assert (vec0._dims == vec1._dims);
        Vec<T> vec2(vec0._dims);
        for(int i = 0; i < vec0._dims; ++i)
        {
            vec2._data[i] = vec0._data[i] * vec1._data[i];
        }
        return vec2;
    }

    template<typename T>
    Vec<T> operator/(I const Vec<T>& vec0, I const Vec<T>& vec1)
    {
        assert (vec0._dims == vec1._dims);
        Vec<T> vec2(vec0._dims);
        for(int i = 0; i < vec0._dims; ++i)
        {
            vec2._data[i] = vec0._data[i] / vec1._data[i];
        }
        return vec2;
    }

    int vec2idx(I const Vec<int>& vec0, I const Vec<int>& shape)
    {
        int idx = 0, interval = 1;
        for(int i = vec0._dims-1; i >= 0; --i)
        {
            idx += interval * vec0._data[i];
            interval *= shape._data[i];
        }
        return idx;
    }

    Vec<int> idx2vec(I int idx, I const Vec<int>& shape)
    {
        Vec<int> vec0(shape._dims);
        for(int i = shape._dims-1; i >= 0; --i)
        {
            vec0._data[i] = idx % shape._data[i];
            idx /= shape._data[i];
        }
        return vec0;
    }

    template<typename T>
    bool move2next(I O Vec<T>& p, I Vec<T>& start, I Vec<T>& step, I Vec<T>& end)
    {
        for(int i = p._dims-1; i >= 0; --i)
        {
            p._data[i] += step._data[i];
            if(end._data[i] != p._data[i])
            {
                return true;
            }
            else
            {
                p._data[i] = start._data[i];
            }
        }
        return false;
    }

    template<typename T>
    void printvec(I Vec<T>& vec0)
    {
        cout<<"(";
        for(int i = 0; i < vec0._dims-1; ++i)
        {
            cout<<vec0[i]<<",";
        }
        cout<<vec0[vec0._dims-1]<<")"<<endl;
    }

}


