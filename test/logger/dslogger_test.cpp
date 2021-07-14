/*** 
 * @Author: devis dong
 * @Date: 2021-07-13 18:43:18
 * @LastEditTime: 2021-07-14 18:38:38
 * @LastEditors: devis dong
 * @Description: 
 * @FilePath: \C++\test\dslogger_test.cpp
 */

#include "logger/dslogger.h"
using namespace ds;

Logger logger(LOGTARGET, LOGLEVEL);
#define log_debug(text) logger.log_debug(text, __FILE__, __LINE__)
#define log_info(text) logger.log_info(text, __FILE__, __LINE__)
#define log_warnning(text) logger.log_warning(text, __FILE__, __LINE__)
#define log_error(text) logger.log_error(text, __FILE__, __LINE__)

int main()
{
    printf("running...\n");
    log_debug("What happend?");
    log_info("This is good.");
    log_warnning("Warning.");
    log_error("IO Error!");
    printf("...done.\n");
    system("pause");
    return 0;
}
