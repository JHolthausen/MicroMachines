#pragma once
#include "template.h"
#include "surface.h"

namespace Tmpl8 {
	class Game_Object
	{
	public:
		Game_Object(){};
		~Game_Object(){};


		virtual void Draw(RECT t, Surface* drawPane) = 0;
		virtual void Update() = 0;


		glm::vec2 position;//always the center of the object
		glm::vec2 velocity;
		glm::vec2 speed;

		double width;
		double height;

	};

}