#pragma once

#include "template.h"
#include "surface.h"
#include <vector>
#include <string>
#include "InputListener.h"
#include "Collider.h"

namespace Tmpl8 {
	class Ship : public Collider
	{
	public:
		Ship(Surface* screen, Surface* world, glm::vec2 position);
		Ship();
		~Ship();

		void Draw(Surface* drawpane, glm::vec2 pos);
		void Update(std::vector<glm::vec2>route);//, Surface* world);
		void RotateRight();
		void rotateLeft();

		void RotateRight(int angle);
		void rotateLeft(int angle);
		void AiRotateRight(double angle);
		void AiRotateLeft(double angle);

		void MoveForeWard();
		void HandleInput();
		void DrawToWorld();
		RECT GetRect();
		void SetKeys(std::string lk, std::string uk, std::string rk);
		void HandleAi(std::vector<glm::vec2>route);
		void Update();
		void Projection(std::vector<glm::vec2>route);// , Surface* world);
		void SetDest(std::vector<glm::vec2>route);

		glm::vec2 position;
		glm::vec2 velocity = glm::vec2(0.0f, 0.0f);
		glm::vec2 speed = glm::vec2(0.0f, 0.0f);
		glm::vec2 dest = glm::vec2(3.0f, 3.0f);
		glm::vec2 speedCap = glm::vec2(5, 5);
		glm::vec2 speedDecrease = glm::vec2(0.01, 0.01);
		glm::vec2 speedIncrease = glm::vec2(0.1, 0.1);
		glm::vec2 destination = glm::vec2(0.1, 0.1);

		Surface* screen;
		Surface* world;

		Surface* imag = new Surface(1, 1);

		Pixel color = 0xffffff;

		std::vector<glm::vec2> linesPoints;
		Surface* image = new Surface("assets/boat3.png");
		Surface* drawImage = new Surface(image->GetWidth() * 2, image->GetHeight() * 2);
		Sprite* s = new Sprite(image, 1);

		std::vector<glm::vec2> trail;

		float ang = 0;

		bool isKill = false;
		int PlayerNumber = 1;

		std::string leftKey = "";
		std::string upKey = "";
		std::string rightKey = "";

		InputListener il;

		bool isAi = false;
		int routeindex = 0;
		int routepoint = 0;

		int laps = 1;
		bool firstfinish = true;
		bool isfinished = false;

		int radius = image->GetWidth() / 2;
	};
}