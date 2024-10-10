#pragma once
#include "Window.h"
#include "Renderer.h"
#include "InputListener.h"

#include <iostream>

class Renderer;

class AppWindow: public Window, public InputListener
{
	public:
		AppWindow();
		~AppWindow();

		// Inherited via Window
		virtual void onCreate() override;
		virtual void onUpdate() override;
		virtual void onDestroy() override;

		virtual void onKeyDown(int key) override;
		virtual void onKeyUp(int key) override;

	private:
		Renderer* renderer;
		float fTicks;
}; 

