#include "ResourceManager.h"
#include "Logger.h"

ResourceManager::ResourceManager() :
	resources()
{

}

ResourceManager::~ResourceManager(){
	std::map<std::string, Sprite::SpritePtr>::const_iterator it;
	
	for(it = this->resources.begin(); it != this->resources.end(); it++){
		if(it->second.use_count() != 1){
			Log(WARN) << "Resource deleted with use count different than 1 (" << it->first << ").";
		}
	}
}

Sprite* ResourceManager::get(const std::string& path_){
	std::map<std::string, Sprite::SpritePtr>::const_iterator it;
	it = this->resources.find(path_);

	if (it != this->resources.end()){
		return it->second.get();
	}
	else{
		return load(path_).get();
	}
	
}

void ResourceManager::registerResource(const std::string& path_, Sprite::SpritePtr resource_){
	this->resources.insert( std::make_pair(path_, resource_) );
}

void ResourceManager::unregisterResource(const std::string& path_){
	std::map<std::string, Sprite::SpritePtr>::const_iterator it;
	it = this->resources.find(path_);

	if (it != this->resources.end()){
		this->resources.erase(it);
	}
}

Sprite::SpritePtr ResourceManager::load(const std::string& path_){
	Sprite::SpritePtr sprite = std::make_shared<Sprite>(path_);
	registerResource(path_, sprite);
	return sprite;
}
