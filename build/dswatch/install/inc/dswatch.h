/*** 
 * @Author: devis dong
 * @Date: 2021-07-13 15:52:28
 * @LastEditTime: 2021-07-16 14:29:42
 * @LastEditors: devis dong
 * @Description: 
 * @FilePath: \C++\src\watch\dswatch.h
 */
#ifndef DSTIME_H
#define DSTIME_H


#include <string>
#include <chrono>
#include "dsdefine.h"

using namespace std;
using namespace chrono;

namespace ds
{
    class Watch
    {
        public:
            Watch();
            ~Watch();
            static string get_datetime(I const bool format=true);
            static string get_date(I const bool format=true);
            static string get_time(I const bool format=true);
            void start_clock();
            void stop_clock();
            double get_duration();
        private:
            time_point<high_resolution_clock> _start;
            time_point<high_resolution_clock> _stop;
    };
}

#endif
