#include "InputListener.h"
#include <iostream>       // std::cout
#include <algorithm>

using namespace Tmpl8;				// to use template classes
using namespace glm;				// to use glm vector stuff

InputListener::InputListener()
{
}

InputListener::~InputListener()
{
}

std::string InputListener::GetKeyPressed()
{
	std::string s = "";
	bool keyPressed = false;

	if (GetAsyncKeyState(48)) // 0
	{
		s = "0";
		keyPressed = true;

		if (GetAsyncKeyState(16))
		{
			s = ")";
		}
	}
	else if (GetAsyncKeyState(49))// 1
	{
		s = "1";
		keyPressed = true;

		if (GetAsyncKeyState(16))
		{
			s = "!";
		}
	}
	else if (GetAsyncKeyState(50))// 2
	{
		s = "2";
		keyPressed = true;
		if (GetAsyncKeyState(16))
		{
			s = "@";
		}
	}
	else if (GetAsyncKeyState(51)) //3
	{
		s = "3";
		keyPressed = true;
		if (GetAsyncKeyState(16))
		{
			s = "#";
		}
	}
	else if (GetAsyncKeyState(52)) //4
	{
		s = "4";
		keyPressed = true;
		if (GetAsyncKeyState(16))
		{
			s = "$";
		}
	}
	else if (GetAsyncKeyState(53)) //5
	{
		s = "5";
		keyPressed = true;
		if (GetAsyncKeyState(16))
		{
			s = "%";
		}
	}
	else if (GetAsyncKeyState(54)) //6
	{
		s = "6";
		keyPressed = true;

		if (GetAsyncKeyState(16))
		{
			s = "^";
		}
	}
	else if (GetAsyncKeyState(55)) //7
	{
		s = "7";
		keyPressed = true;

		if (GetAsyncKeyState(16))
		{
			s = "&";
		}
	}
	else if (GetAsyncKeyState(56)) //8
	{
		s = "8";
		keyPressed = true;

		if (GetAsyncKeyState(16))
		{
			s = "*";
		}
	}
	else if (GetAsyncKeyState(57))//9
	{
		s = "9";
		keyPressed = true;

		if (GetAsyncKeyState(16))
		{
			s = "(";
		}
	}
	else if (GetAsyncKeyState(65))//a
	{
		s = "a";
		keyPressed = true;
	}
	else if (GetAsyncKeyState(66))//b
	{
		s = "b";
		keyPressed = true;
	}
	else if (GetAsyncKeyState(67))//c
	{
		s = "c";
		keyPressed = true;
	}
	else if (GetAsyncKeyState(68))//d
	{
		s = "d";
		keyPressed = true;
	}
	else if (GetAsyncKeyState(69))//e
	{
		s = "e";
		keyPressed = true;
	}
	else if (GetAsyncKeyState(70))//f
	{
		s = "f";
		keyPressed = true;
	}
	else if (GetAsyncKeyState(71))//g
	{
		s = "g";
		keyPressed = true;
	}
	/////
	else if (GetAsyncKeyState(72))//h
	{
		s = "h";
		keyPressed = true;
	}
	else if (GetAsyncKeyState(73))//i
	{
		s = "i";
		keyPressed = true;
	}
	else if (GetAsyncKeyState(74))//j
	{
		s = "j";
		keyPressed = true;
	}
	else if (GetAsyncKeyState(75))//k
	{
		s = "k";
		keyPressed = true;
	}
	//////
	else if (GetAsyncKeyState(76))//l
	{
		s = "l";
		keyPressed = true;
	}
	else if (GetAsyncKeyState(77))//m
	{
		s = "m";
		keyPressed = true;
	}
	else if (GetAsyncKeyState(78))//n
	{
		s = "n";
		keyPressed = true;
	}
	else if (GetAsyncKeyState(79))//o
	{
		s = "o";
		keyPressed = true;
	}

	///
	else if (GetAsyncKeyState(80))//p
	{
		s = "p";
		keyPressed = true;
	}
	else if (GetAsyncKeyState(81))//q
	{
		s = "q";
		keyPressed = true;
	}
	else if (GetAsyncKeyState(82))//r
	{
		s = "r";
		keyPressed = true;
	}
	else if (GetAsyncKeyState(83))//s
	{
		s = "s";
		keyPressed = true;
	}
	else if (GetAsyncKeyState(84))//t
	{
		s = "t";
		keyPressed = true;
	}
	else if (GetAsyncKeyState(85))//u
	{
		s = "u";
		keyPressed = true;
	}
	else if (GetAsyncKeyState(86))//v
	{
		s = "v";
		keyPressed = true;
	}
	else if (GetAsyncKeyState(87))//w
	{
		s = "w";
		keyPressed = true;
	}
	else if (GetAsyncKeyState(88))//x
	{
		s = "x";
		keyPressed = true;
	}
	else if (GetAsyncKeyState(89))//y
	{
		s = "y";
		keyPressed = true;
	}
	else if (GetAsyncKeyState(90))//z
	{
		s = "z";
		keyPressed = true;
	}

	//convert to upercase
	if (GetAsyncKeyState(16) || ((GetKeyState(VK_CAPITAL) & 0x0001) != 0))//shift, capslock
	{
		std::transform(s.begin(), s.end(), s.begin(), ::toupper);
	}

	if (debug && keyPressed)
	{
		std::cout << "inputlistener_GetKeyPressed : " << s << "\n";
	}

	return s;
}
bool InputListener::IsKeyPressed(std::string name)
{
	bool keyPressed = false;

	std::transform(name.begin(), name.end(), name.begin(), ::tolower);

	if (name == "0" && GetAsyncKeyState(48))
	{
		keyPressed = true;
	}
	else if (name == "1" && GetAsyncKeyState(49))
	{
		keyPressed = true;
	}
	else if (name == "2" && GetAsyncKeyState(50))
	{
		keyPressed = true;
	}
	else if (name == "3" && GetAsyncKeyState(51))
	{
		keyPressed = true;
	}
	else if (name == "4" && GetAsyncKeyState(52))
	{
		keyPressed = true;
	}
	else if (name == "5" && GetAsyncKeyState(53))
	{
		keyPressed = true;
	}
	else if (name == "6" && GetAsyncKeyState(54))
	{
		keyPressed = true;
	}
	else if (name == "7" && GetAsyncKeyState(55))
	{
		keyPressed = true;
	}
	else if (name == "8" && GetAsyncKeyState(56))
	{
		keyPressed = true;
	}
	else if (name == "9" && GetAsyncKeyState(57))
	{
		keyPressed = true;
	}
	else if (name == "a" && GetAsyncKeyState(65))
	{
		keyPressed = true;
	}
	else if (name == "b" && GetAsyncKeyState(66))
	{
		keyPressed = true;
	}
	else if (name == "c" && GetAsyncKeyState(67))
	{
		keyPressed = true;
	}
	else if (name == "d" && GetAsyncKeyState(68))
	{
		keyPressed = true;
	}
	else if (name == "e" && GetAsyncKeyState(69))
	{
		keyPressed = true;
	}
	else if (name == "f" && GetAsyncKeyState(70))
	{
		keyPressed = true;
	}
	else if (name == "g" && GetAsyncKeyState(71))
	{
		keyPressed = true;
	}
	else if (name == "h" && GetAsyncKeyState(72))
	{
		keyPressed = true;
	}
	else if (name == "i" && GetAsyncKeyState(73))
	{
		keyPressed = true;
	}
	else if (name == "j" && GetAsyncKeyState(74))
	{
		keyPressed = true;
	}
	else if (name == "k" && GetAsyncKeyState(75))
	{
		keyPressed = true;
	}
	else if (name == "l" && GetAsyncKeyState(76))
	{
		keyPressed = true;
	}
	else if (name == "m" && GetAsyncKeyState(77))
	{
		keyPressed = true;
	}
	else if (name == "n" && GetAsyncKeyState(78))
	{
		keyPressed = true;
	}
	else if (name == "o" && GetAsyncKeyState(79))
	{
		keyPressed = true;
	}
	else if (name == "p" && GetAsyncKeyState(80))
	{
		keyPressed = true;
	}
	else if (name == "q" && GetAsyncKeyState(81))
	{
		keyPressed = true;
	}
	else if (name == "r" && GetAsyncKeyState(82))
	{
		keyPressed = true;
	}
	else if (name == "s" && GetAsyncKeyState(83))
	{
		keyPressed = true;
	}
	else if (name == "t" && GetAsyncKeyState(84))
	{
		keyPressed = true;
	}
	else if (name == "u" && GetAsyncKeyState(85))
	{
		keyPressed = true;
	}
	else if (name == "v" && GetAsyncKeyState(86))
	{
		keyPressed = true;
	}
	else if (name == "w" && GetAsyncKeyState(87))
	{
		keyPressed = true;
	}
	else if (name == "x" && GetAsyncKeyState(88))
	{
		keyPressed = true;
	}
	else if (name == "y" && GetAsyncKeyState(89))
	{
		keyPressed = true;
	}
	else if (name == "z" && GetAsyncKeyState(90))
	{
		keyPressed = true;
	}

	if (keyPressed && debug)
	{
		std::cout << "inputlistener_IsKeyPressed , keypressed :" << name << "\n";
	}

	return keyPressed;
}

POINT InputListener::GetMousePos()
{
	HWND hwnd = GetForegroundWindow();
	POINT p;

	GetCursorPos(&p);
	ScreenToClient(hwnd, &p);

	if (debug)
	{
		std::cout << "InputListener_GetMousePos: " << p.x << " " << p.y << "\n";
	}
	return p;
}