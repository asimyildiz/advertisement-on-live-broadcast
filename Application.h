// application
// @author : ASIM YILDIZ

#pragma once

#ifndef __APPLICATION__
#define __APPLICATION__

class Application;

#include "MetaDataFactory.h"
#include "SFMLPlayer.h"
#include "CommandParser.h"
#include <iostream>

/**
 * Application class to handle application logic
 *
 * start				- initial starting point of the application
 */
class Application
{
public:
	static void start(int argc, char *argv[]);
private:
	static const int MIN_NUMBER_OF_ARGUMENTS = 3;
};

#endif