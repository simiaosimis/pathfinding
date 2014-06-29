#ifndef INCLUDE_COLLISIONRECT_H
#define INCLUDE_COLLISIONRECT_H

#include "SDLWrapper.h"

enum TypeCollision : uint8_t {
	COLLISION = 0,
	GRASS,
	LEVEL_BEGIN,
	GROUND,
	NONE
};

/**
* Simple collision detection.
*/
class CollisionRect {

	public:
		CollisionRect(const int x_, const int y_, const int w_, const int h_,
			const TypeCollision type_);
		
		CollisionRect(const SDL_Rect rect_, const TypeCollision type_);
		
		virtual ~CollisionRect();

		static TypeCollision stringToType(const std::string& strType_);

		TypeCollision type;
		SDL_Rect rect;

};

#endif // INCLUDE_COLLISIONRECT_H
