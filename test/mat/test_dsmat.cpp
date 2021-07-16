/*** 
 * @Author: devis dong
 * @Date: 2021-07-16 14:32:00
 * @LastEditTime: 2021-07-16 17:19:28
 * @LastEditors: devis dong
 * @Description: 
 * @FilePath: \C++\test\mat\test_dsmat.cpp
 */

#include <iostream>
#include "dsmat.h"

using namespace ds;

int main()
{
    printf("running...");
    int h = 10, w = 10, c = 3;
    Mat<int> mat({h, w, c});
    for(int i = 0; i < mat.get_elements_num(); mat[i++] = i);
    for(int i = 0; i < h; ++i)
    {
        for(int j = 0; j < w; ++j)
        {
            for(int k = 0; k < c; ++k)
            {
                cout<<mat.at({i, j, k});
            }
            cout<<" ";
        }
        cout<<endl;
    }
    printf("...done.");
    system("pause");
    return 0;
}
