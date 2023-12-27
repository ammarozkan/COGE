#include <COPE/Types.h>

namespace COPE
{
	struct vec2f
	{
		Point x = 0.0f, y = 0.0f;
	};

	struct vec3f
	{
		Point x,y,z;

		vec3f(Point x, Point y, Point z);
		vec3f(vec2f v, Point z);
		vec3f(Point x, vec2f v);
		vec3f();

		vec3f& operator=(vec3f& v);

		vec3f& operator+=(vec3f& v);
		vec3f& operator-=(vec3f& v);
		friend vec3f operator+(vec3f,vec3f);
		friend vec3f operator-(vec3f,vec3f);
	};

	vec3f operator+(vec3f,vec3f);
	vec3f operator-(vec3f,vec3f);
}