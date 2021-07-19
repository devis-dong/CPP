/*** 
 * @Author: devis dong
 * @Date: 2021-07-19 14:46:33
 * @LastEditTime: 2021-07-19 19:47:04
 * @LastEditors: devis dong
 * @Description: 
 * @FilePath: \C++\src\dsvec\dsvec.h
 */

#ifndef DSVEC_H
#define DSVEC_H

#include <stdio.h>
#include <initializer_list>
#include "dsdefine.h"
using namespace std;

namespace ds
{
    template<typename T>
    class Vec
    {
    public:
        ~Vec();
        Vec(/* args */);
        Vec(I const int dims, I const T val=0);
        // Vec(I const int dims, I const T* data=nullptr);
        Vec(I initializer_list<T> shape);
        Vec(I const Vec<T>& obj);
        int size();
        T& operator=(I const Vec<T>& obj);
        T& operator[](I const int idx);
        Vec<T> operator++();
        Vec<T> operator++(int);
        Vec<T> operator--();
        Vec<T> operator--(int);
        template<typename R>
        friend Vec<R> operator+(I const Vec<R>& vec0, I const Vec<R>& vec1);
        template<typename R>
        friend Vec<R> operator-(I const Vec<R>& vec0, I const Vec<R>& vec1);
        template<typename R>
        friend Vec<R> operator*(I const Vec<R>& vec0, I const Vec<R>& vec1);
        template<typename R>
        friend Vec<R> operator/(I const Vec<R>& vec0, I const Vec<R>& vec1);

        void init();
        void deinit();


        T* _data;
        int _dims;

    };

    template<typename T>
    Vec<T> operator+(I const Vec<T>& vec0, I const Vec<T>& vec1);
    template<typename T>
    Vec<T> operator-(I const Vec<T>& vec0, I const Vec<T>& vec1);
    template<typename T>
    Vec<T> operator*(I const Vec<T>& vec0, I const Vec<T>& vec1);
    template<typename T>
    Vec<T> operator/(I const Vec<T>& vec0, I const Vec<T>& vec1);
    int coord2idx(I const Vec<int>& vec0, I const Vec<int>& shape);
    Vec<int> idx2coord(I int idx, I const Vec<int>& shape);
    template<typename T>
    bool move2next(I O Vec<T>& p, I Vec<T>& start, I Vec<T>& step, I Vec<T>& end);
    template<typename T>
    void printvec(I Vec<T>& vec0);
}

#endif

