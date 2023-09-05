#include "Vector2.h"

struct LeftToRight
{
	bool operator()(const Vector2 &p1, const Vector2 &p2)
	{
		return p1.x < p2.x;
	}
};

struct RightToLeft
{
	bool operator()(const Vector2 &p1, const Vector2 &p2)
	{
		return p1.x > p2.x;
	}
};

struct SameXComponent_ChooseGreaterYComponent
{
	bool operator()(const Vector2 &p1, const Vector2 &p2)
	{
		if (p1.x == p2.x)
			return p1.y <= p2.y;
		else
			return false;
	}
};

struct SameXComponent_ChooseLowerYComponent
{
	bool operator()(const Vector2 &p1, const Vector2 &p2)
	{
		if (p1.x == p2.x)
			return p1.y >= p2.y;
		else
			return false;
	}
};