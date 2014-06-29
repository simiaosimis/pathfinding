#include "PlayerHUD.h"
#include "Game.h"
#include "Logger.h"

PlayerHUD::PlayerHUD(Player* const player_):
	player(player_)
{
	initializeSprites();
	for(int i = 0; i < TOTAL_HUD; i++){
		this->canRenderHud[i] = true;
	}
}

PlayerHUD::~PlayerHUD(){

}

void PlayerHUD::update(){
	switch(this->player->life){
		case 2:
			this->canRenderHud[3] = false;
			break;
		case 1:
			this->canRenderHud[2] = false;
			break;
		case 0:
			this->canRenderHud[1] = false;
			break;
		default :
			break;
	}
}

void PlayerHUD::render(){
	for(int i = 0; i < TOTAL_HUD; i++){
		if(this->canRenderHud[i]){
			this->playerHudSprites[i]->render(0, 0);
		}
	}
}

void PlayerHUD::initializeSprites(){
	this->playerHudSprites[0] = Game::instance().getResources().get("res/images/hud/health_0.png");
	this->playerHudSprites[1] = Game::instance().getResources().get("res/images/hud/health_33.png");
	this->playerHudSprites[2] = Game::instance().getResources().get("res/images/hud/health_66.png");
	this->playerHudSprites[3] = Game::instance().getResources().get("res/images/hud/health_99.png");
	this->playerHudSprites[4] = Game::instance().getResources().get("res/images/hud/hud_no_health.png");	
}