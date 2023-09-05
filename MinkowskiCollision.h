#include "Vector2.h"
#include "Polygon.h"

class MinkowskiCollision
{
private:
	//this hull is created when CheckCollision is called.
	//It is used for collision detection
	cPolygon m_MinkowskiHull;

protected:

	//when a collision has been found, this returns the collision information.
	//vOrigin is only used for display purposes. It defines where the MinkowskiHull
	//should be centered on the screen
	void GetCollisionData(const std::vector<Vector2> &vecVerts,
					  const Vector2 &vOrigin,
					  CollisionData &collisionData);

	//creates a convex hull used for collision detection for the 
	//polygons A and B.
	//vOrigin is only used for display purposes. It defines where the MinkowskiHull
	//should be centered on the screen
	void CreateMinkowskiHull(const cPolygon &objectA,
											 const cPolygon &objectB,
											 const Vector2 &vOrigin);

public:
	//returns true and the collision data if a collision was detected between
	//polygons A and B.
	//vOrigin is only used for display purposes. It defines where the MinkowskiHull
	//should be centered on the screen
	bool CheckCollision(const cPolygon &objectA,
						 const cPolygon &objectB,
						 const Vector2 &vOrigin,
						 CollisionData &collisionData);

	void Render();

	//returns the convex hull used for collision detection
	cPolygon& GetHull(){return m_MinkowskiHull;}
};