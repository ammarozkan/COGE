#include <COPE/Math.h>

namespace COPE
{
	vec3f::vec3f() { x = y = z = 0.0f; }

	vec3f::vec3f(Point x, Point y, Point z) { this->x = x; this->y = y; this->z = z; }

	vec3f::vec3f(vec2f v, Point z) { this->x = v.x; this->y = v.y; this->z = z; }

	vec3f::vec3f(Point x, vec2f v) { this->x = x; this->y = v.x; this->z = v.y; }

	vec3f& vec3f::operator=(vec3f& v)
	{
		x = v.x; y = v.y; z = v.z;
		return *this;
	}

	vec3f& vec3f::operator+=(vec3f& v)
	{
		x += v.x; y += v.y; z += v.z;
		return *this;
	}

	vec3f& vec3f::operator-=(vec3f& v)
	{
		x -= v.x; y -= v.y; z -= v.z;
		return *this;
	}
	
	vec3f operator+(vec3f v1,vec3f v2)
	{
		return {v1.x+v2.x, v1.y+v2.y, v1.z+v2.z};
	}

	vec3f operator-(vec3f v1,vec3f v2)
	{
		return {v1.x-v2.x, v1.y-v2.y, v1.z-v2.z};
	}
}