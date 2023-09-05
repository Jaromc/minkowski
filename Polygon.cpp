#include "Polygon.h"

cPolygon::cPolygon(int iNumVerts, const Vector2 &vPosition)
{
	m_vPosition = vPosition;
	m_iNumVerts = iNumVerts;
	m_mRotationMatrix.Identity();
	m_mRotationMatrix.SetRotation(1.5f);
	m_fOrientation = 0.0f;


	TransformVerts();

}
//transforms the verticies into world space
void cPolygon::TransformVerts()
{
	m_vecVerticies.clear();

	float fTheta = 0;

    for (int i = 0; i < m_iNumVerts; i++)
    {
        //get the position in the sphere of the vert
        fTheta = ((3.14f * 2.0f) / m_iNumVerts);
        fTheta *= i;

		Vector2 temp((float)(RADIUS * cosf(fTheta)), (float)(RADIUS * sinf(fTheta)));

		//transform and add the new vertx to the list
		m_vecVerticies.push_back((temp * m_mRotationMatrix) + m_vPosition);
    }

	
}
//update the polygon position
void cPolygon::Update()
{
	TransformVerts();
}
//render the polygon
void cPolygon::Render()
{
	glColor4f( m_sColour.r, m_sColour.g, m_sColour.b, m_sColour.a );
	glBegin(GL_LINES);

	for (int i = 0; i < m_vecVerticies.size(); i++)
	{		
		glVertex2f(m_vecVerticies[i].x, m_vecVerticies[i].y);	

		if ( i+1 == m_vecVerticies.size())
		{
			glVertex2f(m_vecVerticies[0].x, m_vecVerticies[0].y);
		}
		else
		{
			glVertex2f(m_vecVerticies[i+1].x, m_vecVerticies[i+1].y);
		}		
	}

	glEnd();
}