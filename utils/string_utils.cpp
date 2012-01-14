#include "string_utils.h"

namespace swamp {

static const char* const whitespaces = " \t\f\v\n\r";

std::string& trim_whitespaces(std::string& text) {
	std::string::size_type found = text.find_last_not_of(whitespaces);
	if (found != std::string::npos) {
		text.erase(found + 1);
	}
	else {
		text.clear();
	}

	return text;
}

}

