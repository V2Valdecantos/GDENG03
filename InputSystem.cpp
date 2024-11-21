#include "InputSystem.h"

InputSystem* InputSystem::sharedInstance = nullptr;

InputSystem* InputSystem::getInstance()
{
	return sharedInstance;
}

void InputSystem::initialize()
{
	sharedInstance = new InputSystem();
}

void InputSystem::destroy()
{
	if (sharedInstance != NULL) {
		sharedInstance->release();
		delete sharedInstance;
	}
}

InputSystem::InputSystem() {

}

InputSystem::~InputSystem()
{
}

void InputSystem::addListener(InputListener* listener)
{
	// Check if the listener is already in the list
	if (std::find(inputListenerList.begin(), inputListenerList.end(), listener) == inputListenerList.end())
	{
		inputListenerList.push_back(listener);  // Add the listener if not already present
	}
}

void InputSystem::removeListener(InputListener* listener)
{
	// Use std::remove to remove the listener and erase the "removed" element
	std::vector<InputListener*>::iterator it = std::remove(inputListenerList.begin(), inputListenerList.end(), listener);
	if (it != inputListenerList.end())
	{
		inputListenerList.erase(it, inputListenerList.end());
	}
}

void InputSystem::update()
{
	POINT current_mouse_pos = {};
	::GetCursorPos(&current_mouse_pos);

	if (m_first_time)
	{
		m_old_mouse_pos = Point(current_mouse_pos.x, current_mouse_pos.y);
		m_first_time = false;
	}

	if (current_mouse_pos.x != m_old_mouse_pos.m_x || current_mouse_pos.y != m_old_mouse_pos.m_y)
	{
		//THERE IS MOUSE MOVE EVENT
		std::vector<InputListener*>::iterator it = inputListenerList.begin();

		while (it != inputListenerList.end())
		{
			(*it)->onMouseMove(Point(current_mouse_pos.x, current_mouse_pos.y));
			++it;
		}
	}
	m_old_mouse_pos = Point(current_mouse_pos.x, current_mouse_pos.y);



	if (::GetKeyboardState(keyStates))
	{
		for (unsigned int i = 0; i < 256; i++)
		{
			// KEY IS DOWN
			if (keyStates[i] & 0x80)
			{
				std::vector<InputListener*>::iterator it = inputListenerList.begin();

				while (it != inputListenerList.end())
				{
					if (i == VK_LBUTTON)
					{
						if (keyStates[i] != oldKeyStates[i])
							(*it)->onLeftMouseDown(Point(current_mouse_pos.x, current_mouse_pos.y));
					}
					else if (i == VK_RBUTTON)
					{
						if (keyStates[i] != oldKeyStates[i])
							(*it)->onRightMouseDown(Point(current_mouse_pos.x, current_mouse_pos.y));
					}
					else
						(*it)->onKeyDown(i);

					++it;
				}
			}
			else // KEY IS UP
			{
				if (keyStates[i] != oldKeyStates[i])
				{
					std::vector<InputListener*>::iterator it = inputListenerList.begin();

					while (it != inputListenerList.end())
					{
						if (i == VK_LBUTTON)
							(*it)->onLeftMouseUp(Point(current_mouse_pos.x, current_mouse_pos.y));
						else if (i == VK_RBUTTON)
							(*it)->onRightMouseUp(Point(current_mouse_pos.x, current_mouse_pos.y));
						else
							(*it)->onKeyUp(i);

						++it;
					}
				}

			}

		}
		// store current keys state to old keys state buffer
		::memcpy(oldKeyStates, keyStates, sizeof(unsigned char) * 256);
	}
}

void InputSystem::setCursorPosition(const Point& pos)
{
	::SetCursorPos(pos.m_x, pos.m_y);
}

void InputSystem::showCursor(bool show)
{
	::ShowCursor(show);
}

bool InputSystem::isKeyDown(int key)
{
	if (::GetKeyboardState(keyStates))

	if (keyStates[key] & 0x80) {
		return true;
	}

	else
		return false;
}

bool InputSystem::isKeyUp(int key)
{
	if (::GetKeyboardState(keyStates))

		if (keyStates[key] & 0x80) {
			return false;
		}

		else
			return true;
}


bool InputSystem::release()
{
	if(!inputListenerList.empty())
		inputListenerList.clear();
	
	return false;
}
