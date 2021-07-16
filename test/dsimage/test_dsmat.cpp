/*** 
 * @Author: devis dong
 * @Date: 2021-07-16 20:08:25
 * @LastEditTime: 2021-07-16 20:08:32
 * @LastEditors: devis dong
 * @Description: 
 * @FilePath: \C++\test\dsimage\test_dsmat.cpp
 */


#include <iostream>
#include "dsimage.h"

using namespace ds;

int main()
{
    printf("running...");
    
    int h = 10, w = 10, c = 3;
    Image<int> img(h, w, c);
    for(int i = 0; i < img.get_elements_num(); img[i++] = i);
    for(int i = 0; i < h; ++i)
    {
        for(int j = 0; j < w; ++j)
        {
            for(int k = 0; k < c; ++k)
            {
                cout<<img.at(i, j, k);
            }
            cout<<" ";
        }
        cout<<endl;
    }
    printf("...done.");
    system("pause");
    return 0;
}
