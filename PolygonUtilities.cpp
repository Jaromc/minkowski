#include "PolygonUtilities.h"
#include "SortingStructures.h"

//returns true if the given point is inside the polygon as defined by the verticies
bool PolygonUtilities::PointInConvexPolygon(const std::vector<Vector2> &vecVerticies,
											const Vector2 &vPoint)
{
	int iNumVerts = vecVerticies.size();

    //search over the polygon verts to find the fan triangle the
    //point p lies within
    int iLow = 0; int iHigh = iNumVerts;
    do
    {
        int iMid = (iLow + iHigh) / 2;
        if (TriangleIsCCW(vecVerticies[0], vecVerticies[iMid], vPoint))
            iLow = iMid;
        else
            iHigh = iMid;

    } while (iLow + 1 < iHigh);

    //if point outside last or first edge then it is not inside the n-gon
    if (iLow == 0 || iHigh == iNumVerts)
        return false;

    //p is inside the polygon if it is left of
    //the directed edge from points[iLow] to points[iHigh]
    return TriangleIsCCW(vecVerticies[iLow], vecVerticies[iHigh], vPoint);
}

//returns true if the triangle defined by p1,p2,p2 is counter clockwise
bool PolygonUtilities::TriangleIsCCW(const Vector2 &p1, const Vector2 &p2, const Vector2 &p3)
{
    float fArea = p3.x * p1.y - p1.x * p3.y;
    fArea += p1.x * p2.y - p2.x * p1.y;
    fArea += p2.x * p3.y - p3.x * p2.y;

    if (fArea >= 0.0f)
        return true;
    else
        return false;
}

//fast test.
//used to determine what side of a line segment the given point lies
bool PolygonUtilities::CalculateWherePointLies(const Vector2 &vPointPos,
							 const Vector2 &vLineStart,
							 const Vector2 &vLineEnd)									 
{
	Vector2 vDiff = vLineEnd - vLineStart;
	Vector2 vNorm(-vDiff.y, vDiff.x);

	if ((vPointPos - vLineStart).DotProduct(vNorm) > 0.0f)
		return true;
	else
		return false;
}

//determines which side of the plane a point lies
//returns positive if the point lies on the side to which
//the plane points. if vPlaneDir is normalized then the return
//will be the distance of the object from the plane
//returns negative if the point is on the opposite side
//returns zero if the point lies on the plane
float PolygonUtilities::CalculateWherePointLiesEx(const Vector2 &vPointPos,
							 const Vector2 &vLineStart,
							 const Vector2 &vLineEnd)									 
{
	Vector2 vDiff = vLineStart - vLineEnd;
	Vector2 vNorm(-vDiff.y, vDiff.x);

	vNorm = vNorm.Normalise();

	return (vPointPos - vLineStart).DotProduct(vNorm);
}

//returns the closest point (p) from the point (vPoint)
//to the line segment (vLineA, vLineB)
void PolygonUtilities::ClosestPointLineSegment(const Vector2 &vPoint,
							 const Vector2 &vLineA,
							 const Vector2 &vLineB,
							 Vector2 &p)
{
	Vector2 ab = vLineB - vLineA;
	//project vPoint onto ab
	float t = (vPoint - vLineA).DotProduct(ab) / ab.DotProduct(ab);
	//if outside segment, clamp t
	if (t < 0.0f)
		t = 0.0f;
	if (t > 1.0f)
		t = 1.0f;
	//compute projects position from the clamped t
	p = vLineA + t * ab;
}

//returns the squared distance from a point (vPoint)
//to a line segment (vLineA, vLineB)
float PolygonUtilities::SquaredDistPointSegment(const Vector2 &vPoint,
							 const Vector2 &vLineA,
							 const Vector2 &vLineB)
{
	Vector2 ab = vLineB-vLineA, ac = vPoint - vLineA, bc = vPoint - vLineB;
	float e = ac.DotProduct(ab);
	if (e <= 0.0f)
		return ac.DotProduct(ac);

	float f = ab.DotProduct(ab);
	if (e >= f)
		return bc.DotProduct(bc);

	return ac.DotProduct(ac) - e*e / f;
}

//returns the closest edge and the distance to a polygon
//as defined in vecPoints to a point
void PolygonUtilities::GetClosestEdgeToPoint(const std::vector<Vector2> &vecPoints,
						   const Vector2 &vPoint,
						   CollisionData &colData)
{
	int iSize = vecPoints.size();
	Vector2 p;
	float tMax = INFINITE;
	for (int i = 0; i < iSize; i++)
	{
		if (i+1 == iSize)
			break;

		colData.depth = SquaredDistPointSegment(vPoint, vecPoints[i], vecPoints[i+1]);
		if (colData.depth < tMax)
		{
			tMax = colData.depth;
			colData.collisionEdgeStart = vecPoints[i];
			colData.collisionEdgeEnd = vecPoints[i+1];
		}
	}

	//we also need to test the verts at the start and end of the polygon
	colData.depth = SquaredDistPointSegment(vPoint, vecPoints[iSize-1], vecPoints[0]);
	if (colData.depth < tMax)
	{
		colData.collisionEdgeStart = vecPoints[iSize-1];
		colData.collisionEdgeEnd = vecPoints[0];
	}

}

//sorting algorithm that needs work.
//If any of the given points share the same X axis then the lesser or greater value
//Y axis is deleted depending on the value of bUpper
void PolygonUtilities::UniqueXAxis(std::list<Vector2> &points, bool bUpper)
{
	std::list<Vector2>::iterator current = points.begin();	
	std::list<Vector2>::iterator testAgainst = points.begin();

	for (current; current != points.end(); current++)
	{	
		testAgainst = points.begin();
		while (testAgainst != points.end())
		{
			if (current == testAgainst)
			{
				testAgainst++;
				continue;
			}

			if (current->x == testAgainst->x)
			{
				if (bUpper)
				{
					if (current->y > testAgainst->y)
					{
						testAgainst = points.erase(testAgainst);
						continue;
					}
				}
				else
				{
					if (current->y < testAgainst->y)
					{
						testAgainst = points.erase(testAgainst);
						continue;
					}
				}
			}

			testAgainst++;
		}	
	}
}

//creates a convex hull from the given points
void PolygonUtilities::CreateConvexHull(const std::list<Vector2> &points, cPolygon &returnHull)
{
	//these lists will hold the sorted data
	std::list<Vector2> upper = points;
	std::list<Vector2> lower = points;

	//sort the list in order of X axis value
	upper.sort(LeftToRight());
	lower.sort(RightToLeft());

	//delete any duplicate X axis points 
	UniqueXAxis(upper, true);
	UniqueXAxis(lower, false);

	//this will hold the upper edge of the convex hull
	std::list<Vector2> upperEdge;

	std::list<Vector2>::iterator currentVert = upper.begin();
	std::list<Vector2>::iterator end = upper.end();
	std::list<Vector2>::iterator v1;
	std::list<Vector2>::iterator v2;

	Vector2 start = *currentVert;
	upperEdge.push_front(start);
	upperEdge.push_front(*++currentVert);
		
	currentVert++;	

	Vector2 newStart;
	int iSize = upper.size();
	//create the upper edge of the hull
	if (iSize > 2)
	{
		do
		{				
			v1 = v2 = upperEdge.begin();
			//if the point is on the right side of the line then create the edge
			if (CalculateWherePointLies(*currentVert, *v1, *++v2))
			{				
				upperEdge.push_front(*currentVert);
				currentVert++;
				newStart = *v1;
			}
			//else if the point is on the left side then this point is outside the current
			//hull and the hull chain is in error so we need to go back
			else
			{
				newStart = *v2;
				upperEdge.erase(v1);

				if (upperEdge.size() == 1)
				{
					upperEdge.push_front(*currentVert);
					currentVert++;
				}
			}

		

		}while(currentVert != end);
	}

	//this will hold the lower half of the covex hull
	std::list<Vector2> lowerEdge;

	currentVert = lower.begin();
	end = lower.end();

	start = *currentVert;
	lowerEdge.push_front(start);
	lowerEdge.push_front(*++currentVert);
		
	currentVert++;
	
	iSize = lower.size();
	//create the lower edge of the hull
	if (iSize > 2)
	{
		do
		{	
			v1 = v2 = lowerEdge.begin();
			//if the point is on the right side of the line then create the edge
			if (CalculateWherePointLies(*currentVert, *v1, *++v2))
			{
				
				lowerEdge.push_front(*currentVert);
				currentVert++;
				newStart = *v1;
			}
			//else if the point is on the left side then this point is outside the current
			//hull and the hull chain is in error so we need to go back
			else
			{
				newStart = *v2;
				lowerEdge.erase(v1);

				if (lowerEdge.size() == 1)
				{
					lowerEdge.push_front(*currentVert);
					currentVert++;
				}
					
			}
		}while(currentVert != end);
	}

	currentVert = upperEdge.begin(); 
	end = upperEdge.end();
	for (currentVert; currentVert != end; currentVert++)
	{
		returnHull.AddVert(*currentVert);
	}
	//since the return verts are stored in a vector we need to
	//swap the verts over for both the upper and lower halves of the hull
	currentVert = lowerEdge.begin(); 
	end = lowerEdge.end();
	for (currentVert; currentVert != end; currentVert++)
	{
		returnHull.AddVert(*currentVert);
	}
}