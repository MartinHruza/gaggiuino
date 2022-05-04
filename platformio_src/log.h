#ifndef __LOG_H_
#define __LOG_H_

#define LOG_E(msg) do { log_e(__FILE__, __LINE__, msg); } while (0)
void log_e(const char * file, const int line, const char *msg);

#endif
