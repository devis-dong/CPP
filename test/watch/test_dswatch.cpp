/*** 
 * @Author: devis dong
 * @Date: 2021-07-15 19:18:44
 * @LastEditTime: 2021-07-16 16:01:58
 * @LastEditors: devis dong
 * @Description: 
 * @FilePath: \C++\test\watch\test_dswatch.cpp
 */
#include <thread>
#include "dswatch.h"

using namespace std;
using namespace ds;

int main()
{
    Watch watch = Watch();
    printf("running...\n");
    printf("%s\n", Watch::get_time().c_str());
    watch.start_clock();
    this_thread::sleep_for(std::chrono::seconds(1)); //休眠1秒
    // this_thread::sleep_for(std::chrono::milliseconds(10)); //休眠10毫秒
    watch.stop_clock();
    printf("%s\n", Watch::get_time().c_str());
    printf("time cost: %f", watch.get_duration());
    printf("...done.\n");
    system("pause");
    return 0;
}

