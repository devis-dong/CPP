/*** 
 * @Author: devis dong
 * @Date: 2021-07-13 12:53:46
 * @LastEditTime: 2021-07-16 19:01:34
 * @LastEditors: devis dong
 * @Description: 
 * @FilePath: \C++\src\mat\dsmat.h
 */

#ifndef DSMAT_H
#define DSMAT_H

#include <vector>
#include <string>
#include <initializer_list>
#include "dsdefine.h"

using namespace std;

namespace ds
{
    template <typename T>
    class Mat
    {
        public:
            Mat();
            Mat(I initializer_list<int> shape);
            template <typename R>
            Mat(I initializer_list<int> shape, I const R* pdata);
            template <typename R>
            Mat(I const Mat<R> &obj);
            virtual ~Mat();
            vector<int> shape() const;
            int get_elements_num() const;
            int get_dims_num() const;
            T& at(I initializer_list<int> pos);
            T& at(I const int idx);
            T* ptr(initializer_list<int> pos);
            T* ptr(I const int idx);
            T& operator()(I initializer_list<int> pos);
            T& operator[](I const int idx);
            template <typename R>
            T& operator=(I const Mat<R>& obj);
            int reset(I initializer_list<int> shape);
        private:
            void init();
            void deinit();
        protected:
            T* _pdata;
            int _elements_num;
            int _elements_size;
            int _data_num;
            int _dims_num;
            vector<int> _shape;
            vector<int> _interval;
    };
}


#endif