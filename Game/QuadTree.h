#pragma once

#include "template.h"
#include "surface.h"
#include "Bubble.h"
#include <vector>
#include "Ship.h"
#include "Bom.h"

namespace Tmpl8 {
	class QuadTree
	{
	public:
		QuadTree(RECT treeRECT);
		~QuadTree();

		void Devide();
		void Add(Bubble* bubble);
		bool PointInRect(glm::vec2 p);
		bool PointInInnerRect(glm::vec2 p);
		void Update();

		void Draw(RECT t, Surface* s);//forvisuals
		void PopBack(); //delete childs if all empty or amount of objects + parent is less than cap

		void CheckCollision(Ship* s);
		void CheckCollision(Bom* b);

		QuadTree* aa;
		QuadTree* ab;
		QuadTree* ba;
		QuadTree* bb;

		bool isLeaf = true;

		RECT treeRECT;
		RECT InnerRECT;

		std::vector<Bubble*> bubbles;
		int vectorCap = 2; // the amount of bubbles in vector
		int branchCap = 1; //the amount of devision allowed
		int branchNr = 1;
	};
}