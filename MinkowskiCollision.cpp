#include "MinkowskiCollision.h"

//when a collision has been found, this returns the collision information.
//vOrigin is only used for display purposes. It defines where the MinkowskiHull
//should be centered on the screen
void MinkowskiCollision::GetCollisionData(const std::vector<Vector2> &vecVerts,
										  const Vector2 &vOrigin,
										  CollisionData &collisionData)
{
	//get the closest edge to the point within collisionData
	PolygonUtilities::GetClosestEdgeToPoint(vecVerts, vOrigin, collisionData);

	//gets the closest point on a line segment to the given point
	PolygonUtilities::ClosestPointLineSegment(vOrigin,
		collisionData.collisionEdgeStart,
		collisionData.collisionEdgeEnd,
		collisionData.collisionPoint);

	//calculate the collision normal
	Vector2 perp = collisionData.collisionEdgeEnd - collisionData.collisionEdgeStart;
	collisionData.collisionNormal.x = -perp.y;
	collisionData.collisionNormal.y = perp.x;
	collisionData.collisionNormal = collisionData.collisionNormal.Normalise();
	
	//calculate the collision  depth.
	collisionData.depth = sqrtf(collisionData.depth);
}
//creates a convex hull used for collision detection for the 
//polygons A and B.
//vOrigin is only used for display purposes. It defines where the MinkowskiHull
//should be centered on the screen
void MinkowskiCollision::CreateMinkowskiHull(const cPolygon &objectA,
											 const cPolygon &objectB,
											 const Vector2 &vOrigin)
{
	int iVertexCountA = objectA.GetVerts().size();
	int iVertexCountB = objectB.GetVerts().size();

	//The minkowski difference is defined by:
	//for all verts in A and for all verts in B, MinkowskiHull = vertA - vertB
	//the origin is added to the position for display purposes only
	std::list<Vector2> temp;
	for (int i = 0; i < iVertexCountA; i++)
	{
		for (int j = 0; j < iVertexCountB; j++)
		{
			temp.push_back((objectB.GetVerts()[j] - objectA.GetVerts()[i]) + Vector2(vOrigin.x,vOrigin.y));
		}
	}

	//create the convex hull from the given vertices 
	PolygonUtilities::CreateConvexHull(temp, m_MinkowskiHull);
}
//returns true and the collision data if a collision was detected between
//polygons A and B.
//vOrigin is only used for display purposes. It defines where the MinkowskiHull
//should be centered on the screen
bool MinkowskiCollision::CheckCollision(const cPolygon &objectA,
						 const cPolygon &objectB,
						 const Vector2 &vOrigin,
						 CollisionData &collisionData)
{
	//clear the verts
	m_MinkowskiHull.ClearVerts();
	//create the collision hull from objects A and B
	CreateMinkowskiHull(objectA, objectB, vOrigin);

	//if the origin is contained within the collision hull then the two objects intersect
	if (PolygonUtilities::PointInConvexPolygon(m_MinkowskiHull.GetVerts(), vOrigin))
	{
		//there is a collision so get the collision data
		GetCollisionData(m_MinkowskiHull.GetVerts(),
							vOrigin,
							collisionData);
							
		return true;
	}
	//there is no collision so return false
	else
		return false;
}

void MinkowskiCollision::Render()
{
	m_MinkowskiHull.Render();
}