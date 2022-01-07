#pragma once
#include <bitset>
#include "Include/GL/glew.h"
#include "Include/GLFW/glfw3.h"
#include "vector2.hpp"

class Input
{
public:

	static void Triggerd_Reset();

	static void Initialize(int width = 0, int height = 0);
	static void Reset(void);

	static void SetKeyPressed(int key, int action);
	static bool IsKeyPressed(int key);
	static bool IsKeyTriggered(int key);
	static bool IsKeyReleased(int key);
	static bool IsKeyAnyPressed();
	static bool IsKeyAnyTriggered();
	static bool IsKeyAnyReleased();

	static void SetMousePos(double x_pos, double y_pos);
	static vector2 GetMousePos(float zoom = 1);

	static void SetMousePressed(int button, int action);
	static void SetMouseWheelScroll(double x_offset, double y_offset);

	static bool IsMousePressed(int button);
	static bool IsMouseTriggered(int button);
	static bool IsMouseDoubleClicked(int button);
	static bool IsMouseReleased(int button);
	static double MouseWheelScroll();

private:
	static std::bitset<GLFW_KEY_LAST> key_pressed;
	static std::bitset<GLFW_KEY_LAST> key_triggered;
	static std::bitset<GLFW_KEY_LAST> key_released;

	static vector2 mousePos;
	static vector2 windowSize;

	static std::bitset<GLFW_MOUSE_BUTTON_LAST> mouse_pressed;
	static std::bitset<GLFW_MOUSE_BUTTON_LAST> mouse_triggered;
	static std::bitset<GLFW_MOUSE_BUTTON_LAST> mouse_doubleclick;
	static std::bitset<GLFW_MOUSE_BUTTON_LAST> mouse_released;

	static bool mouse_trigger;
	static bool key_trigger;
	static double x_offset_;
	static double y_offset_;
};

