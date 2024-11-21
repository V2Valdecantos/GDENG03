#pragma once
#include "InputListener.h"
#include "Windows.h"
#include <unordered_set>
#include "Point.h"

class InputSystem
{
public:
	typedef std::vector<InputListener*> List;

	static InputSystem* getInstance();

	static void initialize();
	static void destroy();

	void addListener(InputListener* listener);
	void removeListener(InputListener* listener);
	void update();


	bool isKeyDown(int key);
	bool isKeyUp(int key);

	void setCursorPosition(const Point& pos);
	void showCursor(bool show);


private:
	InputSystem();
	~InputSystem();
	InputSystem(InputSystem const&) {};
	InputSystem& operator*(InputSystem const&) {};
	bool release();

private:
	void callOnKeyDown(int key);
	void callOnKeyUp(int key);

	void callOnMouseMove(Point deltaPt);
	void callOnLeftMouseDown(Point deltaPt);
	void callOnLeftMouseUp(Point deltaPt);
	void callOnRightMouseDown(Point deltaPt);
	void callOnRightMouseUp(Point deltaPt);

	static InputSystem* sharedInstance;
	List inputListenerList;
	unsigned char keyStates[256] = {};
	unsigned char oldKeyStates[256] = {};
	Point m_old_mouse_pos;
	bool m_first_time = true;

};
