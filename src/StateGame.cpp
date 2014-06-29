#include "StateGame.h"

StateGame::~StateGame(){
	// Should be called in each state unload.
	cleanEntities();
}

void StateGame::addEntity(Entity* const entity){
	this->entities.push_back(entity);
}

void StateGame::cleanEntities(){
	for(auto entity : this->entities){
		delete entity;
		entity = nullptr;
	}

	this->entities.clear();
}
