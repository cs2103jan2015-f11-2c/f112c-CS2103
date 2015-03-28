#pragma once

#ifndef PARSEREXCEPTIONS_H
#define PARSEREXCEPTIONS_H

#include <iostream>
#include <string>

class ParserExceptions {
private:
	std::string exceptionCode;

public:
	static const std::string ERROR_MISSING_INPUT;
	static const std::string ERROR_NO_NAME;
	static const std::string ERROR_TOO_MANY_DATES;
	static const std::string ERROR_TOO_MANY_TIMES;
	static const std::string ERROR_MISSING_DAY;
	static const std::string ERROR_UNUSED_INTEGERS;
	static const std::string ERROR_MISSING_HOUR_MIN;
	static const std::string ERROR_TOO_MANY_DEL;
	static const std::string ERROR_MISSING_INDEX;
	static const std::string ERROR_INSUFFICIENT_INFO;
	static const std::string ERROR_UNKNOWN_COMMAND;
	static const std::string ERROR_UNKNOWN_DATE;
	static const std::string ERROR_UNKNOWN_HOUR;
	static const std::string ERROR_UNKNOWN_MINUTE;
	static const std::string ERROR_START_AFTER_END;
	
	ParserExceptions(std::string);

	std::string getExceptionCode();
};

#endif
