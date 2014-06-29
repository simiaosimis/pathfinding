#ifndef INCLUDE_PLAYER_H
#define INCLUDE_PLAYER_H

#include "DynamicEntity.h"
#include "Sprite.h"
#include "InputKeys.h"
#include "Animation.h"
#include <map>
#include <vector>

class StatePlayer;

class Potion;
/**
* The player entity class.
* Contains all the relevant implementation relative to the player.
*/
class Player : public DynamicEntity {

	public:
		/**
		* All possible player states.
		*/
		enum PStates : uint8_t {
			IDLE = 0,
			MOVING,
			AERIAL,
			ROLLING,
			CROUCHING,
			AIMING,
			MOVINGCROUCH,
			ATTACK,
			ATTACKMOVING,
			ATTACKJUMPING,
			HITED
		};

		enum PItems : uint8_t {
			POTION = 0
		};

		/**
		* The constructor.
		* Creates the player by setting the position and sprite.
		* @param x_ : position in x axis.
		* @param y_ : position in y axis.
		* @param sprite_ : which sprite to use.
		*/
		Player(const double x_, const double y_, const std::string& path_);

		/**
		* The destructor.
		* Exits the current state and destroys all states.
		*/
		virtual ~Player();

		/**
		* Updates the player.
		* @see Player::updateInput, Player::updatePosition
		* @param dt_ : Delta time. Time elapsed between one frame and the other, independent
		* 	of processing speed.
		*/
		virtual void update(const double dt_);

		/**
		* Renders the player.
		* Uses the player's sprite render method.
		* @see Sprite::render
		* @param cameraX_ : The x position of the camera.
		* @param cameraY_ : The y position of the camera.
		*/
		virtual void render(const double cameraX_, const double cameraY_);

		/**
		* @return The players current animation setting.
		*/
		Animation *getAnimation();

		bool isDead();

	private:
		virtual void updateBoundingBox();
		virtual void handleCollision(std::array<bool, CollisionSide::SOLID_TOTAL> detections_);
		bool goToLocation(int location_);

		Animation* animation; /**< Current player animation. */

};

#endif //INCLUDE_PLAYER_H
