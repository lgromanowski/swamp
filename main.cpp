#include "swamp.h"
#include "utils/text_logger.h"

int main(/*int argc, char** argv*/) {
	swamp::TextLogger::getInstance()->open("swamp_server.log");

	swamp::Swamp s;
  return s.run();
}
