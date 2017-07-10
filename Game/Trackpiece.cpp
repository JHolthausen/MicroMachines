#include "Trackpiece.h"

using namespace Tmpl8;				// to use template classes
using namespace glm;				// to use glm vector stuff

Trackpiece::Trackpiece(int tracknumber)
{
	this->tracknumber = tracknumber;

	std::vector<glm::vec2> p;
	startPositions.push_back(p);


	std::vector<glm::vec2> p1;
	startPositions.push_back(p);


	std::vector<glm::vec2> p2;
	startPositions.push_back(p2);


	std::vector<glm::vec2> p3;
	startPositions.push_back(p3);
}

Trackpiece::~Trackpiece()
{
}

void Trackpiece::Setpoints(glm::vec2 inPoint, glm::vec2 outPoint)
{
	//this->points = points;
}

void Trackpiece::Rotate()
{
	index++;
	if (index == images.size())
	{
		index = 0;
	}

	image = images[index];
}

//glm::vec2 temp;
//float m = -(PI / 20);
//for (int i = 0; i < linesPoints.size(); i++)
//{
//	temp.x = linesPoints[i].x*cos(m) + linesPoints[i].y*sin(m);
//	temp.y = -linesPoints[i].x*sin(m) + linesPoints[i].y*cos(m);
//
//	linesPoints[i] = temp;
//}
//
//velocity = glm::normalize(linesPoints[0]); // first point is the point hes facing