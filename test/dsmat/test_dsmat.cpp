/*** 
 * @Author: devis dong
 * @Date: 2021-07-16 14:32:00
 * @LastEditTime: 2021-07-17 18:03:29
 * @LastEditors: devis dong
 * @Description: 
 * @FilePath: \C++\test\dsmat\test_dsmat.cpp
 */

#include <iostream>
#include "dsmat.h"
#include "dswatch.h"

using namespace ds;

int main()
{
    printf("running...");
    Watch mywatch;
    int h = 1000, w = 1000, c = 1;
    Mat<int> mat({h, w, c});
    for(int i = 0; i < mat.get_elements_num(); mat[i++] = i);
    mywatch.start_clock();
    // for(int i = 0; i < mat.get_elements_num(); ++i) mat.at(i);
    for(int i = 0; i < h; ++i)
    {
        for(int j = 0; j < w; ++j)
        {
            for(int k = 0; k < c; ++k)
            {
                // mat.at({i, j, k});
                mat.at(i*w*c + j*c + k);
                // cout<<mat.at({i, j, k});
            }
            // cout<<" ";
        }
        // cout<<endl;
    }
    mywatch.stop_clock();
    cout<<"time cost: "<<mywatch.get_duration()<<"s"<<endl;
    printf("...done.");
    system("pause");
    return 0;
}
