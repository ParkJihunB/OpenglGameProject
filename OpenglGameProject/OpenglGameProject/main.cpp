/**
* @mainpage main
* @brief main of program
* @details main of program
*/
#include "Engine.hpp"

int main(void)
{
	Engine* engine = new Engine();

	engine->Init();
	engine->Update();
	engine->Quit();

	return 0;
}