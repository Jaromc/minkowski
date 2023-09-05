#include "Vector2.h"
#include "Polygon.h"
#include <vector>
#include <list>

class PolygonUtilities
{
private:
	//sorting algorithm that needs work.
	//If any of the given points share the same X axis then the lesser or greater value
	//Y axis is deleted depending on the value of bUpper
	static void UniqueXAxis(std::list<Vector2> &points, bool bUpper);
public:
	//returns true if the given point is inside the polygon as defined by the verticies
	static bool PointInConvexPolygon(const std::vector<Vector2> &vecVerticies,
											const Vector2 &vPoint);

	//returns true if the given triangle is counter clockwise
	static bool TriangleIsCCW(const Vector2 &p1, const Vector2 &p2, const Vector2 &p3);

	//fast test.
	//used to determine what side of a line segment the given point lies
	static bool CalculateWherePointLies(const Vector2 &vPointPos,
								 const Vector2 &vLineStart,
								 const Vector2 &vLineEnd);

	//determines which side of the plane a point lies
	//returns positive if the point lies on the side to which
	//the plane points. if vPlaneDir is normalized then the return
	//will be the distance of the object from the plane
	//returns negative if the point is on the opposite side
	//returns zero if the point lies on the plane
	static float CalculateWherePointLiesEx(const Vector2 &vPointPos,
								 const Vector2 &vLineStart,
								 const Vector2 &vLineEnd);

	//returns the closest point (p) from the point (vPoint)
	//to the line segment (vLineA, vLineB)
	static void ClosestPointLineSegment(const Vector2 &vPoint,
								 const Vector2 &vLineA,
								 const Vector2 &vLineB,
								 Vector2 &p);

	 //returns the squared distance from a point (vPoint)
	 //to a line segment (vLineA, vLineB)
	static float SquaredDistPointSegment(const Vector2 &vPoint,
							 const Vector2 &vLineA,
							 const Vector2 &vLineB);

	//returns the closest edge and the distance to a polygon
	//as defined in vecPoints to a point
	static void GetClosestEdgeToPoint(const std::vector<Vector2> &vecPoints,
						   const Vector2 &vPoint,
						   CollisionData &colData);

	//creates a convex hull from the given points
	static void CreateConvexHull(const std::list<Vector2> &points,
								cPolygon &returnHull);
};