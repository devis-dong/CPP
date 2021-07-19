/*** 
 * @Author: devis dong
 * @Date: 2021-07-19 00:37:38
 * @LastEditTime: 2021-07-19 14:00:55
 * @LastEditors: devis dong
 * @Description: 
 * @FilePath: \C++\src\dsmat\dsmat.h
 */

#ifndef DSMAT_H
#define DSMAT_H

#include <string>
#include "dsdefine.h"
using namespace std;


namespace ds
{
    template <typename T>
    class Mat
    {
        public:
            Mat();
            Mat(I const string& filepath, I const int flag=1);
            Mat(I const int* shape, I const int dims, I const T val=0);
            Mat(I initializer_list<int> shape, I const T val=0);
            template <typename R>
            Mat(I initializer_list<int> shape, I const R* data);
            template <typename R>
            Mat(I const Mat<R> &obj);
            template <typename R>
            T& operator=(I const Mat<R>& obj);
            virtual ~Mat();
            T& at(I initializer_list<int> pos);
            T* ptr(I initializer_list<int> pos);
            int reset(I initializer_list<int> shape, I const T val=0);
            int reset(I const int* shape, I const int dims, I const T val=0);
            void init();
            void deinit();
            static void show(I Mat<T>& mat, I const string winname="");
            static void close();
            static void close(I const string winname);
            static void waitkey(I const int delay=0);

            T*  _data;
            int _shape[64];
            int _steps[64];
            int _dims;
            int _len;
    };

    template <typename U, typename V, typename T>
    Mat<T> convolve(I Mat<U>& mat, I Mat<V>& ker, I int* step);
    template <typename U, typename V, typename T>
    void convolve(I Mat<U>& mat, I Mat<V>& ker, I int* step, O Mat<T>& con);
}

#endif