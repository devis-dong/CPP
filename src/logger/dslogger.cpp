/*** 
 * @Author: devis dong
 * @Date: 2021-07-13 15:30:20
 * @LastEditTime: 2021-07-15 14:03:27
 * @LastEditors: devis dong
 * @Description: 
 * @FilePath: \C++\src\Logger\dslogger.cpp
 */

#include <stdarg.h>
#include "common/dsdefine.h"
#include "logger/dslogger.h"
#include "time/dstime.h"

using namespace std;

#define format_str(text)    { va_list args;\
        va_start(args, fmt);\
        vsprintf(text, fmt, args);\
        va_end(args); }

namespace ds
{
    void Logger::init(I const int& target, I const int& level, I const string& path)
    {
        _target = target;
        _level = level;
        _path = path;
        _file_handle = nullptr;
        if(_path.empty() || "" == _path) _path = string("logs/") + get_date() +".log";
        string msg = get_format_date() + " ****WELCOME**** Target: " + target2str(_target) + " Level: " + level2str(_level) + "Path: " + _path + "\n";
        if(target & target_file)
        {
            _file_handle = fopen(_path.c_str(), "a");
            fwrite(msg.c_str(), msg.size(), 1, (FILE*)_file_handle);
            fflush((FILE*)_file_handle);
        }
        if(target & target_terminal)
        {
            printf("%s", msg.c_str());
        }
    }

    void Logger::deinit()
    {
        if(nullptr != _file_handle)
        {
            fclose((FILE*)_file_handle);
            _file_handle = nullptr;
        }
    }

    Logger::Logger(I const int& target, I const int& level, I const string& path)
    {
        init(target, level, path);
    }

    Logger::~Logger()
    {
        deinit();
    }

    string Logger::target2str(I const int& level)
    {
        string target_str;
        switch (level)
        {
            case target_terminal:
                target_str = "[TERMINAL]    ";
                break;
            case target_file:
                target_str = "[FILE]        ";
                break;
            case target_all:
                target_str = "[ALL]         ";
                break;
            default:
                target_str = "[UNKNOWN]     ";
                break;
        }
        return target_str;
    }

    string Logger::level2str(I const int& level)
    {
        string level_str;
        switch (level)
        {
            case level_debug:
                level_str = "[DEBUG]        ";
                break;
            case level_info:
                level_str = "[INFO]         ";
                break;
            case level_warning:
                level_str = "[WARNING]      ";
                break;
            case level_error:
                level_str = "[ERROR]        ";
                break;
            case level_all:
                level_str = "[ALL]          ";
                break;
            default:
                level_str = "[UNKNOWN]      ";
                break;
        }
        return level_str;
    }

    void Logger::log(I const LogLevel& level, I const string& file, I const int& line, I const string& text)
    {
        string msg = get_format_date() + " " + level2str(level) + " " + file + "(" + to_string(line) + ")" + ": " + text + "\n";
        if((_level & level) && (_target & target_terminal))
        {
            printf("%s", msg.c_str());
        }
        if(_target & target_file)
        {
            fwrite(msg.c_str(), msg.size(), 1, (FILE*)_file_handle);
            fflush((FILE*)_file_handle);
        }
    }

    void Logger::log_debug(I const string& file, I const int& line, I const char* fmt, ...)
    {
        char text[256]; format_str(text);
        this->log(level_debug, file, line, text);
    }

    void Logger::log_info(I const string& file, I const int& line, I const char* fmt, ...)
    {
        char text[256]; format_str(text);
        this->log(level_debug, file, line, text);
    }

    void Logger::log_warning(I const string& file, I const int& line, I const char* fmt, ...)
    {
        char text[256]; format_str(text);
        this->log(level_debug, file, line, text);
    }
    
    void Logger::log_error(I const string& file, I const int& line, I const char* fmt, ...)
    {
        char text[256]; format_str(text);
        this->log(level_debug, file, line, text);
    }
}
