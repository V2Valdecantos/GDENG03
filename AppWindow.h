#pragma once
#include "Window.h"
#include "Renderer.h"

#include <iostream>

class Renderer;

class AppWindow: public Window
{
	public:
		AppWindow();
		~AppWindow();

		// Inherited via Window
		virtual void onCreate() override;
		virtual void onUpdate() override;
		virtual void onDestroy() override;

	private:
		Renderer* renderer;
		float fTicks;
}; 

