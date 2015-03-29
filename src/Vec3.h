#ifndef VEC3_H
#define VEC3_H

#include "Vec2.h"


template <class T>
class Vec3: public Vec2 <T>
{
public:

	Vec3() : x(0), y(0), z(0) {}
    Vec3(T x, T y, T z) {this->x = x; this->y = y; this->z = z;}
	Vec3 (const Vec3<T>& ref) {this->x = ref.X(); this->y = ref.Y(); this->z = ref.Z();}
	Vec3& operator= (const Vec3<T>& ref) {this->x = ref.X(); this->y = ref.Y(); this->z = ref.Z(); return *this;}

	T Z() const {return z;}
	void setZ(T z) {this->z = z;}

	virtual Vec3& operator+=(const Vec3& rhs)
    {
        this->x += rhs.x;
        this->y += rhs.y;
		this->z += rhs.z;
        return *this;
    }

   virtual Vec3& operator*=(T f)
    {
        this->x *= f;
        this->y *= f;
		this->z *= f;
        return *this;
    }
      virtual Vec3& operator*=(Vec3<T>& f)
    {
        this->x *= f.X();
        this->y *= f.Y();
		this->z *= f.Z();
        return *this;
    }


protected:

T z;

};

template <class T>
Vec3<T> operator+(const Vec3<T>& a, const Vec3<T>& b)
{
    Vec3<T> res = a;
    res += b;
    return res;
}

template <class T>
Vec3<T> operator*(const Vec3<T>&a, T f)
{
    Vec3<T> res = a;
    res *= f;
    return res;
}

template <class T>
bool operator == (const Vec3<T>&a, const Vec3<T>& b)
{
	return ( (a.X()==b.X())&&(a.Y()==b.Y())&&(a.Z()==b.Z()));
}

template <class T>
bool operator != (const Vec3<T>&a, const Vec3<T>& b)
{
	return !(a==b);
}

typedef Vec3<float> Vec3f;
typedef Vec3<int> Vec3i;
typedef Vec3<double> Vec3d;


#endif //VEC3_H