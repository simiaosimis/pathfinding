#include "CollisionRect.h"
#include "Logger.h"

CollisionRect::CollisionRect(const int x_, const int y_, const int w_, const int h_,
	const TypeCollision type_) :
	
	type(type_),
	rect{x_, y_, w_, h_}
{

}
		
CollisionRect::CollisionRect(const SDL_Rect rect_, const TypeCollision type_) :
	type(type_),
	rect(rect_)
{

}

CollisionRect::~CollisionRect(){

}

TypeCollision CollisionRect::stringToType(const std::string& strType_){
	if(strType_ == "collision"){
		return COLLISION;
	}
	else if(strType_ == "grass"){
		return GRASS;
	}
	else if(strType_ == "level_begin"){
		return LEVEL_BEGIN;
	}
	else if(strType_ == "ground"){
		return GROUND;
	}
	else{
		Log(ERROR) << "Unknown collision type for " << strType_ << " .";
		return NONE;
	}
}
