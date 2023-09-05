#include "Minkowski.h"
#include "PolygonUtilities.h"
#include "sdl_opengl.h"
#include "sdl.h"
#include "GL_Functions.h"

Minkowski::Minkowski():m_vOrigin(ORIGIN_X, ORIGIN_Y)
{
	m_vecPolys.push_back(cPolygon(4, Vector2(100,100)));
	m_vecPolys.push_back(cPolygon(12, Vector2(150,100)));

	m_bObjectSelected = false;
	m_iSelectedIndex = -1;
	m_bRotate = false;
}

bool Minkowski::Update()
{
	//handle uesr input
	if (!HandleInput())
		return false;

	//update the polygons
	m_vecPolys[0].Update();
	m_vecPolys[1].Update();

	glClear(GL_COLOR_BUFFER_BIT);

	//check for collisions
	CollisionData collisionData;
	if (collisionDetection.CheckCollision(m_vecPolys[0],
										m_vecPolys[1],
										m_vOrigin,
										collisionData))
	{
		//there is a collision so render the collision polygon red
		collisionDetection.GetHull().SetColor(1,0,0);
		//render the collision polygon
		collisionDetection.Render();
		//draw the closest edge to the origin
		DrawLine(collisionData.collisionEdgeStart ,collisionData.collisionEdgeEnd, 0,1,0);
		//draaw the collision normal*depth
		DrawLine(collisionData.collisionPoint,m_vOrigin, 0,1,0);
		//draw the closest point on the collision polygon to the origin
		gl->DrawPoint(collisionData.collisionPoint, 0,1,0,1);
	}
	else
	{
		//there is no collision so render the collision polygon white
		collisionDetection.GetHull().SetColor(1,1,1);
		collisionDetection.Render();
	}

	//render the polygons
	m_vecPolys[0].Render();
	m_vecPolys[1].Render();

	//draw the origin
	gl->DrawPoint(Vector2(250,250), 5,1,1,1);

	SDL_GL_SwapBuffers();

	return true;
}

bool Minkowski::HandleInput()
{
	SDL_Event event;
	//check for user input
	while (SDL_PollEvent (&event))
	{
		switch (event.type)
		{

		case SDL_MOUSEBUTTONDOWN:
			{
				//check polygon selection for translation 
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					if (!m_bObjectSelected && !m_bRotate)
					{
						Vector2 vMousePos(event.button.x, event.button.y);
						if (PolygonUtilities::PointInConvexPolygon(m_vecPolys[0].GetVerts(), vMousePos))
						{
							m_bObjectSelected = true;
							m_iSelectedIndex = 0;
						}
						else if(PolygonUtilities::PointInConvexPolygon(m_vecPolys[1].GetVerts(), vMousePos))
						{
							m_bObjectSelected = true;
							m_iSelectedIndex = 1;
						}
					}
				}
				//check polygon selection for rotation
				else if (event.button.button == SDL_BUTTON_RIGHT)
				{
					if (!m_bObjectSelected && !m_bRotate)
					{
						Vector2 vMousePos(event.button.x, event.button.y);
						if (PolygonUtilities::PointInConvexPolygon(m_vecPolys[0].GetVerts(), vMousePos))
						{
							m_bRotate = true;
							m_iSelectedIndex = 0;
						}
						else if(PolygonUtilities::PointInConvexPolygon(m_vecPolys[1].GetVerts(), vMousePos))
						{
							m_bRotate = true;
							m_iSelectedIndex = 1;
						}
					}
				}
				break;
			}
			
		//check for mouse release
		case SDL_MOUSEBUTTONUP:
			{
				if (m_bObjectSelected)
				{
					if (event.button.button == SDL_BUTTON_LEFT)
					{
						m_bObjectSelected = false;
						m_iSelectedIndex = -1;
					}
				}
				else if (m_bRotate)
				{
					if (event.button.button == SDL_BUTTON_RIGHT)
					{
						m_bRotate = false;
						m_iSelectedIndex = -1;
					}
				}
				break;
			}
		//check for mouse motion
		case SDL_MOUSEMOTION:
			{
				if (m_bObjectSelected)
				{
					m_vecPolys[m_iSelectedIndex].AddToPosition(event.motion.xrel, event.motion.yrel);
				}
				else if (m_bRotate)
				{
					m_vecPolys[m_iSelectedIndex].AddRotation((event.motion.xrel + event.motion.yrel) * 0.01f);
				}
				break;
			}
			//check for keyboard input
		case SDL_KEYDOWN:
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_s:
					m_vecPolys[0].IncreaseVertCount();
					break;
				case SDLK_a:
					m_vecPolys[0].DecreaseVertCount();
					break;
				case SDLK_x:
					m_vecPolys[1].IncreaseVertCount();
					break;
				case SDLK_z:
					m_vecPolys[1].DecreaseVertCount();
					break;
				case SDLK_ESCAPE:
					return false;
					break;
				}	
				break;
			}
		case SDL_QUIT:
			return false;
			break;
		}
	}

	return true;
}

void Minkowski::DrawLine(const Vector2 &vp1,
					const Vector2 &vp2,
					float r, float g, float b)const
{
	glColor4f( r, g, b, 1 );
	glBegin(GL_LINES);
	
	glVertex2f(vp1.x, vp1.y);	
	glVertex2f(vp2.x, vp2.y);

	glEnd();
}