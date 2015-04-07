#pragma once

#ifndef PARSERLOG_H
#define PARSERLOG_H

#include <iostream>
#include <fstream>
#include <string>

class ParserLog {
private:
	static const std::string textfilename;

public:
	ParserLog();

	void logParserStart(std::string);
	void logParserEnterFunc(std::string);
	void logParserIdentified(std::string);
	void logParserError(std::string);
	void logParserSuccess(std::string);
	void logParserFailure(std::string);
};

#endif