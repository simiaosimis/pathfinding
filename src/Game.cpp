#include "Game.h"
#include "FPSWrapper.h"
#include "Configuration.h"
#include <cassert>

#include "LevelOne.h"
#include "GStateMenu.h"

#include "Dijkstra.h"

#include "Logger.h"

#define ADD_STATE(stateEnum, stateClass) this->statesMap.emplace(stateEnum, new stateClass())

Game& Game::instance(){
	static Game* instance = new Game();
	return *instance;
}

Game::Game() :
	dijkstra(nullptr),
	window(nullptr),
	isRunning(false),
	inputHandler(new InputHandler()),
	resourceManager(new ResourceManager()),
	fadeScreen(nullptr),
	currentState(nullptr),
	statesMap()
{
	initializeStates();

	this->window = new Window(Configuration::getScreenWidth(),
		Configuration::getScreenHeight(), Configuration::getWindowTitle());

	assert(this->window != nullptr && "The window should not be null!");

	this->isRunning = true;
	FPSWrapper::initialize(this->fpsManager);

	this->dijkstra = new Dijkstra();
 
}

Game::~Game(){
	if(this->dijkstra != nullptr){
		delete this->dijkstra;
		this->dijkstra = nullptr;
	}

	if(this->currentState != nullptr){
		this->currentState->unload();
	}

	destroyStates();
	Log(DEBUG) << "\tStates unload...";
	
	if(this->inputHandler != nullptr){
		delete this->inputHandler;
	}
	Log(DEBUG) << "\tinput unload...";
	if(this->resourceManager != nullptr){
		delete this->resourceManager;
	}
	Log(DEBUG) << "\tresource unload...";
	if(this->window != nullptr){
		Log(DEBUG) << "\tentrou window...";	
		delete this->window;
		this->window = nullptr;
	}
	Log(DEBUG) << "\twindow unload...";
}

void Game::runGame(){
	this->fadeScreen = new FadeScreen();

	this->currentState = this->statesMap.at(GStates::MENU);
	this->currentState->load();

	// Get the first game time.
	double totalGameTime = 0.0;
	const double deltaTime = 1.0 / 60.0;
	double accumulatedTime = 0.0;

	// This is the main game loop.
	while(this->isRunning){

		const double frameTime = FPSWrapper::delay(this->fpsManager);
		accumulatedTime += frameTime;

		// Update.
		while(accumulatedTime >= deltaTime){
			this->inputHandler->handleInput();

			// Check for an exit signal from input.
			if(this->inputHandler->isQuitFlag() == true){
				stop();
				return;
			}

			this->currentState->update(deltaTime);
			this->fadeScreen->update(deltaTime);

			accumulatedTime -= deltaTime;
			totalGameTime += deltaTime;
		}

		// Render.
		window->clear();

		this->currentState->render();
		this->fadeScreen->render();

		window->render();
		
	}

}

void Game::setState(const GStates state_){
	/// @todo Implement the transition between states.
	this->currentState->unload();
	this->currentState = this->statesMap.at(state_);
	this->currentState->load();
}

void Game::initializeStates(){
	// Initialize all the states in Game here.

	// Emplace the states pointers onto the map.
	ADD_STATE(MENU, GStateMenu);
	ADD_STATE(LEVEL_ONE, LevelOne);

}

void Game::destroyStates(){
	std::map<GStates, StateGame*>::const_iterator it;
    for(it = this->statesMap.begin(); it != this->statesMap.end(); it++){

    }
}

std::array<bool, GameKeys::MAX> Game::getInput(){
	return this->inputHandler->getKeyStates();
}

int Game::getMouseX(){
	return this->inputHandler->mouseX;
}

int Game::getMouseY(){
	return this->inputHandler->mouseY;
}

ResourceManager& Game::getResources(){
	return (*(this->resourceManager));
}

void Game::stop(){
	this->isRunning = false;
}

void Game::clearKeyFromInput(const GameKeys key_){
	this->inputHandler->clearKey(key_);
}

FadeScreen& Game::getFade(){
	return (*(this->fadeScreen));
}
