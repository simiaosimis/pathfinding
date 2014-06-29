#include "Level.h"
#include "Logger.h"

Level::Level() :
	width(0),
	height(0),
	player(nullptr),
	camera(nullptr),
	tileMap(nullptr),
	quadTree(nullptr),
	background(nullptr)
{
	// Only serves as the initializer for the derived classes.
}

Level::~Level(){
	this->player = nullptr;

	if(this->camera != nullptr){
		delete this->camera;
		this->camera = nullptr;
	}

	if(this->playerHud != nullptr){
		delete this->playerHud;
		this->playerHud = nullptr;
	}

	if(this->tileMap != nullptr){
		delete this->tileMap;
		this->tileMap = nullptr;
	}

	if(this->quadTree != nullptr){
		delete this->quadTree;
		this->quadTree = nullptr;
	}
}

unsigned int Level::getWidth(){
	return this->width;
}

unsigned int Level::getHeight(){
	return this->height;
}

void Level::setPlayer(Player* const player_){
	this->player = player_;

	if(this->player != nullptr){
		this->player->setLevelWH(this->width, this->height);
		addEntity(this->player);
	}
	else{
		Log(WARN) << "Setting a null player for the level!";
	}
	
}

void Level::setCamera(Camera* const camera_){
	this->camera = camera_;

	if(this->camera != nullptr){
		if(this->player != nullptr){
			this->camera->setLevelWH(this->width, this->height);
		}
		else{
			Log(WARN) << "Shouldn't set the camera before the player, in Level!";
		}
	}
	else{
		Log(WARN) << "Setting a null camera!";
	}

}

void Level::clearEnemies(){

}
