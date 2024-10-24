#pragma once
#include "Camera.h"
#include <iostream>
#include <vector>

class Camera;
class CameraManager
{
	public:
		CameraManager();
		~CameraManager();
		
		void Update();
		void AddCamera(Camera* cam);
		std::vector<Camera*> GetCameras();
		Camera* GetActiveCamera();
		void CycleCameras();
		void setActiveCamera();

		Matrix4x4 getViewMatrix();
		Matrix4x4 getProjMatrix();

	private:
		std::vector<Camera*> cameras;
		Camera* activeCamera;
		int camIndex = 0;


	private:
		static CameraManager* P_SHARED_INSTANCE;

	private:
		CameraManager(const CameraManager&);
		CameraManager& operator = (const CameraManager&);

	public:
		static CameraManager* getInstance();

	friend class GameObject;
};

