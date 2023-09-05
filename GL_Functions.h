#include "Vector2.h"

class Opengl
{
private:
	Opengl();
	~Opengl();

	static Opengl* mInstance;
public:

	static Opengl* Instance()
	{
		if ( mInstance == NULL )
			mInstance = new Opengl();

		return mInstance;
	}

	static void Destroy()
	{
		delete mInstance;
		mInstance = 0;
	}

	int InitGL (int width, int height);
	void DrawPoint (const Vector2 &position, float size = 2, float R = 1, float G = 1, float  B = 1);
	
};

#define gl Opengl::Instance()