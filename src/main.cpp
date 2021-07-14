/*** 
 * @Author: devis dong
 * @Date: 2021-07-12 15:57:14
 * @LastEditTime: 2021-07-12 21:06:06
 * @LastEditors: devis dong
 * @Description: 
 * @FilePath: \Tools\src\main.cpp
 */

#include<stdio.h>
#include "opencv.hpp"

using namespace std;
using namespace cv;

int main()
{
    printf("running...\n");
    
    Mat img = imread("./imgs/lenna.jpg");
    imshow("image", img);
    waitKey(0);

    printf("done.\n");
    return 0;
}
