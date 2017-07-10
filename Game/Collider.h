#pragma once

#include "template.h"
#include "surface.h"

namespace Tmpl8 {
	class Collider
	{
	public:
		Collider();
		~Collider();


		bool CheckCircleCollision(double radius_obj1, glm::vec2 pos_obj1, double radius_obj2, glm::vec2 pos_obj2);
		bool CheckRECTCollision(RECT a, RECT b);


	};

}