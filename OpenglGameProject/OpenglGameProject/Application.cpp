#include <iostream>
#include "Application.hpp"
#include "Transform.hpp"

namespace
{
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	//void Window_Exit(GLFWwindow* window);
	void errorCallback(int errorCode, const char* errorDescription);
	void window_resized(GLFWwindow* window, int width, int height);
	void KeyCallback(GLFWwindow* window, int key, int scancode
		, int action, int mods);
	void MousePositionCallback(GLFWwindow* window, double x_pos, double y_pos);
	void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	void MouseWheelScroll(GLFWwindow* window, double x_offset, double y_offset);
	//void DropCallBack(GLFWwindow* window, int count, const char** paths);
}


bool Application::Init()
{
	glfwSetErrorCallback(errorCallback);

	// glfw: initialize and configure
	// ------------------------------
	if (!glfwInit())
	{
		std::cerr << "GLFW Initialize failed" << '\n';
		return false;
	}

	// We use OpenGL 3.3 version 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// To make MacOS happy
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// We don't use the past OpenGL
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// glfw window creation
	//4 parameter : full screen mode -> if want to use glfwGetPrimaryMonitor(),
	//5 patameter : share resources
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	//const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	//glfwSetWindowMonitor(window, nullptr, (mode->width / 2) - static_cast<int>(SCR_WIDTH / 2),
	//	(mode->height / 2) - static_cast<int>(SCR_HEIGHT / 2),
	//	static_cast<int>(SCR_WIDTH), static_cast<int>(SCR_HEIGHT), 0);


	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetWindowSizeCallback(window, window_resized);
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MousePositionCallback);
	glfwSetMouseButtonCallback(window, MouseButtonCallback);
	glfwSetScrollCallback(window, MouseWheelScroll);
	//glfwSetDropCallback(window, DropCallBack);
	//glfwSetWindowCloseCallback(window, Window_Exit);

	Input::Initialize(static_cast<int>(SCR_WIDTH), static_cast<int>(SCR_HEIGHT));

	glewInit();
	return true;
}


bool Application::Update(float dt) //if false->keep running
{
	// input
	// -----
	Input::Triggerd_Reset();


	// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
	// -------------------------------------------------------------------------------
	glfwSwapBuffers(window);
	glfwSwapInterval(true);
	glfwPollEvents();
	processInput(window);

	//if glfwWindowShouldClose->true : return false for quit
	//else					  ->false: return true for keep going
	return !glfwWindowShouldClose(window);
}

void Application::Quit()
{
	// glfw: terminate, clearing all previously allocated GLFW resources.
   // ------------------------------------------------------------------
	glfwTerminate();
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void Application::processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

namespace
{
	// glfw: whenever the window size changed (by OS or user resize) this callback function executes
	// ---------------------------------------------------------------------------------------------
	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		// make sure the viewport matches the new window dimensions; note that width and 
		// height will be significantly larger than specified on retina displays.
		glViewport(0, 0, width, height);
	}

	void errorCallback(int errorCode, const char* errorDescription)
	{
		fprintf(stderr, "Error: %s\n", errorDescription);
	}

	void window_resized(GLFWwindow* window, int width, int height)
	{
	}

	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Input::SetKeyPressed(key, action);
	}
	//void DropCallBack(GLFWwindow* window, int count, const char** paths)
	//{
	//	std::string path(paths[0]);
	//	Imgui_System::soundlist.push_back(path);
	//}

	void MousePositionCallback(GLFWwindow* window, double x_pos, double y_pos)
	{
		Input::SetMousePos(x_pos, y_pos);
	}

	void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		Input::SetMousePressed(button, action);
	}

	void MouseWheelScroll(GLFWwindow* window, double x_offset, double y_offset)
	{
		Input::SetMouseWheelScroll(x_offset, y_offset);
	}
}

