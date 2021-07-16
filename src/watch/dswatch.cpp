/*** 
 * @Author: devis dong
 * @Date: 2021-07-13 15:52:34
 * @LastEditTime: 2021-07-16 15:59:57
 * @LastEditors: devis dong
 * @Description: 
 * @FilePath: \C++\src\watch\dswatch.cpp
 */

#include <time.h>
#include <chrono>
#include "dswatch.h"

namespace ds
{
    Watch::Watch() {}
    Watch::~Watch() {}
    string Watch::get_datetime(I const bool format)
    {
        time_t t = time(0); 
        char tmp[32]={0};
        if(format)
        {
            strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&t));
        }
        else
        {
            strftime(tmp, sizeof(tmp), "%Y%m%d%H%M%S", localtime(&t));
        }
        return tmp;
    }

    string Watch::get_date(I const bool format)
    {
        time_t t = time(0); 
        char tmp[32]={0};
        if(format)
        {
            strftime(tmp, sizeof(tmp), "%Y-%m-%d", localtime(&t));
        }
        else
        {
            strftime(tmp, sizeof(tmp), "%Y%m%d", localtime(&t));
        }
        return tmp;
    }

    string Watch::get_time(I const bool format)
    {
        time_t t = time(0); 
        char tmp[32]={0};
        if(format)
        {
            strftime(tmp, sizeof(tmp), "%H:%M:%S", localtime(&t));
        }
        else
        {
            strftime(tmp, sizeof(tmp), "%H%M%S", localtime(&t));
        }
        return tmp;
    }

    void Watch::start_clock()
    {
        _start = _stop = high_resolution_clock::now();
    }

    void Watch::stop_clock()
    {
        _stop = high_resolution_clock::now();
    }

    double Watch::get_duration()
    {
        return double(duration_cast<microseconds>(_stop - _start).count()) * microseconds::period::num / microseconds::period::den;
    }
} // namespace ds

