#include "Bom.h"

using namespace Tmpl8;				// to use template classes
using namespace glm;				// to use glm vector stuff

Bom::Bom()
{
	width = image->GetWidth();
	height = image->GetWidth();
}

Bom::~Bom()
{
}

void Bom::Draw(RECT t, Surface* drawPane)
{
	if (!isHit)
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
	}
	else
	{
		for (double i = 0; i < PI * 2; i += 0.01)
		{
			double aa = radius * std::cos((i));
			double bb = radius * std::sin((i));
			double a = 0 + position.x - t.left;
			double b = 0 + position.y - t.top;

			drawPane->Plot(aa + a, bb + b, 0x990000);
		}
	}
}

void Bom::Update()
{
	if (isHit)
	{
		if (radius < radiusCap)
		{
			radius += radiusStep;
		}
		else
		{
			isKill = true;
		}

		if (blastspeed.x > 0 && blastspeed.y > 0)
		{
			blastspeed -= blastDecrease;
		}
		else
		{
			//isKill = true;
			blastspeed = glm::vec2(0, 0);
		}
	}
}