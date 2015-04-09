#include "ParserExceptions.h"

const std::string ParserExceptions::ERROR_MISSING_INPUT = "PS000";
const std::string ParserExceptions::ERROR_NO_NAME = "PS001";
const std::string ParserExceptions::ERROR_TOO_MANY_DATES = "PS002";
const std::string ParserExceptions::ERROR_TOO_MANY_TIMES = "PS003";
const std::string ParserExceptions::ERROR_MISSING_DAY = "PS004";
const std::string ParserExceptions::ERROR_UNUSED_INFORMATION = "PS005";
const std::string ParserExceptions::ERROR_MISSING_HOUR_MIN = "PS006";
const std::string ParserExceptions::ERROR_TOO_MANY_DEL = "PS007";
const std::string ParserExceptions::ERROR_MISSING_INDEX = "PS008";
const std::string ParserExceptions::ERROR_INSUFFICIENT_INFO = "PS009";
const std::string ParserExceptions::ERROR_UNKNOWN_COMMAND = "PS010";
const std::string ParserExceptions::ERROR_UNKNOWN_DATE = "PS011";
const std::string ParserExceptions::ERROR_UNKNOWN_HOUR = "PS012";
const std::string ParserExceptions::ERROR_UNKNOWN_MINUTE = "PS013";
const std::string ParserExceptions::ERROR_START_AFTER_END = "PS014";
const std::string ParserExceptions::ERROR_NO_SHOW = "PS015";
const std::string ParserExceptions::ERROR_DUE_TOO_MANY_DATES = "PS016";
const std::string ParserExceptions::ERROR_DUE_TOO_MANY_TIMES = "PS017";
const std::string ParserExceptions::ERROR_INVALID_YEAR = "PS018";
const std::string ParserExceptions::ERROR_NO_EDIT_TO_DEADLINE = "PS019";

ParserExceptions::ParserExceptions(std::string errorCode) {
	exceptionCode = errorCode;
}

std::string ParserExceptions::getExceptionCode() {
	return exceptionCode;
}


