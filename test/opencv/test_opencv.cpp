/*** 
 * @Author: devis dong
 * @Date: 2021-07-16 14:32:00
 * @LastEditTime: 2021-07-16 21:43:50
 * @LastEditors: devis dong
 * @Description: 
 * @FilePath: \C++\test\opencv\test_dsimage.cpp
 */

#include <iostream>
#include <string>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;


int main()
{
    cout<<"running..."<<endl;
    string image_path = "E:/Coding/C++/bin/imgs/lenna.jpg";
    Mat img = imread(image_path, IMREAD_COLOR);
    if(img.empty())
    {
        std::cout << "Could not read the image: " << image_path << std::endl;
        return 1;
    }
    imshow("display window", img);
    waitKey(0);
    cout<<"...done."<<endl;
    system("pause");
    return 0;
}
