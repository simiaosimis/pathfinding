#include "Game.h"
#include "Logger.h"
#include "Configuration.h"

int main(int argc, char** argv){

	// Unused.
	((void)argc);
	((void)argv);

	Log(DEBUG) << "Starting Dauphine...";

	Configuration::initialize();

	bool systemsInitialized = SDLWrapper::initialize();

	if(systemsInitialized){
		Game::instance().runGame();
		//delete &Game::instance();
	}
	else{
		Log(ERROR) << "System were not initialized.";
	}

	SDLWrapper::close();

	Log(DEBUG) << "Exiting Dauphine...";
	return 0;
}
