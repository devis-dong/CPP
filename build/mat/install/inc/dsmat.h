/*** 
 * @Author: devis dong
 * @Date: 2021-07-13 12:53:46
 * @LastEditTime: 2021-07-16 16:57:53
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
            T& at(initializer_list<int> pos);
            T* ptr(initializer_list<int> pos);
            T& operator[](I const int i);
            template <typename R>
            T& operator=(I const Mat<R>& obj);
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