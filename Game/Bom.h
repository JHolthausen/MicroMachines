#pragma once
#include "template.h"
#include "surface.h"

#include "Game_Object.h"
#include "Collider.h"

namespace Tmpl8 {
	class Bom : public Collider, public Game_Object
	{
	public:
		Bom();
		~Bom();

		void Draw(RECT t, Surface* drawPane);
		void Update();
		void setImage(Surface* s);

		Surface* image = new Surface("assets/ball.png");
		//Sprite* s = new Sprite(image, 1);

		double radius = image->GetWidth() / 2; // assume width and height of image are equal
		bool isHit = false;
		double radiusCap = 100;
		double radiusStep = 1;
		glm::vec2 blastspeed = glm::vec2(8, 8);
		glm::vec2 blastDecrease = glm::vec2(0.2, 0.2);
		bool isKill = false;
	};
}
