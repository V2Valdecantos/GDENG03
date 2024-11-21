#pragma once

#include "Camera.h"
#include "Matrix4x4.h"

class SceneCameraHandler
{
public:
	static SceneCameraHandler* getInstance();
	static void initialize();
	static void destroy();

	void init();
	void update(float deltaTime, RECT windowBounds);
	Matrix4x4 getSceneCameraViewMatrix();

private:
	SceneCameraHandler();
	~SceneCameraHandler();
	SceneCameraHandler(SceneCameraHandler const&) {}; 
	SceneCameraHandler& operator = (SceneCameraHandler const&) {};

	bool release();

	static SceneCameraHandler* sharedInstance;

	Camera* camera = nullptr;
};

