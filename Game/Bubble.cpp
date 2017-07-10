#include "Bubble.h"

using namespace Tmpl8;				// to use template classes
using namespace glm;				// to use glm vector stuff

Bubble::Bubble()
{
	width = image->GetWidth();
	height = image->GetWidth();
}

Bubble::~Bubble()
{
	//delete image;
	//delete c;
}

void Bubble::setImage(Surface* s)
{
	delete image;
	image = s;
	radius = image->GetWidth() / 2;

	width = image->GetWidth();
	height = image->GetWidth();
}

void Bubble::Draw(RECT t, Surface* drawPane)
{
	double a = 0 + position.x - t.left - (width / 2);
	double b = 0 + position.y - t.top - (height / 2);

	RECT r{ position.x - width / 2,
		position.y - height / 2,
		position.x + width / 2,
		position.y + height / 2 };

	if (CheckRECTCollision(t, r))
	{
		//s->Draw(a, b, drawPane);
		image->CopyTo(drawPane, a, b);
	}

	/*for (double i = 0; i < PI * 2; i += 0.01)
	{
	double aa = radius * std::cos((i));
	double bb = radius * std::sin((i));
	a = 0 + position.x - t.left ;
	b = 0 + position.y - t.top;

	drawPane->Plot(aa + a, bb + b, 0x990000);
	}*/
}

void Bubble::Update()
{
	position += velocity *speed;

	if (speed.x > 0 &&
		speed.y > 0)
	{
		speed.x -= 0.01;
		speed.y -= 0.01;
	}
}