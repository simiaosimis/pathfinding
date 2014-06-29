#ifndef INCLUDE_LEVEL_H
#define INCLUDE_LEVEL_H

#include "Sprite.h"
#include "Player.h"
#include "Camera.h"
#include "StateGame.h"
#include "TileMap.h"
#include "QuadTree.h"
#include "PlayerHUD.h"

/**
* Abstract class for levels.
* Contains a background, player and a camera.
*/
class Level : public StateGame {
	
	public:	
		/**
		* The destructor.
		* Deletes all the allocated attributes, even though the specific levels should.
		*/
		virtual ~Level();

		/**
		* @return The Level width.
		*/
		unsigned int getWidth();

		/**
		* @return The Level height.
		*/
		unsigned int getHeight();

	protected:
		/**
		* The constructor.
		* Initializes all the attributes.
		*/
		Level();

		/**
		* @param player_ : Sets the player for the level.
		*/
		virtual void setPlayer(Player* const player_);

		/**
		* @param camera_ : Sets the camera for the level.
		* @note You should only set the camera after setting the player. Will warn if you
		* 	didn't.
		*/
		virtual void setCamera(Camera* const camera_);

		virtual void clearEnemies();

		unsigned int width; /**< Width that defines the horizontal limits. */
		unsigned int height; /**< Height that defines the vertical limits. */

		Player* player; /**< The direct reference to player, even though its in the list. */
		Camera* camera; /**< The current camera for that level. */

		TileMap* tileMap;
		QuadTree* quadTree;

		Sprite* background;

};

#endif //INCLUDE_LEVEL_H
