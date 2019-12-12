#include "Application.h"

/**
 * initial starting point of the application
 * check total number of arguments passed to the application, it should be at least MIN_NUMBER_OF_ARGUMENTS
 * check if "-ts" option is passed to the application
 * get "-ts" option value which should point to the path of ts file which is going to be used for testing
 *
 * @param argc total number of arguments passed to the application
 * @param argv argument list
 */
void Application::start(int argc, char *argv[])
{
	if (argc < Application::MIN_NUMBER_OF_ARGUMENTS) {
		std::cout << "Usage is -ts <infile>\n";
		std::cin.get();
		exit(0);
	}

	CommandParser input(argc, argv);
	if (!input.isCommandExists("-ts")) {
		std::cout << "Please provide a ts file path to the application.\n";
		exit(0);
	}

	const std::string &tsFile = input.getCommandByOption("-ts");
	if (!tsFile.empty()) {
		setlocale(LC_ALL, "");

		// use fake meta data because there is not yet any service to fetch metadata from
		MetaDataFactory *metaDataFactory = new MetaDataFactory(1);
		AbstractMetaDataService *metaDataService = metaDataFactory->getMetaDataService();
		metaDataService->getMetaData("");

		SFMLPlayer *player = new SFMLPlayer();
		player->play(tsFile, metaDataService);
		player->close();
	}	
}