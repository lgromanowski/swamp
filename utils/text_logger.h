#ifndef SWAMP_TEXT_LOGGER_H
#define SWAMP_TEXT_LOGGER_H

#include "logger.h"

#include <string>
#include <fstream>

namespace swamp {

struct TextLogger : public Logger<TextLogger> {
	int open(const char* path);
	int close();
	int flush();
	int write(LogLevel level, const char* text, ...);

	// This class is not copyable
	TextLogger(const TextLogger&) = delete;
	TextLogger& operator=(const TextLogger&) = delete;

	protected:
		friend class Singleton<TextLogger>;

		TextLogger();
		virtual ~TextLogger();

	private:
		logger::Decorator* m_decorator;
		std::ofstream m_stream;
};

} /* namespace TextLogger */

#endif // SWAMP_TEXT_LOGGER_H
