#pragma once
#include "System.hpp"
#include "Include/GL/glew.h"
#include "Include/GLFW/glfw3.h"
#include <string>
#include "Input.hpp"

class Application : public System
{
public:
	Application(unsigned int width, unsigned int height) : SCR_WIDTH(width), SCR_HEIGHT(height) {}
	bool Init() override;
	bool Update(float dt) override;
	void Quit() override;

public:
	void processInput(GLFWwindow *window);

private:
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;
	GLFWwindow* window = nullptr;

};

