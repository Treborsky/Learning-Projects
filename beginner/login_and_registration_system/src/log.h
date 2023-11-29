#ifndef TREBORSKY_LOG_H_
#define TREBORSKY_LOG_H_

#include <iostream>
#define LOG_INTERNAL(level, module, stream_fmt) do { std::cout << std::setw(6) << std::left << #level << \
                                                           ":" << std::setw(6) << std::left << #module << \
                                                           ":" << std::setw(5) << std::left << __LINE__ << \
                                                           ":" << std::setw(50) << std::left << __PRETTY_FUNCTION__ << \
                                                           " : {msg:\"" << stream_fmt << "\"}" << std::endl; } while(0)
#define LOG(level, module, stream_fmt) LOG_INTERNAL(level, module, stream_fmt)
#define LOG_DEBUG(module, stream_fmt) LOG(DEBUG, module, stream_fmt)
#define LOG_INFO(module, stream_fmt) LOG(INFO, module, stream_fmt)

#endif // TREBORSKY_LOG_H_