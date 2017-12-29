#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup") //remove console window

#include "Application.h"

int main()
{
	Application* app = new Application();
	app->start(Application::TITLE_SCENE);
	return 0;
}