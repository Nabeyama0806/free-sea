#pragma once
#include "Vector2.h"
#include <functional>

class Button
{
private:
	Vector2 m_size;
	std::function<void()> m_callbackFunction;
	int m_mouseButton;
	bool m_isClickDown;
	bool IsMouseContain(const Vector2& position);

public:
	Button(const Vector2& size, int mouseButton, std::function<void()> callbackFunction);

	void Update(const Vector2& position);
	void Draw(const Vector2& position);
};
