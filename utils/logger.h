#ifndef SWAMP_LOGGER_H
#define SWAMP_LOGGER_H

#include "utils/singleton.h"

namespace swamp {

enum class LogLevel : unsigned int {
	LOG_DEBUG,
	LOG_INFO,
	LOG_WARNING,
	LOG_ERROR,
	LOG_FATAL
};

template <
	class T
>
struct Logger : public Singleton<T> {
	virtual int open(const char* path) = 0;
	virtual int close() = 0;
	virtual int flush() = 0;
	virtual int write(LogLevel level, const char* text, ...) = 0;

	// This class is not copyable
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;

	protected:
		Logger(){}
		virtual ~Logger(){}
};

namespace logger {

struct Decorator {
	virtual ~Decorator() {}
	virtual const char* decorate(LogLevel level, const char* text) = 0;
};

} /* namespace logger */
} /* namespace swamp */

#endif /* SWAMP_LOGGER_H */
