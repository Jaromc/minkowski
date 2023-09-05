class Vector2
{
	friend Vector2 operator+( const Vector2 &v1, const Vector2 &v2 );
	friend Vector2 operator+( const Vector2 &Vector, const float value );
	friend Vector2 operator-( const Vector2 &v1, const Vector2 &v2 );
	friend Vector2 operator*( const Vector2 &v1, const Vector2 &v2 );
	friend Vector2 operator*( const float value, const Vector2 &Vector );
	friend Vector2 operator/( const Vector2 &v1, const Vector2 &v2 );

protected:
	
public:
	Vector2();
	~Vector2();
	Vector2(float xValue, float yValue);
	float getY() const;
	float getX() const;
	float GetMagnitude()const;
	float GetMagnitudeSquared();
	float DotProduct(const Vector2 &v)const;
	float CrossProduct (const Vector2 &v)const;
	Vector2 LinearInt(Vector2 &object2, float dist);
	Vector2 Projection(const Vector2 &n)const; //n = line to project on
	Vector2 DistVector2(const Vector2 &size, float length)const;
	void setX(float x);
	void setY(float y);
	Vector2 Normalise()const;
	float x;
	float y;


	Vector2& operator+=( const Vector2 &v );
	const Vector2 operator/(const float s)const;
	Vector2& operator-=(const Vector2 &v);
	Vector2& operator=(const Vector2 &v);
	Vector2 operator-() const;
	Vector2& operator*=(const float s);
	const Vector2 operator*(const float s)const;
	float& operator[]( const int axis );
	bool operator==(const Vector2 &v)const;

};

inline Vector2 Vector2::Projection(const Vector2 &n) const
{
	Vector2 p;
	p.x = (this->DotProduct(n) / ((n.x * n.x) + (n.y * n.y))) * n.x;
	p.y = (this->DotProduct(n) / ((n.x * n.x) + (n.y * n.y))) * n.y;
	return p;
}

inline float Vector2::CrossProduct(const Vector2 &v)const
{
	return (x*v.y) - (y*v.x); 
}

inline Vector2::Vector2()
{
	x = y = 0;
}

inline Vector2::Vector2(float xValue, float yValue)
{
	x = xValue;
	y = yValue;
}

inline float Vector2::getY() const
{
	return y;
}

inline float Vector2::getX() const
{
	return x;
}

inline float Vector2::DotProduct(const Vector2 &v)const
{	
	return ((v.x * this->x) + (v.y * this->y));
}

inline float Vector2::GetMagnitude()const
{
	float length;
	return (length = sqrt( ( x*x ) + ( y*y )));
}

inline float Vector2::GetMagnitudeSquared()
{
	//float lengthSquared;
	//return (lengthSquared = pow( x, 2 ) + pow( y, 2 ));
}

inline void Vector2::setX(float x)
{
	this->x = x;
}

inline void Vector2::setY(float y)
{
	this->y = y;
}

inline Vector2 Vector2::operator-() const
{
	return Vector2(-x,-y);
}

inline Vector2 operator+( const Vector2 &v1, const Vector2 &v2 )
{
	return Vector2( v1.x + v2.x, v1.y + v2.y );
}

inline const Vector2 Vector2::operator *(const float s)const
{
	return Vector2 (x*s, y*s); 
}

inline const Vector2 Vector2::operator/(const float s)const
{
	float d = 1/s;
	return Vector2(x*d, y*d);
}

inline Vector2& Vector2::operator *=(const float s)
{
	x *= s;
	y *= s;
}

inline Vector2& Vector2::operator -=(const Vector2 &v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

inline Vector2& Vector2::operator+=(  const Vector2 &v )
{
	this->x += v.x;
	this->y += v.y;
	return *this;
}

inline bool Vector2::operator ==(const Vector2 &v)const
{
	return (v.x == x && v.y == y);
}

inline Vector2& Vector2::operator=( const Vector2 &v)
{
	x = v.x;
	y = v.y;
	return *this;
}

inline float& Vector2::operator[]( const int axis )
{
	return *((&x)+axis);
}

inline Vector2 operator-( const Vector2 &v1, const Vector2 &v2 )
{
	return Vector2( v1.x - v2.x, v1.y - v2.y );
}

inline Vector2 operator*( const Vector2 &v1, const Vector2 &v2 )
{
	return Vector2( v1.x * v2.x, v1.y * v2.y );
}

inline Vector2 operator/( const Vector2 &v1, const Vector2 &v2 )
{
	return Vector2( v1.x / v2.x, v1.y / v2.y );
}

inline Vector2 operator+( const Vector2 &v, const float value )
{
	return Vector2(v.x + value, v.y + value);
}

inline Vector2 operator*( const float value, const Vector2 &v )
{
	return Vector2(v.x * value, v.y * value);
}

