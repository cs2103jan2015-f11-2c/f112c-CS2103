#include "ParserLog.h"

const std::string ParserLog::textfilename = "ParserLog.txt";

ParserLog::ParserLog() {
}

void ParserLog::logParserStart(std::string input) {
	std::ofstream writeFile;
	writeFile.open(textfilename,std::ios::app);
	writeFile << "Initialised parsing of input \"" << input << "\"" << std::endl;
	writeFile.close();
}

void ParserLog::logParserEnterFunc(std::string functionName) {
	std::ofstream writeFile;
	writeFile.open(textfilename,std::ios::app);
	writeFile << "Entered " << functionName << std::endl;
	writeFile.close();
}

void ParserLog::logParserIdentified(std::string functionName) {
	std::ofstream writeFile;
	writeFile.open(textfilename,std::ios::app);
	writeFile << functionName << std::endl;
	writeFile.close();
}

void ParserLog::logParserError(std::string errorCode) {
	std::ofstream writeFile;
	writeFile.open(textfilename,std::ios::app);
	writeFile << "Encountered error. Error code: " << errorCode << std::endl;
	writeFile.close();
}

void ParserLog::logParserSuccess(std::string input) {
	std::ofstream writeFile;
	writeFile.open(textfilename,std::ios::app);
	writeFile << "Successfully parsed input \"" << input << "\"" << std::endl << std::endl;
	writeFile.close();
}

void ParserLog::logParserFailure(std::string input) {
	std::ofstream writeFile;
	writeFile.open(textfilename,std::ios::app);
	writeFile << "Failed to parse input \"" << input << "\"" << std::endl << std::endl;
	writeFile.close();
}