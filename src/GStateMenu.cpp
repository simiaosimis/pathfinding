#include "GStateMenu.h"
#include "Game.h"
#include "Logger.h"

#include <string>

GStateMenu::GStateMenu() :
	menuImage(nullptr),
	passedTime(0.0),
	currentSelection(Selection::NEWGAME)
{

}

GStateMenu::~GStateMenu(){

}

void GStateMenu::load(){
	Log(DEBUG) << "Loading menu...";

	const std::string pathTitleScreen = "res/images/menu_titleScreen.png";

    this->menuImage = Game::instance().getResources().get(pathTitleScreen);

    Game::instance().getFade().fadeOut(0, 0.002);
}

void GStateMenu::unload(){
	Log(DEBUG) << "\tUnloading menu...";
	cleanEntities();
}

void GStateMenu::update(const double dt_){
	this->passedTime += dt_;

	std::array<bool, GameKeys::MAX> keyStates = Game::instance().getInput();
	if(keyStates[GameKeys::ESCAPE] == true){
		Game::instance().stop();
	}
	if(currentSelection == Selection::NEWGAME && keyStates[GameKeys::SPACE] == true){
		Game::instance().setState(Game::GStates::LEVEL_ONE);
	}
}

void GStateMenu::render(){
	if(this->menuImage != nullptr){
		this->menuImage->render(0, 0, nullptr, true);
	}
	else{
		Log(WARN) << "No image set to display on the menu!";
	}
}
