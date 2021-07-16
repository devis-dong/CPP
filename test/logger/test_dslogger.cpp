/*** 
 * @Author: devis dong
 * @Date: 2021-07-13 18:43:18
 * @LastEditTime: 2021-07-16 15:52:35
 * @LastEditors: devis dong
 * @Description: 
 * @FilePath: \C++\test\logger\test_dslogger.cpp
 */

#include "dslogger.h"
using namespace ds;

#ifndef logger_init
#define logger_init
    logger(Logger::target_all, Logger::level_all, "");
#endif

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
