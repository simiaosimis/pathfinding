#include "Configuration.h"

// 16:10
const unsigned int Configuration::resolutionWidth = 192;
const unsigned int Configuration::resolutionHeight = 108;

uint32_t Configuration::maxFramerate = 0;
std::string Configuration::windowTitle = "";
unsigned int Configuration::logicalRenderSize = 0;
unsigned int Configuration::screenWidth = 0;
unsigned int Configuration::screenHeight = 0;
unsigned int Configuration::cameraDistanceWidth = 0;
unsigned int Configuration::cameraDistanceHeight = 0;


void Configuration::initialize(){

	Configuration::maxFramerate = 60;

	Configuration::windowTitle = "Trabalho de Grafo - EDA 2";

	Configuration::logicalRenderSize = 10;

	Configuration::cameraDistanceWidth =
		Configuration::resolutionWidth * Configuration::logicalRenderSize;

	Configuration::cameraDistanceHeight =
		Configuration::resolutionHeight * Configuration::logicalRenderSize;

	Configuration::screenWidth = 960;

	Configuration::screenHeight = 540;

}

unsigned int Configuration::getResolutionWidth(){
	return Configuration::resolutionWidth;
}

unsigned int Configuration::getResolutionHeight(){
	return Configuration::resolutionHeight;
}

uint32_t Configuration::getMaxFramerate(){
	return Configuration::maxFramerate;
}

std::string Configuration::getWindowTitle(){
	return Configuration::windowTitle;
}

unsigned int Configuration::getLogicalRenderSize(){
	return Configuration::logicalRenderSize;
}

unsigned int Configuration::getScreenWidth(){
	return Configuration::screenWidth;
}

unsigned int Configuration::getScreenHeight(){
	return Configuration::screenHeight;
}

unsigned int Configuration::getCameraDistanceWidth(){
	return Configuration::cameraDistanceWidth;
}

unsigned int Configuration::getCameraDistanceHeight(){
	return Configuration::cameraDistanceHeight;
}
