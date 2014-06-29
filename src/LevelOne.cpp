#include "LevelOne.h"
#include "Game.h"
#include "Logger.h"
#include "TileMap.h"
#include "Collision.h"

LevelOne::LevelOne() :
	Level()
{

}

LevelOne::~LevelOne(){

}

void LevelOne::load(){
	Log(DEBUG) << "Loading level 1...";

	// Loading the tile/tilemap.
	this->tileMap = new TileMap("res/maps/level1.tmx");

	// Setting the level width/height.
	this->width = this->tileMap->getMapWidth();
	this->height = this->tileMap->getMapHeight();
	SDL_Rect bounds = {0, 0, (int)this->width, (int)this->height};
	this->quadTree = new QuadTree(0, bounds);

	this->background = Game::instance().getResources().get("res/images/lv1_background.png");

	const std::string pathPlayerSpriteSheet = "res/images/spriteSheet_nadine.png";

	// Loading the player and the camera.
	Player* lPlayer = new Player(this->tileMap->getInitialX(), this->tileMap->getInitialY(), pathPlayerSpriteSheet);
	Camera* lCamera = new Camera(lPlayer); 

	// Finally, setting the player and the camera.
	setPlayer(lPlayer);

	setCamera(lCamera);

	Game::instance().getFade().fadeOut(0, 0.002);
}

void LevelOne::unload(){
	Log(DEBUG) << "\tUnloading level 1...";
	cleanEntities();
	clearEnemies();
	Log(DEBUG) << "\t level 1 unloaded...";
}

void LevelOne::update(const double dt_){
	// Populating the QuadTree.
	this->quadTree->setObjects(this->tileMap->getCollisionRects());

	// Updating the entities, using the QuadTree.
	std::vector<CollisionRect> returnObjects;
	for (auto entity : this->entities) {
		returnObjects.clear();
		this->quadTree->retrieve(returnObjects, entity->getBoundingBox());
		entity->setCollisionRects(returnObjects);
		entity->update(dt_);
	}


	// Updating the camera.
	this->camera->update();
	
}

void LevelOne::render(){
	const int cameraX = this->camera->getClip().x;
	const int cameraY = this->camera->getClip().y;

	// Render the tiles in the TileMap.
	this->tileMap->render(cameraX, cameraY);

	// Render all the entities in the list.
	for(auto entity : this->entities){
        entity->render(cameraX, cameraY);
	}
}

