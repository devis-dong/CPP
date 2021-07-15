/*** 
 * @Author: devis dong
 * @Date: 2021-07-13 12:53:46
 * @LastEditTime: 2021-07-14 20:37:02
 * @LastEditors: devis dong
 * @Description: 
 * @FilePath: \CPP\src\mat\dsmat.h
 */

#ifndef DSMAT_H
#define DSMAT_H

#include <vector>
#include <string>
#include <initializer_list>
#include "common/dsdefine.h"

using namespace std;

namespace ds
{
    template <typename T>
    class Mat
    {
        public:
            Mat(I initializer_list<int> shape);
            template <typename R>
            Mat(I initializer_list<int> shape, I const R* const pdata);
            template <typename R>
            Mat(I Mat<R> &mat);
            virtual ~Mat();
            int reset(I initializer_list<int> shape);
            vector<int> shape() const;
            int num_of_elements() const;
            int size_of_elements() const;
            int dims() const;
            // T& at(initializer_list<int> pos);
            template <typename ...Args>
            T& at(I Args&&... pos);
            // T* ptr(initializer_list<int> pos);
            template <typename ...Args>
            T* ptr(I Args&&... pos);
            int step(I const int i) const;
            template <typename ...Args>
            T& operator()(I Args&&... pos);
            T& operator[](I const int i);
        private:
            void member_init();
            void member_free();
        protected:
            T* m_pdata;
            int m_num_of_elements;
            int m_size_of_elements;
            vector<int> m_shape;
            vector<int> m_step;
    };
}


#endif