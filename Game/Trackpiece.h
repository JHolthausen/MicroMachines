#pragma once

#include "template.h"
#include "surface.h"

#include <vector>

namespace Tmpl8 {
	class Trackpiece
	{
	public:
		Trackpiece(int);
		~Trackpiece();

		void Setpoints(glm::vec2, glm::vec2);
		void Rotate();

		int tracknumber = 0;

		std::vector<glm::vec2> inPoints;
		std::vector<glm::vec2> outPoints;
		std::vector<std::vector<glm::vec2>> startPositions;

		std::vector<Surface*> images;

		Surface* image;
		int index = 0;
	};
}