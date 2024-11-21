#pragma once
#include <string>
#include "imgui.h"
#include "LogUtils.h"

class UIManager;

using std::string;

class UIScreen
{
public:
	UIScreen(const UIScreen& obj) = delete;
	UIScreen(UIScreen&& other) noexcept = delete;

protected:
	explicit UIScreen(string name) : name(std::move(name)) {}

	virtual ~UIScreen() = default;
	UIScreen& operator=(const UIScreen& other) = default;
	UIScreen& operator=(UIScreen&& other) noexcept = default;

	string getName() { return name; }
	virtual void draw() = 0;

	string name;

	friend class UIManager;
};

