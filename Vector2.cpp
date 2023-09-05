#include "Vector2.h"

Vector2 Vector2::Normalise()const
{
	float length;

	length = this->GetMagnitude();
	return Vector2(x / length, y / length);
}

Vector2 Vector2::LinearInt(Vector2 &object2, float dist)
{
	float inv = 1.0 - dist;

	return Vector2 ((object2.x * inv) + (this->x * dist), (object2.y * inv) + (this->y * dist));
}

Vector2::~Vector2()
{

}
