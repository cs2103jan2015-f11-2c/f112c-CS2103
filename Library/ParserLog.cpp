#include "ParserLog.h"

const std::string ParserLog::textfilename = "ParserLog.txt";

ParserLog::ParserLog(){
}

void ParserLog::logParserEnterFunc(std::string functionName){
	std::ofstream writeFile;
	writeFile.open(textfilename,std::ios::app);
	writeFile << "Entered " << functionName << std::endl;
	writeFile.close();
}

void ParserLog::logParserError(std::string errorCode){
	std::ofstream writeFile;
	writeFile.open(textfilename,std::ios::app);
	writeFile << "Encountered error. Error code: " << errorCode << std::endl;
	writeFile.close();
}