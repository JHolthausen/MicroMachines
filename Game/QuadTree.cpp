#include "QuadTree.h"

using namespace Tmpl8;				// to use template classes
using namespace glm;				// to use glm vector stuff

QuadTree::QuadTree(RECT treeRECT)
{
	this->treeRECT = treeRECT;

	InnerRECT.top = treeRECT.top + 20;
	InnerRECT.bottom = treeRECT.bottom - 20;
	InnerRECT.left = treeRECT.left + 20;
	InnerRECT.right = treeRECT.right - 20;
}

QuadTree::~QuadTree()
{
	if (!isLeaf){
		delete aa;
		delete ab;
		delete ba;
		delete bb;
	}

	for (int i = 0; i < bubbles.size(); i++)
	{
		delete bubbles[i];
		bubbles.erase(bubbles.begin() + i);
	}
}

void QuadTree::Devide()
{
	isLeaf = false;

	RECT tmp;
	tmp.top = treeRECT.top;
	tmp.bottom = treeRECT.top + ((treeRECT.bottom - treeRECT.top) / 2);
	tmp.left = treeRECT.left;
	tmp.right = treeRECT.left + ((treeRECT.right - treeRECT.left) / 2);

	aa = new QuadTree(tmp);
	aa->branchNr = branchNr + 1;

	tmp.top = treeRECT.top;
	tmp.bottom = treeRECT.top + ((treeRECT.bottom - treeRECT.top) / 2);
	tmp.left = treeRECT.left + ((treeRECT.right - treeRECT.left) / 2);
	tmp.right = treeRECT.right;

	ab = new QuadTree(tmp);
	ab->branchNr = branchNr + 1;

	tmp.top = treeRECT.top + ((treeRECT.bottom - treeRECT.top) / 2);
	tmp.bottom = treeRECT.bottom;
	tmp.left = treeRECT.left;
	tmp.right = treeRECT.left + ((treeRECT.right - treeRECT.left) / 2);

	ba = new QuadTree(tmp);
	ba->branchNr = branchNr + 1;

	tmp.top = treeRECT.top + ((treeRECT.bottom - treeRECT.top) / 2);
	tmp.bottom = treeRECT.bottom;
	tmp.left = treeRECT.left + ((treeRECT.right - treeRECT.left) / 2);
	tmp.right = treeRECT.right;

	bb = new QuadTree(tmp);
	bb->branchNr = branchNr + 1;
}

void QuadTree::Add(Bubble* bubble)
{
	if (!isLeaf)
	{
		if (aa->PointInRect(bubble->position)){ aa->Add(bubble); }
		if (ab->PointInRect(bubble->position)){ ab->Add(bubble); }
		if (ba->PointInRect(bubble->position)){ ba->Add(bubble); }
		if (bb->PointInRect(bubble->position)){ bb->Add(bubble); }
	}
	else
	{
		if (bubbles.size() < vectorCap || branchNr >= branchCap)
		{
			bubbles.push_back(bubble);
		}
		else
		{
			Devide();
			bool check = false;
			for (int i = 0; i < bubbles.size(); i++) // if points near edge keep m
			{
				if (aa->PointInInnerRect(bubbles[i]->position)){ aa->Add(bubbles[i]); check = true; }
				else if (ab->PointInInnerRect(bubbles[i]->position)){ ab->Add(bubbles[i]); check = true; }
				else if (ba->PointInInnerRect(bubbles[i]->position)){ ba->Add(bubbles[i]); check = true; }
				else if (bb->PointInInnerRect(bubbles[i]->position)){ bb->Add(bubbles[i]); check = true; }

				if (check) { bubbles.erase(bubbles.begin() + i); }
			}
			Add(bubble);
		}
	}
}

bool QuadTree::PointInRect(glm::vec2 p)
{
	if (p.x >= treeRECT.left &&
		p.x <= treeRECT.right &&
		p.y >= treeRECT.top &&
		p.y <= treeRECT.bottom)
	{
		return true;
	}

	return false;
}

bool QuadTree::PointInInnerRect(glm::vec2 p)
{
	if (p.x >= InnerRECT.left &&
		p.x <= InnerRECT.right &&
		p.y >= InnerRECT.top &&
		p.y <= InnerRECT.bottom)
	{
		return true;
	}

	return false;
}

void QuadTree::Draw(RECT t, Surface* drawPane)
{
	for (int i = 0; i < bubbles.size(); i++)
	{
		bubbles[i]->Draw(t, drawPane);
	}

	if (isLeaf){
		//drawPane->Box(treeRECT.left +1 - t.left, treeRECT.top+1 -t.top, treeRECT.right-1 -t.right, treeRECT.bottom-1- t.bottom, 0xff0000);

		for (int i = 0; i < bubbles.size(); i++) // if points near edge keep m
		{
			//	drawPane->Plot(bubbles[i]->position.x, bubbles[i]->position.y, 0xff0000);
		}
	}
	else
	{
		glm::vec2 s = glm::vec2(t.right - t.left, t.top - t.bottom);

		if (!isLeaf)
		{
			/*if (aa->PointInRect(s)) { aa->Draw(t,drawPane); };
			if (ab->PointInRect(s)) { ab->Draw(t,drawPane); };
			if (ba->PointInRect(s)) { ba->Draw(t,drawPane); };
			if (bb->PointInRect(s)) { bb->Draw(t,drawPane); };*/

			aa->Draw(t, drawPane);
			ab->Draw(t, drawPane);
			ba->Draw(t, drawPane);
			bb->Draw(t, drawPane);
		}
	}
}

void QuadTree::CheckCollision(Ship* s)
{
	for (int i = 0; i < bubbles.size(); i++)
	{
		double r1 = bubbles[i]->radius;
		double r2 = s->radius;
		glm::vec2 p1 = bubbles[i]->position;
		glm::vec2 p2 = s->position;

		if (bubbles[i]->CheckCircleCollision(r1, p1, r2, p2))
		{
			if (bubbles[i]->isWall)
			{
				//	bubbles[i]->position += s->velocity*s->speed;
				s->position -= s->velocity*s->speed;
				s->speed = -s->speed;
			}
			else
			{
				bubbles[i]->velocity = glm::normalize(bubbles[i]->position - s->position);
				bubbles[i]->speed = s->speed;
				//s->speed = -s->speed;
			}
		}
	}

	if (!isLeaf)
	{
		if (aa->PointInRect(s->position)) { aa->CheckCollision(s); };
		if (ab->PointInRect(s->position)) { ab->CheckCollision(s); };
		if (ba->PointInRect(s->position)) { ba->CheckCollision(s); };
		if (bb->PointInRect(s->position)) { bb->CheckCollision(s); };
	}
}

void QuadTree::CheckCollision(Bom* s)
{
	for (int i = 0; i < bubbles.size(); i++)
	{
		double r1 = bubbles[i]->radius;
		double r2 = s->radius;
		glm::vec2 p1 = bubbles[i]->position;
		glm::vec2 p2 = s->position;

		if (bubbles[i]->CheckCircleCollision(r1, p1, r2, p2))
		{
			//bubbles[i]->velocity = glm::normalize(bubbles[i]->position - s->position);
			//bubbles[i]->speed = s->blastspeed;

			bubbles[i]->position = glm::vec2(0, 0);

			//s->speed = -s->speed;
		}
	}

	if (!isLeaf)
	{
		if (aa->PointInRect(s->position)) { aa->CheckCollision(s); };
		if (ab->PointInRect(s->position)) { ab->CheckCollision(s); };
		if (ba->PointInRect(s->position)) { ba->CheckCollision(s); };
		if (bb->PointInRect(s->position)) { bb->CheckCollision(s); };
	}
}

void QuadTree::PopBack()
{
	if (!isLeaf)
	{
		aa->PopBack();
		ab->PopBack();
		ba->PopBack();
		bb->PopBack();

		if (aa->bubbles.size() +
			ab->bubbles.size() +
			ba->bubbles.size() +
			bb->bubbles.size() +
			bubbles.size() < vectorCap)
		{
			for (int i = 0; i < aa->bubbles.size(); i++)
			{
				bubbles.push_back(aa->bubbles[i]);
			}

			for (int i = 0; i < ab->bubbles.size(); i++)
			{
				bubbles.push_back(ab->bubbles[i]);
			}

			for (int i = 0; i < ba->bubbles.size(); i++)
			{
				bubbles.push_back(ba->bubbles[i]);
			}

			for (int i = 0; i < bb->bubbles.size(); i++)
			{
				bubbles.push_back(bb->bubbles[i]);
			}

			delete aa;
			delete ab;
			delete ba;
			delete bb;

			isLeaf = true;
		}
	}
}

void QuadTree::Update()
{
	for (int i = 0; i < bubbles.size(); i++)
	{
		if (!bubbles[i]->isWall)
		{
			bubbles[i]->Update();
		}
	}

	if (!isLeaf)
	{
		aa->Update();
		ab->Update();
		ba->Update();
		bb->Update();
	}
}