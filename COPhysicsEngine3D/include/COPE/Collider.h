#include <vector>
#include <COPE/Math.h>

//#define COLLIDING_WITH && // man... (c1 COLLIDING_WITH c2) is a interesting syntax.

namespace COPE
{
	class CircularCollider
	{
		private:
			vec3f center; Point diameter;
		public:
			CircularCollider(vec3f,Point);
			CircularCollider(Point);

			bool isColliding(CircularCollider);
			CircularCollider operator+(vec3f);
			CircularCollider operator-(vec3f);

			friend bool operator&&(CircularCollider,CircularCollider);

	};
	bool operator&&(CircularCollider,CircularCollider);

	class AABBCollider
	{
	private:
		vec3f a,b;
	public:
		AABBCollider(std::vector<vec3f> vertices);
		AABBCollider(vec3f a, vec3f b);
		bool isColliding(AABBCollider);

		AABBCollider operator+(vec3f);
		AABBCollider operator-(vec3f);

		friend bool operator&&(AABBCollider,AABBCollider);
	};
	bool operator&&(AABBCollider,AABBCollider);

	class Collider
	{
	private:
		AABBCollider FastCollider;
	public:
		bool fastControlCollider(AABBCollider);
		bool isColliding(Collider);

	};
}