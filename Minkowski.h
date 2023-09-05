#include "Vector2.h"
#include "MinkowskiCollision.h"
#include <vector>

//defines the origin of the screen
#define ORIGIN_X 250
#define ORIGIN_Y 250

class Minkowski
{
private:
	//container for the polygons
	std::vector<cPolygon> m_vecPolys;
	//true if we the user has selected a polygon
	bool m_bObjectSelected;
	//if a polygon is selectes then we store the index to it
	int m_iSelectedIndex;
	//true if we want to rotation a polygon
	bool m_bRotate;
	//the origin used for the collision hull
	//this is only used to translate the collision hull for display purposes
	const Vector2 m_vOrigin;
	//method used for collision detection
	MinkowskiCollision collisionDetection;
public:
	Minkowski();
	~Minkowski(){}

	bool Update();
	bool HandleInput();
	void DrawLine(const Vector2 &vp1, const Vector2 &vp2, float r, float g, float b)const;
};