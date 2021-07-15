/*** 
 * @Author: devis dong
 * @Date: 2021-07-13 18:43:18
 * @LastEditTime: 2021-07-15 21:38:18
 * @LastEditors: devis dong
 * @Description: 
 * @FilePath: \C++\test\logger\test_dslogger.cpp
 */

#include "logger/dslogger.h"
using namespace ds;


logger(Logger::target_all, Logger::level_all, "");

int main()
{
    printf("running...\n");
    logdebug("what happened? %d", 0);
    loginfo("This is good. %d", 1);
    logwarnning("Warning. %d", 2);
    logerror("IO Error! %d", 3);
    printf("...done.\n");
    system("pause");
    return 0;
}
