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

	void logParserEnterFunc(std::string);
	void logParserError(std::string);
};

#endif