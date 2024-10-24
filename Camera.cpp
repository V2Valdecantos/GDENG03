#include "Camera.h"

Camera::Camera() : GameObject("Camera")
{

}

Camera::~Camera()
{
}

void Camera::Update(float deltaTime, Matrix4x4 view, Matrix4x4 proj)
{
	this->UpdateViewMatrix();
}

void Camera::UpdateViewMatrix()
{
	CBData cbData = {};
	cbData.m_time = 0;
	ConstantBuffer* cb = GraphicsEngine::get()->createConstantBuffer();
	cb->load(&cbData, sizeof(CBData));

	Matrix4x4 temp;

	cbData.m_world.setIdentity();

	Matrix4x4 world_cam;
	world_cam.setIdentity();

	temp.setIdentity();
	temp.setRotationX(this->localRotation.m_x);
	world_cam *= temp;

	temp.setIdentity();
	temp.setRotationY(this->localRotation.m_y);
	world_cam *= temp;


	Vector3D new_pos = this->localPosition + world_cam.getZDirection() * (m_forward * 0.1f);

	new_pos = new_pos + world_cam.getXDirection() * (m_rightward * 0.1f);
	this->localPosition = new_pos;

	world_cam.setTranslation(new_pos);

	this->worldMatrix = world_cam;


	world_cam.inverse();

	this->viewMatrix = world_cam;
	cbData.m_view = world_cam;

	if (!isOrtho) 
	{
		this->projMatrix.setPerspectiveFovLH(1.57f, ((float)1024 / (float)720), 0.1f, 100.0f);
		cbData.m_proj.setPerspectiveFovLH(1.57f, ((float)1024 / (float)720), 0.1f, 100.0f);
	}
	else 
	{
		this->projMatrix.setOrthoLH(1024 / 90, 720 / 90, 0.1f, 100.0f);
		cbData.m_proj.setOrthoLH(1024 / 90, 720 / 90, 0.1f, 100.0f);
	}
		

	cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cbData);

}

bool Camera::isActive()
{
	return false;
}

void Camera::setActive(bool active)
{
	this->active = active;
}

void Camera::draw(Window* window)
{
}

void Camera::ToggleOrtho()
{
}

Matrix4x4 Camera::getViewMatrix()
{
	return this->viewMatrix;
}

Matrix4x4 Camera::getProjMatrix()
{
	return this->projMatrix;
}

void Camera::onKeyDown(int key)
{
	if (this->active) 
	{
		if (key == 'W')
		{
			this->m_forward = 1.0f;
			this->UpdateViewMatrix();
		}
		if (key == 'S')
		{
			this->m_forward = -1.0f;
			this->UpdateViewMatrix();
		}

		if (key == 'A')
		{
			this->m_rightward = -1.0f;
			this->UpdateViewMatrix();
		}
		if (key == 'D')
		{
			this->m_rightward = 1.0f;
			this->UpdateViewMatrix();
		}
	}
}

void Camera::onKeyUp(int key)
{
	if (this->active)
	{
		this->m_forward = 0.0f;
		this->m_rightward = 0.0f;

		if (key == 'Q')
			this->isOrtho = !this->isOrtho;
	}


}

void Camera::onMouseMove(const Point& mouse_pos)
{


	if (!isOrtho)
	{
		this->localRotation.m_x += (mouse_pos.m_y - (720 / 2.0f)) * EngineTime::getDeltaTime() * 0.1f;
		this->localRotation.m_y += (mouse_pos.m_x - (1024 / 2.0f)) * EngineTime::getDeltaTime() * 0.1f;
	}
	InputSystem::get()->setCursorPosition(Point((int)(1024 / 2.0f), (int)(720 / 2.0f)));
	this->UpdateViewMatrix();
}

void Camera::onLeftMouseDown(const Point& mouse_pos)
{
}

void Camera::onLeftMouseUp(const Point& mouse_pos)
{
}

void Camera::onRightMouseDown(const Point& mouse_pos)
{
}

void Camera::onRightMouseUp(const Point& mouse_pos)
{
}
