/*** 
 * @Author: devis dong
 * @Date: 2021-07-13 12:55:05
 * @LastEditTime: 2021-07-14 18:37:44
 * @LastEditors: devis dong
 * @Description: 
 * @FilePath: \C++\src\Mat\dsmat.cpp
 */

#include "common/dsdefine.h"
#include "mat/dsmat.h"

namespace ds
{
    template <typename T>
    Mat<T>::Mat(I initializer_list<int> shape)
    {
        assert (shape.size() > 0);
        member_init();
        m_shape = shape;
        m_step.resize(m_shape.size());
        int step = 1;
        for(int i = m_shape.size()-1; i >= 0; step *= m_shape[i], --i) m_step[i] = step;
        m_num_of_elements = step;
        m_size_of_elements = m_num_of_elements * sizeof(T);
        m_pdata = new T[m_num_of_elements];
        assert (m_pdata != nullptr);
        memset(m_pdata, 0, m_size_of_elements);
    }

    // template <typename T>
    // template <typename R>
    // Mat<T>::Mat(I initializer_list<int> shape, I const R data)
    // {
    //     assert (shape.size() > 0);
    //     member_init();
    //     m_shape = shape;
    //     m_step.resize(m_shape.size());
    //     int step = 1;
    //     for(int i = m_shape.size()-1; i >= 0; step *= m_shape[i], --i) m_step[i] = step;
    //     m_num_of_elements = step;
    //     m_size_of_elements = m_num_of_elements * sizeof(T);
    //     m_pdata = new T[m_num_of_elements]; // {data};
    //     assert (m_pdata != nullptr);
    //     for(int i = 0; i < m_num_of_elements; ++i) m_pdata[i] = (T)data;
    // }

    template <typename T>
    template <typename R>
    Mat<T>::Mat(I initializer_list<int> shape, I const R* const pdata)
    {
        assert (shape.size() > 0);
        member_init();
        m_shape = shape;
        m_step.resize(m_shape.size());
        int step = 1;
        for(int i = m_shape.size()-1; i >= 0; step *= m_shape[i], --i) m_step[i] = step;
        m_num_of_elements = step;
        m_size_of_elements = m_num_of_elements * sizeof(T);
        m_pdata = new T[m_num_of_elements];
        assert (m_pdata != nullptr);
        for(int i = 0; i < m_num_of_elements; ++i) m_pdata[i] = (T)pdata[i];
    }

    template <typename T>
    template <typename R>
    Mat<T>::Mat(I Mat<R> &mat)
    {
        member_init();
        m_shape = mat.m_shape;
        m_step = mat.m_step;
        m_num_of_elements = mat.m_num_of_elements;
        m_size_of_elements = m_num_of_elements * sizeof(T);
        m_pdata = new T[m_num_of_elements];
        assert (m_pdata != nullptr);
        for(int i = 0; i < m_num_of_elements; ++i) m_pdata[i] = (T)mat.m_pdata[i];
    }

    template <typename T>
    int Mat<T>::reset(I initializer_list<int> shape)
    {
        assert (shape.size() > 0);
        member_free();
        member_init();
        m_shape = shape;
        m_step.resize(m_shape.size());
        int step = 1;
        for(int i = m_shape.size()-1; i >= 0; step *= m_shape[i], --i) m_step[i] = step;
        m_num_of_elements = step;
        m_size_of_elements = m_num_of_elements * sizeof(T);
        m_pdata = new T[m_num_of_elements];
        assert (m_pdata != nullptr);
        memset(m_pdata, 0, m_size_of_elements);

        return 0;
    }

    template <typename T>
    Mat<T>::~Mat()
    {
        member_free();
    }

    template <typename T>
    void Mat<T>::member_init()
    {
        m_pdata = nullptr;
        m_shape.clear();
        m_num_of_elements = 0;
        m_size_of_elements = 0;
    }

    template <typename T>
    void Mat<T>::member_free()
    {
        m_size_of_elements = 0;
        m_num_of_elements = 0;
        m_shape.clear();
        if(m_pdata) delete [] m_pdata;
    }

    template <typename T>
    vector<int> Mat<T>::shape() const
    {
        return m_shape;
    }

    template <typename T>
    int Mat<T>::num_of_elements() const
    {
        return m_num_of_elements;
    }

    template <typename T>
    int Mat<T>::size_of_elements() const
    {
        return m_size_of_elements;
    }

    template <typename T>
    int Mat<T>::dims() const
    {
        return m_shape.size();
    }

    // template <typename T>
    // T& Mat<T>::at(initializer_list<int> pos)
    // {
    //     assert (0 < pos.size() && pos.size() <= m_shape.size());
    //     int idx = 0, i = 0;
    //     for(initializer_list<int>::iterator it = pos.begin(); it != pos.end(); ++it, ++i)
    //     {
    //         assert ((*it) < m_shape[i]);
    //         idx += ((*it) * m_step[i]);
    //     }
    //     return m_pdata[idx];
    // }

    template <typename T>
    template <typename ...Args>
    T& Mat<T>::at(Args&&... args)
    {
        initializer_list<int> pos = {(std::forward<Args>(args))...};
        int idx = 0, i = 0;
        for(initializer_list<int>::iterator it = pos.begin(); it != pos.end(); ++it, ++i)
        {
            assert ((*it) < m_shape[i]);
            idx += ((*it) * m_step[i]);
        }
        return m_pdata[idx];
    }

    // template <typename T>
    // T* Mat<T>::ptr(initializer_list<int> pos)
    // {
    //     assert (0 < pos.size() && pos.size() <= m_shape.size());
    //     int idx = 0, i = 0;
    //     for(initializer_list<int>::iterator it = pos.begin(); it != pos.end(); ++it, ++i)
    //     {
    //         assert ((*it) < m_shape[i]);
    //         idx += ((*it) * m_step[i]);
    //     }
    //     return m_pdata + idx;
    // }

    template <class T>
    template <typename ...Args>
    T* Mat<T>::ptr(Args&&... args)
    {
        initializer_list<int> pos = {(std::forward<Args>(args))...};
        assert (0 < pos.size() && pos.size() <= m_shape.size());
        int idx = 0, i = 0;
        for(initializer_list<int>::iterator it = pos.begin(); it != pos.end(); ++it, ++i)
        {
            assert ((*it) < m_shape[i]);
            idx += ((*it) * m_step[i]);
        }
        return m_pdata + idx;
    }

    template <typename T>
    template <typename ...Args>
    T& Mat<T>::operator()(Args&&... args)
    {
        initializer_list<int> pos = {(std::forward<Args>(args))...};
        int idx = 0, i = 0;
        for(initializer_list<int>::iterator it = pos.begin(); it != pos.end(); ++it, ++i)
        {
            assert ((*it) < m_shape[i]);
            idx += ((*it) * m_step[i]);
        }
        return m_pdata[idx];
    }

    template <typename T>
    T& Mat<T>::operator[](I const int i)
    {
        return m_pdata[i];
    }

    template <typename T>
    int Mat<T>::step(I const int i) const
    {
        assert (0 <= i && i < m_step.size());
        return m_step[i];
    }

}

