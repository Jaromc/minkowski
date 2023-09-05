#include "sdl_opengl.h"
#include "sdl.h"
#include "GL_Functions.h"

int main()
{
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);

	//init opengl/SDL
	gl->InitGL(500,500);
	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

	Main main;

	//enter main loop
	while (main.Update())
	{

	}

	SDL_Quit();

	return 0;
}

