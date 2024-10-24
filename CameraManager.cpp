#include "CameraManager.h"

CameraManager* CameraManager::P_SHARED_INSTANCE = NULL;
CameraManager::CameraManager() {}
CameraManager::CameraManager(const CameraManager&) {}

CameraManager* CameraManager::getInstance() {
    if (P_SHARED_INSTANCE == NULL)
        P_SHARED_INSTANCE = new CameraManager();

    return P_SHARED_INSTANCE;
}

CameraManager::~CameraManager()
{
}

void CameraManager::Update()
{
    this->activeCamera->Update(EngineTime::getDeltaTime(), this->activeCamera->getViewMatrix(), this->activeCamera->getProjMatrix());
}

void CameraManager::AddCamera(Camera* cam)
{
    this->cameras.push_back(cam);
    this->setActiveCamera();
}

std::vector<Camera*> CameraManager::GetCameras()
{
    return this->cameras;
}

Camera* CameraManager::GetActiveCamera()
{
    return this->activeCamera;
}

void CameraManager::CycleCameras()
{
    if (this->camIndex + 1 <= cameras.size())
        this->camIndex += 1;
    else
        this->camIndex = 0;

    this->activeCamera->setActive(false);

    this->activeCamera = this->cameras[this->camIndex];
    this->activeCamera->setActive(true);
}

void CameraManager::setActiveCamera()
{
    this->activeCamera = this->cameras[this->camIndex];
    this->activeCamera->setActive(true);
}

Matrix4x4 CameraManager::getViewMatrix()
{
    return this->activeCamera->getViewMatrix();
}

Matrix4x4 CameraManager::getProjMatrix()
{
    return this->activeCamera->getProjMatrix();
}
