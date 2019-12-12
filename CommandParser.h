// utils
// @author : ASIM YILDIZ

#pragma once

#ifndef __COMMANDPARSER__
#define __COMMANDPARSER__

class CommandParser;

#include <string>
#include <vector>

/**
 * Implementation of command parser utility from console
 *
 * getCommandByOption	- find a command option from arguments list
 * isCommandExists		- check if a command exists inside argumet list
 */
class CommandParser
{
public:
	CommandParser(int &argc, char **argv);
	std::string getCommandByOption(const std::string &option) const;
	bool isCommandExists(const std::string &option) const;
private:
	std::vector <std::string> _arguments;
};

#endif