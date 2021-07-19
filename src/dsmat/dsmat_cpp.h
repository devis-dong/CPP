/*** 
 * @Author: devis dong
 * @Date: 2021-07-19 00:37:38
 * @LastEditTime: 2021-07-19 19:48:55
 * @LastEditors: devis dong
 * @Description: 
 * @FilePath: \C++\src\dsmat\dsmat.h
 */

#ifndef DSMAT_H
#define DSMAT_H

#include <string>
#include "dsdefine.h"
#include "dsvec.h"
using namespace std;


namespace ds
{
    template <typename T>
    class Mat
    {
        public:
            Mat();
            Mat(I initializer_list<T> shape, I const T val=0);
            Mat(I const string& filepath, I const int flag=1);
            Mat(I Vec<int>& shape, I const T val=0);
            // template <typename R>
            // Mat(I Vec<int> shape, I const R* data);
            Mat(I const Mat<T> &obj);
            T& operator=(I const Mat<T>& obj);
            virtual ~Mat();
            T& at(I Vec<int> pos);
            T* ptr(I Vec<int> pos);
            int reset(I Vec<int> shape, I const T val=0);
            void init();
            void deinit();
            static void show(I Mat<T>& mat, I const string winname="");
            static void close();
            static void close(I const string winname);
            static void waitkey(I const int delay=0);

            T*  _data;
            Vec<int>* _shape;
            Vec<int>* _steps;
            int _dims;
            int _len;
    };

    template <typename U, typename V, typename T>
    Mat<T> convolve(I Mat<U>& mat, I Mat<V>& ker, I Vec<int>& step);
    template <typename U, typename V, typename T>
    void convolve(I Mat<U>& mat, I Mat<V>& ker,  I Vec<int>& step, O Mat<T>& con);
    template <typename T>
    Mat<T> sample(I Mat<T>& mat, I Vec<double> rate);
}

#endif