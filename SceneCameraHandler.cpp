#include "SceneCameraHandler.h"
#include <iostream>

SceneCameraHandler* SceneCameraHandler::sharedInstance = nullptr;

SceneCameraHandler* SceneCameraHandler::getInstance()
{
	return sharedInstance;
}

void SceneCameraHandler::initialize()
{
	sharedInstance = new SceneCameraHandler();
	sharedInstance->init();
	
}

void SceneCameraHandler::destroy()
{
	if (sharedInstance != NULL) {
		sharedInstance->release();
		delete sharedInstance;
	}
}

void SceneCameraHandler::init()
{
	this->camera = new Camera("MyCamera");
}

void SceneCameraHandler::update(float deltaTime, RECT windowBounds)
{
	this->camera->update(deltaTime, windowBounds);
}


Matrix4x4 SceneCameraHandler::getSceneCameraViewMatrix()
{
	return this->camera->getViewMatrix();
}

SceneCameraHandler::SceneCameraHandler()
{
}

SceneCameraHandler::~SceneCameraHandler()
{
}

bool SceneCameraHandler::release()
{
	return false;
}
