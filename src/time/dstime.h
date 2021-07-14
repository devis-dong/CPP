/*** 
 * @Author: devis dong
 * @Date: 2021-07-13 15:52:28
 * @LastEditTime: 2021-07-14 20:05:55
 * @LastEditors: devis dong
 * @Description: 
 * @FilePath: \C++\src\Time\dstime.h
 */
#ifndef DSTIME_H
#define DSTIME_H

#include <time.h>
#include <string>

using namespace std;

namespace ds
{
    string get_format_date()
    {
        time_t t = time(0); 
        char tmp[32]={0};
        strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&t));
        return tmp;
    }

    string get_date()
    {
        time_t t = time(0); 
        char tmp[32]={0};
        strftime(tmp, sizeof(tmp), "%Y%m%d%H%M%S", localtime(&t));
        return tmp;
    }
}

#endif
