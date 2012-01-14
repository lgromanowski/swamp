#include "text_logger.h"
#include <ctime>
#include <cstdarg>

namespace swamp {

namespace logger {

struct TextDecorator : public Decorator {
	TextDecorator();
	virtual ~TextDecorator();

	const char* decorate(LogLevel level, const char* text);

	private:
		const char* addDateTime();
		const char* addLogLevel(LogLevel level);

	private:
		std::string m_text;
};

} /* namespace logger */

namespace logger {

//------------------------------------------------------------------------------
TextDecorator::TextDecorator()
	: m_text() {
}

//------------------------------------------------------------------------------
TextDecorator::~TextDecorator() {
}

//------------------------------------------------------------------------------
const char* TextDecorator::decorate(LogLevel level, const char* text) {
	m_text = addDateTime();
	m_text += addLogLevel(level);
	m_text += text;

	return m_text.c_str();
}

//------------------------------------------------------------------------------
const char* TextDecorator::addDateTime() {
	static char buf[64] = {0};
	time_t timestamp = time(nullptr);
	strftime(buf, sizeof(buf), "%Y-%m-%d %X ", localtime(&timestamp));
	return buf;
}

//------------------------------------------------------------------------------
const char* TextDecorator::addLogLevel(LogLevel level) {
	static char* s;

	switch (level) {
		//--------------------------------------------------------------------------
		case LogLevel::LOG_DEBUG: {
			s = (char*)"[DEBUG] ";
			break;
		}

		//--------------------------------------------------------------------------
		case LogLevel::LOG_INFO: {
			s = (char*)"[INFO] ";
			break;
		}

		//--------------------------------------------------------------------------
		case LogLevel::LOG_WARNING: {
			s = (char*)"[WARNING] ";
			break;
		}

		//--------------------------------------------------------------------------
		case LogLevel::LOG_ERROR: {
			s = (char*)"[ERROR] ";
			break;
		}

		//--------------------------------------------------------------------------
		case LogLevel::LOG_FATAL: {
			s = (char*)"[FATAL] ";
			break;
		}

		//--------------------------------------------------------------------------
		default: {
			s = (char*)" ";
			break;
		}
	}

	return s;
}

} /* namespace logger */

//------------------------------------------------------------------------------
TextLogger::TextLogger()
	: m_decorator(new logger::TextDecorator)
	, m_stream() {
}
/*
//------------------------------------------------------------------------------
TextLogger::TextLogger(logger::Decorator* decorator)
	: m_decorator(decorator)
	, m_stream() {
}
*/
//------------------------------------------------------------------------------
TextLogger::~TextLogger() {
	m_stream.flush();
	m_stream.close();

	delete m_decorator;
}

//------------------------------------------------------------------------------
int TextLogger::open(const char* path) {
	if (path != nullptr) {
		m_stream.open(path, std::ios::app | std::ios::out);
	}

	return m_stream.is_open() ? 0 : -1;
}

//------------------------------------------------------------------------------
int TextLogger::close() {
	m_stream.close();
	return 0;
}

//------------------------------------------------------------------------------
int TextLogger::flush() {
	int result = -1;
	return result;
}

//------------------------------------------------------------------------------
int TextLogger::write(LogLevel level, const char* text, ...) {
	int result = -1;
	if (m_decorator != nullptr) {
		char buffer[1024];
		va_list args;
		va_start(args, text);
		vsnprintf(buffer, sizeof(buffer), text, args);
		va_end(args);

		m_stream << m_decorator->decorate(level, buffer) << std::endl;
		result = 0;
	}
	return result;
}

} /* namespace TextLogger */

