#include "Vector2.h"
#include "Matrix3.h"
#include <vector>

//radius of a polygon
#define RADIUS 50.f

//holds collision information
struct CollisionData
{
	Vector2 collisionEdgeStart;
	Vector2 collisionEdgeEnd;
	Vector2 collisionNormal;	
	Vector2 collisionPoint;
	float depth;
};

//holds colour information
struct COLOUR
{
	COLOUR()
	{
		r = g = b = a = 1.0f;
	}
	float r;
	float g;
	float b;
	float a;
};

class cPolygon
{
private:

	//verticies that define this polygon
	std::vector<Vector2> m_vecVerticies;
	//number of vertices
	int m_iNumVerts;
	//rotation matrix
	Matrix3 m_mRotationMatrix;
	//orientation of the polygon
	float m_fOrientation;
	//polygon center
	Vector2 m_vPosition;
	//colour of this polygon
	COLOUR m_sColour;

	//transforms the verticies into world space
	void TransformVerts();

public:
	cPolygon():m_iNumVerts(-1),
				m_fOrientation(0.f){}
	cPolygon(int iNumPoints, const Vector2 &vPosition);
	//update the polygon position
	void Update();
	//render the polygon
	void Render();
	//clears the vertex list
	void ClearVerts(){m_vecVerticies.clear();}
	//increase the number of verts in this polygon by 1
	void IncreaseVertCount();
	//decreases the number of verts in this polygon by 1
	void DecreaseVertCount();
	//returns the vertex list
	const std::vector<Vector2>& GetVerts()const{return m_vecVerticies;}
	//sets the vertx list
	void SetVerts(const std::vector<Vector2>& vecNewVerts){m_vecVerticies = vecNewVerts;}
	//adds a vertex to the vertex list
	void AddVert(const Vector2 &vNewVert){m_vecVerticies.push_back(vNewVert);}
	//adds the given value to the current orientation
	void AddRotation(float fRadians);
	//sets the polygon position
	void SetPosition(const Vector2 &vNewPosition){m_vPosition = vNewPosition;}
	//adds the values to the current position
	void AddToPosition(float x, float y){m_vPosition.x += x, m_vPosition.y += y;}
	//sets the polygon colour
	void SetColor(float r, float g, float b);
	//returns the polygon position
	const Vector2& GetPosition()const {return m_vPosition;}
};
//adds the given value to the current orientation
inline void cPolygon::AddRotation(float fRadians)
{
	m_fOrientation += fRadians;
	m_mRotationMatrix.SetRotation(m_fOrientation);
}
//sets the polygon colour
inline void cPolygon::SetColor(float r, float g, float b)
{
	m_sColour.r = r;
	m_sColour.g = g;
	m_sColour.b = b;
}
//increase the number of verts in this polygon by 1
inline void cPolygon::IncreaseVertCount()
{
	//check that we haven'y exceeded to maximum
	//amount of verts
	if (m_iNumVerts < 20)
	{
		m_iNumVerts++;
		TransformVerts();
	}
}
//decreases the number of verts in this polygon by 1
inline void cPolygon::DecreaseVertCount()
{
	//check that we still have a minimun amount of verts
	if (m_iNumVerts > 3)
	{
		m_iNumVerts--;
		TransformVerts();
	}
}
