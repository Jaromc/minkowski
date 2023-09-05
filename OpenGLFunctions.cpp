#include "OpenGLFunctions.h"
#include "sdl_opengl.h"
#include "sdl.h"

Opengl* Opengl::mInstance = 0;

Opengl::Opengl()
{
}

int Opengl::InitGL(int width, int height)
{
	int error;

	//Initialise SDL
	error = SDL_Init (SDL_INIT_EVERYTHING);

	//gl and SDL settings
	SDL_GL_SetAttribute (SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute (SDL_GL_DEPTH_SIZE, 32);
	SDL_GL_SetAttribute (SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute (SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute (SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute (SDL_GL_ALPHA_SIZE, 8);

	//Use Hardware acceleration
	unsigned int flags = SDL_OPENGL | SDL_HWSURFACE;

	//Video mode
	SDL_SetVideoMode(width, height, 32, flags);

	//Window colour
	glClearColor (0.0, 0.0, 0.0, 0.0);

	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glOrtho (0.0, width, height, 0.0, 0.0, 10.0);

	//Disable v-sync
	typedef void (APIENTRY * WGLSWAPINTERVALEXT) (int);
	WGLSWAPINTERVALEXT wglSwapIntervalEXT = (WGLSWAPINTERVALEXT)
	wglGetProcAddress("wglSwapIntervalEXT");
	if (wglSwapIntervalEXT) {
	wglSwapIntervalEXT(0); // disable vertical synchronisation
	}

	return error;

}

void Opengl::DrawPoint (const Vector2 &position, float size, float R, float G, float  B)
{
	glDisable(GL_TEXTURE_2D);

	//Set the colour to the passed in colour
	glColor4f( R, G, B, 1 );

	//Set the Point size
	glPointSize( size );

	//Start drawing points
	glBegin(GL_POINTS);
	glVertex2f( position.x, position.y );
	glEnd();

	glEnable(GL_TEXTURE_2D);

	//Set the colour back to white
	glColor4f( 1, 1, 1, 1 );

}

Opengl::~Opengl()
{

}