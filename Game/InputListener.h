#pragma once

#include "template.h"
#include "surface.h"
#include <string>

namespace Tmpl8 {
	class InputListener
	{
	public:
		InputListener();
		~InputListener();

		bool IsKeyPressed(std::string name);
		std::string GetKeyPressed();

		POINT GetMousePos();

		bool debug = false;
	};
}