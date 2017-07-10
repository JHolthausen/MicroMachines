#pragma once

#include "template.h"
#include "surface.h"
#include "game.h"

namespace Tmpl8 {
	class Camera
	{
	public:
		Camera(RECT camView);
		Camera(){};
		~Camera();

		glm::vec2 position;

		RECT camView;

		int width;
		int height;

	};

}