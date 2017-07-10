#include "Collider.h"


using namespace Tmpl8;				// to use template classes
using namespace glm;				// to use glm vector stuff

Collider::Collider()
{
}


Collider::~Collider()
{
}


bool Collider::CheckCircleCollision(double radius_obj1, glm::vec2 pos_obj1, double radius_obj2, glm::vec2 pos_obj2)
{
	glm::vec2 tmp = pos_obj1 - pos_obj2;
	double d = std::sqrt(pow(tmp.x, 2) + pow(tmp.y, 2));
	double i = radius_obj1 + radius_obj2;

	return d < i ? true : false;
}


bool Collider::CheckRECTCollision(RECT RectA, RECT RectB)
{
	if (RectA.left < RectB.right && RectA.right > RectB.left &&
		RectA.top < RectB.bottom && RectA.bottom > RectB.top)
	{
		return true;
	}
	return false;

}