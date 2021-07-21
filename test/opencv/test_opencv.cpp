/*** 
 * @Author: devis dong
 * @Date: 2021-07-16 14:32:00
 * @LastEditTime: 2021-07-21 23:03:53
 * @LastEditors: devis dong
 * @Description: 
 * @FilePath: \C++\test\opencv\test_opencv.cpp
 */

#include <iostream>
#include <string>
#include "opencv2/opencv.hpp"

#include <math.h>

using namespace std;
using namespace cv;




int main()
{
    cout<<"running..."<<endl;
    // string image_path = "E:/Coding/C++/bin/imgs/lenna.jpg";
    // Mat img = imread(image_path, IMREAD_COLOR);
    // if(img.empty())
    // {
    //     std::cout << "Could not read the image: " << image_path << std::endl;
    //     return 1;
    // }
    // imshow("display window", img);
    // waitKey(0);
    double pi = 3.14159265358979323846;
    double dpr = 180/pi;
    cout<<(atan2(1, 1))*dpr<<" "<<(atan2(1, -1))*dpr<<" "<<(atan2(-1, -1))*dpr<<" "<<(atan2(-1, 1))*dpr<<endl;
    cout<<(atan2(0, -1))*dpr<<endl;

    cout<<"...done."<<endl;
    system("pause");
    return 0;
}
