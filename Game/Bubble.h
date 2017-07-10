#pragma once

#include "template.h"
#include "surface.h"

#include "Game_Object.h"
#include "Collider.h"

namespace Tmpl8 {
	class Bubble : public Game_Object, public Collider
	{
	public:
		Bubble();
		~Bubble();

		void Draw(RECT t, Surface* drawPane);
		void Update();
		void setImage(Surface* s);

		Surface* image = new Surface("assets/bubble2.png");
		//Sprite* s = new Sprite(image, 1);

		double radius = image->GetWidth() / 2; // assume width and height of image are equal
		bool isWall = false;

		//Collider* c = new Collider();
	};
}