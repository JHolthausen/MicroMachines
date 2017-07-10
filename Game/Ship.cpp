#include "Ship.h"
#include <math.h>

using namespace Tmpl8;				// to use template classes
using namespace glm;				// to use glm vector stuff

Ship::Ship(Surface* screen, Surface* world, glm::vec2 position)
{
	this->screen = screen;
	this->position = position;
	this->world = world;

	//create linespoints for ship
	linesPoints.push_back(glm::vec2(30.0, 0.0)); // the first point is the nose
	linesPoints.push_back(glm::vec2(20.0, 10));
	linesPoints.push_back(glm::vec2(-20.0, 10));
	linesPoints.push_back(glm::vec2(-20.0, -10));
	linesPoints.push_back(glm::vec2(20.0, -10));
}

Ship::~Ship()
{
	delete image;
}

Ship::Ship()
{
	linesPoints.push_back(glm::vec2(30.0, 0.0)); // the first point is the nose
	linesPoints.push_back(glm::vec2(20.0, 10));
	linesPoints.push_back(glm::vec2(-20.0, 10));
	linesPoints.push_back(glm::vec2(-20.0, -10));
	linesPoints.push_back(glm::vec2(20.0, -10));

	/*PlayerNumber = 1;
	if (playernumber == 1){ color = 0xff0000; }
	if (playernumber == 2){ color = 0x00ff00; }
	if (playernumber == 3){ color = 0x0ff000; }
	if (playernumber == 4){ color = 0x000ff0; }*/

	//	PlayerNumber++;

	rotateLeft(0);
}

void Ship::Draw(Surface* drawpane, glm::vec2 pos)
{
	glm::vec2 drawPoint = pos;

	//for (int i = 0; i < linesPoints.size(); i++)
	//{
	//	if (i != linesPoints.size() - 1)
	//	{
	//		drawpane->Line(linesPoints[i].x + drawPoint.x,
	//			linesPoints[i].y + drawPoint.y,
	//			linesPoints[i + 1].x + drawPoint.x,
	//			linesPoints[i + 1].y + drawPoint.y,
	//			color);
	//	}
	//	else
	//	{
	//		drawpane->Line(linesPoints[i].x + drawPoint.x,
	//			linesPoints[i].y + drawPoint.y,
	//			linesPoints[0].x + drawPoint.x,
	//			linesPoints[0].y + drawPoint.y,
	//			color);
	//		break;
	//	}
	//}

	//image->CopyTo(drawpane, drawPoint.x - image->GetWidth() / 2, drawPoint.y - image->GetHeight() / 2);
	//

	//drawImage->CopyTo(drawpane, drawPoint.x - drawImage->GetWidth() / 2, drawPoint.y - drawImage->GetHeight() / 2);
	s = new Sprite(drawImage, 1);
	s->Draw(drawPoint.x - drawImage->GetWidth() / 2, drawPoint.y - drawImage->GetHeight() / 2, drawpane);

	//s->Draw(drawPoint.x - image->GetWidth() / 2, drawPoint.y - image->GetHeight() / 2, drawpane);
	//delete s;
	/*
		for (double i = 0; i < PI * 2; i += 0.01)
		{
		double a = radius * std::cos((i));
		double b = radius * std::sin((i));

		drawpane->Plot(drawPoint.x + a, drawPoint.y + b, 0x990000);
		}*/

	//drawpane->Bar(drawPoint.x + velocity.x * 4, drawPoint.y + velocity.y * 4, drawPoint.x + velocity.x * 4 + 2, drawPoint.y + velocity.y * 4 + 2, 0x990000);

	//drawpane->Bar(drawPoint.x, drawPoint.y, drawPoint.x + 2, drawPoint.y + 2, color);
	//drawpane->Plot(drawPoint.x, drawPoint.y, color);
}
void Ship::Update(std::vector<glm::vec2>route)//, Surface* world)
{
	if (!isAi)
	{
		HandleInput();
	}
	else
	{
		HandleAi(route);
	}
	glm::vec2 tpos = position += velocity * speed;

	Projection(route);// , world);

	//little cheat -> plyscreenwidth 1000 and height 800

	/*if (tpos.x <= 20 || tpos.x >= 1000 - 20)
	{
	velocity.x = 0;
	}
	if (tpos.y <= 20|| tpos.y >= 800 - 20)
	{
	velocity.y = 0;
	}
	*/
	position += velocity * speed;

	if (speed.x > 0 &&
		speed.y > 0)
	{
		speed.x -= 0.01;
		speed.y -= 0.01;
	}
	else //its in reveerse or "bouncing back
	{
		speed.x += 0.01;
		speed.y += 0.01;
	}

	//DrawToWorld();
}

void Ship::Update()
{
	HandleInput();

	position += velocity * speed;
	position += velocity * speed;

	if (speed.x > 0 &&
		speed.y > 0)
	{
		speed -= speedDecrease;
	}
	else //its in reveerse or "bouncing back
	{
		speed += speedDecrease;
	}
}
//draw to world surface// for minimap
void Ship::DrawToWorld()
{
	glm::vec2 drawPoint = position;

	for (int i = 0; i < linesPoints.size(); i++)
	{
		if (i != linesPoints.size() - 1)
		{
			world->Line(linesPoints[i].x + drawPoint.x,
				linesPoints[i].y + drawPoint.y,
				linesPoints[i + 1].x + drawPoint.x,
				linesPoints[i + 1].y + drawPoint.y,
				color);
		}
		else
		{
			world->Line(linesPoints[i].x + drawPoint.x,
				linesPoints[i].y + drawPoint.y,
				linesPoints[0].x + drawPoint.x,
				linesPoints[0].y + drawPoint.y,
				color);
			break;
		}
	}
}
void Ship::RotateRight()
{
	glm::vec2 temp;
	float m = -(PI / 20);
	for (int i = 0; i < linesPoints.size(); i++)
	{
		temp.x = linesPoints[i].x*cos(m) + linesPoints[i].y*sin(m);
		temp.y = -linesPoints[i].x*sin(m) + linesPoints[i].y*cos(m);

		linesPoints[i] = temp;
	}

	velocity = glm::normalize(linesPoints[0]); // first point is the point hes facing
}
void Ship::rotateLeft()
{
	glm::vec2 temp;
	float m = PI / 20;
	for (int i = 0; i < linesPoints.size(); i++)
	{
		temp.x = linesPoints[i].x*cos(m) + linesPoints[i].y*sin(m);
		temp.y = -linesPoints[i].x*sin(m) + linesPoints[i].y*cos(m);

		linesPoints[i] = temp;
	}

	velocity = glm::normalize(linesPoints[0]); // first point is the point hes facing
}

void Ship::RotateRight(int angle)
{
	ang -= angle;

	//step++;
	float m = PI * 2 / 360 * ang;
	drawImage->Clear(0);

	//imageTest.GetWidth() / 2;
	//imageTest.GetHeight() / 2;

	for (int i = 0; i < image->GetHeight(); i++)
	{
		for (int j = 0; j < image->GetWidth(); j++)
		{
			glm::vec2 pixelPos(-(image->GetWidth() / 2) + j, -(image->GetHeight() / 2) + i);
			glm::vec2 temp = pixelPos;

			temp.x = pixelPos.x*cos(m) + pixelPos.y*sin(m);
			temp.y = -pixelPos.x*sin(m) + pixelPos.y*cos(m);

			image->CopyTo(imag, 0 - j, 0 - i);

			imag->CopyTo(drawImage, temp.x + drawImage->GetWidth() / 2, temp.y + drawImage->GetHeight() / 2);
		}
	}

	if (!isAi){
		glm::vec2 temp;
		linesPoints[0] = glm::vec2(30, 0);
		temp.x = linesPoints[0].x*cos(m) + linesPoints[0].y*sin(m);
		temp.y = -linesPoints[0].x*sin(m) + linesPoints[0].y*cos(m);

		linesPoints[0] = temp;

		velocity = glm::normalize(linesPoints[0]);
	}
}

void Ship::rotateLeft(int angle)
{
	ang += angle;
	//step++;
	float m = PI * 2 / 360 * ang;
	drawImage->Clear(0);

	//imageTest.GetWidth() / 2;
	//imageTest.GetHeight() / 2;

	for (int i = 0; i < image->GetHeight(); i++)
	{
		for (int j = 0; j < image->GetWidth(); j++)
		{
			glm::vec2 pixelPos(-(image->GetWidth() / 2) + j, -(image->GetHeight() / 2) + i);
			glm::vec2 temp = pixelPos;

			temp.x = pixelPos.x*cos(m) + pixelPos.y*sin(m);
			temp.y = -pixelPos.x*sin(m) + pixelPos.y*cos(m);

			image->CopyTo(imag, 0 - j, 0 - i);

			imag->CopyTo(drawImage, temp.x + drawImage->GetWidth() / 2, temp.y + drawImage->GetHeight() / 2);
		}
	}

	if (!isAi){
		glm::vec2 temp;
		linesPoints[0] = glm::vec2(30, 0);
		temp.x = linesPoints[0].x*cos(m) + linesPoints[0].y*sin(m);
		temp.y = -linesPoints[0].x*sin(m) + linesPoints[0].y*cos(m);

		linesPoints[0] = temp;
	}

	//delete s;
	//s = new Sprite(drawImage, 1);

	//velocity = glm::normalize(linesPoints[0]);
}

void Ship::MoveForeWard()
{
	//build up speed and cap it
	if (speed.x < speedCap.x &&
		speed.y < speedCap.y)
	{
		speed += speedIncrease;
	}

	velocity = glm::normalize(linesPoints[0]); // first point is the point hes facing
}

RECT Ship::GetRect()
{
	RECT r;
	r.top = position.y - 10;
	r.left = position.x - 20;
	r.right = position.x + 20;
	r.bottom = position.y + 10;
	return r;
}

void Ship::SetKeys(std::string lk, std::string uk, std::string rk)
{
	leftKey = lk;
	upKey = uk;
	rightKey = rk;
}

void Ship::HandleInput()
{
	if (il.IsKeyPressed(leftKey))
	{
		rotateLeft(5);
	}
	if (il.IsKeyPressed(upKey))
	{
		MoveForeWard();
	}
	if (il.IsKeyPressed(rightKey))
	{
		RotateRight(5);
	}
}

void Ship::HandleAi(std::vector<glm::vec2>route)
{
	glm::vec2 temp = destination - position;

	float d = std::sqrt(pow(temp.x, 2) + pow(temp.y, 2));

	velocity = temp / d;

	int range = 10;

	temp = position - velocity;

	float a = destination.y - velocity.y - temp.y;
	float b = destination.x - velocity.x - temp.x;
	float angle = std::atan2(a, b);

	double xx = angle;// / (PI * 2) * 360;

	if (xx < PI)
		AiRotateRight(xx);
	else
		AiRotateLeft(xx);

	if (position.x > destination.x - range &&
		position.y > destination.y - range &&
		position.x < destination.x + range &&
		position.y < destination.y + range)
	{
		//routeindex++;
		//rotate to new point

		if (routeindex == route.size())
		{
			routeindex = 0;
		}

		SetDest(route);

		//dest = glm::vec2(route[routeindex].x + rand() % 100 - 50, route[routeindex].y + rand() % 100 - 50) - position
	}

	//build up speed and cap it
	if (speed.x < speedCap.x &&
		speed.y < speedCap.y)
	{
		speed += speedIncrease;
	}
}

void Ship::AiRotateRight(double angle)
{
	float m = -angle;// ang += angle;;
	drawImage->Clear(0);

	//imageTest.GetWidth() / 2;
	//imageTest.GetHeight() / 2;

	for (int i = 0; i < image->GetHeight(); i++)
	{
		for (int j = 0; j < image->GetWidth(); j++)
		{
			glm::vec2 pixelPos(-(image->GetWidth() / 2) + j, -(image->GetHeight() / 2) + i);
			glm::vec2 temp = pixelPos;

			temp.x = pixelPos.x*cos(m) + pixelPos.y*sin(m);
			temp.y = -pixelPos.x*sin(m) + pixelPos.y*cos(m);

			image->CopyTo(imag, 0 - j, 0 - i);

			imag->CopyTo(drawImage, temp.x + drawImage->GetWidth() / 2, temp.y + drawImage->GetHeight() / 2);
		}
	}
}
void Ship::AiRotateLeft(double angle)
{
	float m = angle;// ang += angle;;
	drawImage->Clear(0);

	//imageTest.GetWidth() / 2;
	//imageTest.GetHeight() / 2;

	for (int i = 0; i < image->GetHeight(); i++)
	{
		for (int j = 0; j < image->GetWidth(); j++)
		{
			glm::vec2 pixelPos(-(image->GetWidth() / 2) + j, -(image->GetHeight() / 2) + i);
			glm::vec2 temp = pixelPos;

			temp.x = pixelPos.x*cos(m) + pixelPos.y*sin(m);
			temp.y = -pixelPos.x*sin(m) + pixelPos.y*cos(m);

			image->CopyTo(imag, 0 - j, 0 - i);

			imag->CopyTo(drawImage, temp.x + drawImage->GetWidth() / 2, temp.y + drawImage->GetHeight() / 2);
		}
	}
}

void Ship::SetDest(std::vector<glm::vec2>route)
{
	glm::vec2 tmp = route[routepoint];
	int range = 280;
	int minus = 140;
	destination = glm::vec2(tmp.x + rand() % range - minus, tmp.y + rand() % range - minus);
}

void Ship::Projection(std::vector<glm::vec2>route)// , Surface* world)
{
	//calculate
	glm::vec2 projection;;
	double a;
	double b;
	double c;
	double d;
	glm::vec2 subtrack;

	if (routepoint == route.size() || routepoint == 0)
	{
		subtrack = route[route.size() - 1];
		routepoint = 0;
	}
	else
	{
		subtrack = route[routepoint - 1];
	}

	glm::vec2 point = position - subtrack;
	glm::vec2 line = route[routepoint] - subtrack;

	a = (point.x * line.x) + (point.y *line.y);
	b = (line.x * line.x) + (line.y *line.y);
	c = line.x*a / b;
	d = line.y*a / b;

	projection = glm::vec2(c, d);

	a = std::sqrt(pow(projection.x, 2) + pow(projection.y, 2));
	b = std::sqrt(pow(line.x, 2) + pow(line.y, 2));
	//Pixel color = a<b ? 0x00ff00 : 0xFF0000;
	Pixel color = 0xFF0000;

	if (a > b - 20 ||
		projection.x > line.x - 300 &&
		projection.y > line.y - 300 &&
		projection.x < line.x + 300 &&
		projection.y < line.y + 300
		)
	{
		routepoint++;

		if (routepoint == 1)
		{
			if (firstfinish)
			{
				firstfinish = false;
			}
			else
			{
				laps++;
			}
		}
	}

	projection += subtrack;

	glm::vec2 z = (projection - subtrack) - (position - subtrack);

	b = std::sqrt(pow(z.x, 2) + pow(z.y, 2));

	/*if (b > 150)
	{
	speed -= glm::vec2(0.3, 0.3);
	}*/
	color = b < 150 ? 0x00ff00 : 0xFF0000;

	//visual

	/*world->Bar(projection.x, projection.y, projection.x + 10, projection.y + 10, color);
	world->Line(projection.x, projection.y, position.x, position.y, color);
	*/
	/*world->Bar(point.x, point.y, point.x + 2, point.y + 2, 0xffffff);
	world->Line(0, 0, point.x, point.y, 0xffffff);

	world->Bar(line.x, line.y, line.x + 2, line.y + 2, 0x0000ff);
	world->Line(0, 0, line.x, line.y, 0x0000ff);*/
}