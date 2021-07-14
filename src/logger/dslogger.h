/*** 
 * @Author: devis dong
 * @Date: 2021-07-13 15:30:14
 * @LastEditTime: 2021-07-14 20:16:27
 * @LastEditors: devis dong
 * @Description: 
 * @FilePath: \C++\src\Logger\dslogger.h
 */

#ifndef DSLOGGER_H
#define DSLOGGER_H


#include<string>
#include<iostream>
#include <stdio.h>
#include "common/dsdefine.h"

using namespace std;

namespace ds
{
    class Logger
    {
        public:
            enum LogLevel{level_debug = 0b00000001, level_info = 0b00000010, level_warning = 0b00000100, level_error = 0b00001000, level_all=0b11111111};
            enum LogTarget{target_file = 0b00000001, target_terminal = 0b00000010, target_all = 0b11111111};
            Logger(I const int& target=target_terminal, I const int& level=level_debug, I const string& path="");
            ~Logger();
            void log_debug(I const string& text, I const string& file=__FILE__, I const int& line=__LINE__);
            void log_info(I const string& text, I const string& file=__FILE__, I const int& line=__LINE__);
            void log_warning(I const string& text, I const string& file=__FILE__, I const int& line=__LINE__);
            void log_error(I const string& text, I const string& file=__FILE__, I const int& line=__LINE__);
        private:
            void init(I const int& target=target_terminal, I const int& level=level_debug, I const string& path="");
            void deinit();
            void log(I const string& text, I const LogLevel level, I const string& file=__FILE__, I const int& line=__LINE__);            // 输出行为
            string target2str(I const int& level);
            string level2str(I const int& level);
        private:
            void*   _file_handle;           // 将日志输出到文件的流对象
            int     _target;                // 日志输出目标
            int     _level;                 // 日志等级
            string  _path;                  // 日志文件路径
    };
}

#endif
