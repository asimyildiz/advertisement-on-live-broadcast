#include "CommandParser.h"

/**
 * constructor of CommandParser class
 * parse arguments and populate __argumnets vector
 *
 * @param argc total number of arguments passed to the application
 * @param argv argument list 
 */
CommandParser::CommandParser(int &argc, char **argv) {
	for (int i = 1; i < argc; ++i) {
		this->_arguments.push_back(std::string(argv[i]));
	}
}

/**
 * find a command option from arguments list
 * searches inside arguments vector with find method for the command and return next element
 *
 * @param option string value to search inside commands
 * @return command value found
 */
std::string CommandParser::getCommandByOption(const std::string &option) const {
	std::vector<std::string>::const_iterator itr;
	itr = std::find(this->_arguments.begin(), this->_arguments.end(), option);
	if (itr != this->_arguments.end() && ++itr != this->_arguments.end()) {
		return *itr;
	}

	return std::string("");
}

/**
 * check if a command exists inside argumet list
 * searches inside arguments vector with find method and return true if it exists
 *
 * @param option string value to search inside commands
 * @return true if command exists inside arguments
 */
bool CommandParser::isCommandExists(const std::string &option) const {
	return (std::find(this->_arguments.begin(), this->_arguments.end(), option) != this->_arguments.end());
}