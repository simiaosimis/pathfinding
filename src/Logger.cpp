#include "Logger.h"

Logger::Logger(){

}

Logger::~Logger(){
	this->os << std::endl;
	fprintf(stderr, "%s", this->os.str().c_str());
	fflush(stderr);
}

std::ostringstream& Logger::log(const LogLevel level_){
	this->os << levelToString(level_);
	return this->os;
}

std::string Logger::levelToString(const LogLevel level_){
	static const char* const buffer[] = {"[Info]:    ", "[Warning]: ", "[Error]:  ", "[Debug]:   "};
	return buffer[level_];
}
