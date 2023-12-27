#include <COPE/Collider.h>
#include <COPE/Macros.h>
#include <cstdlib>

namespace COPE
{
	AABBCollider::AABBCollider(std::vector<vec3f> vs)
	{
		if(vs.size() <= 1) WARN("Should specify some dot's' for a collider.");
		vec3f min, max;
		min = max = vs[0];

		for(std::vector<vec3f>::iterator iter;iter!=vs.end();iter++)
		{
			if((*iter).x < min.x) min.x = (*iter).x;
			if((*iter).y < min.y) min.y = (*iter).y;
			if((*iter).z < min.z) min.z = (*iter).z;

			if((*iter).x > max.x) max.x = (*iter).x;
			if((*iter).y > max.y) max.y = (*iter).y;
			if((*iter).z > max.z) max.z = (*iter).z;
		}
		a = min; b = max;
	}

	AABBCollider::AABBCollider(vec3f a, vec3f b)
	{
		this->a = a; this->b = b;
	}

	AABBCollider AABBCollider::operator+(vec3f v)
	{
		return AABBCollider(this->a + v, this->b + v);
	}

	bool AABBCollider::isColliding(AABBCollider other)
	{
		bool xCase = (this->a.x < other.a.x && this->b.x > other.a.x) || (other.a.x < this->a.x && other.b.x > this->a.x);
		bool yCase = (this->a.y < other.a.y && this->b.y > other.a.y) || (other.a.y < this->a.y && other.b.y > this->a.y);
		bool zCase = (this->a.z < other.a.z && this->b.z > other.a.z) || (other.a.z < this->a.z && other.b.z > this->a.z);
		return xCase && yCase && zCase;
	}


	bool operator&&(AABBCollider c1,AABBCollider c2)
	{
		return c1.isColliding(c2);
	}
}