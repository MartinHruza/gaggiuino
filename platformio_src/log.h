#ifndef LOG_H
#define LOG_H

#define LOG_E(msg) do { log_e(__FILE__, __LINE__, msg); } while (0)
void log_e(const char * file, const int line, const char *msg);

#endif
