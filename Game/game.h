#pragma once

// #define FULLSCREEN
#define SCRWIDTH	1200
#define SCRHEIGHT	800
#define TILESIZE	64

#include "template.h"
#include "surface.h"
#include "QuadTree.h"
#include "Camera.h"
#include "Ship.h"
#include "Bom.h"

namespace Tmpl8 {
	class Surface;
	class Camera;

	class Game
	{
	public:
		void SetTarget(Surface* _Surface) { screen = _Surface; }
		void Init();
		void Shutdown() { /* implement if you want code to be executed upon app exit */ };
		void Tick(float _DT);
		void MouseUp(int _Button) { /* implement if you want to detect mouse button presses */ }
		void MouseDown(int _Button) { /* implement if you want to detect mouse button presses */ }
		void MouseMove(int _X, int _Y) { /* implement if you want to detect mouse movement */ }
		void KeyUp(int a_Key) { /* implement if you want to handle keys */ }
		void KeyDown(int a_Key) { /* implement if you want to handle keys */ }

		Surface* CameraRecord(Camera* cam); // checks what object is in camera range and draws it

		void InitCams();
		void InitShips();
		void InitWorld();

		void Delete();

		QuadTree* tree;

		int worldWidth;
		int worldHeight;

		void PlayGame();
		void InitGame();

		void InitQuadTree();

		void HandleMenus();

		int  SelectPlayersMenu();

		void HandleButtonSelect(int humans);

		int MainMenu();

		std::string keyArray[4][3];
		int players = 1;
		int humans = 1;

		std::vector<Bom*> bombs;
		std::vector<Bubble*> bubbles;
		std::vector<Bubble*> Bubbles2;

		std::vector<Ship*> playersList;
		std::vector<glm::vec2> route;

	private:
		Surface* screen;

		std::vector<std::vector<int>> worldGrid;
		std::vector<Camera*> cams;
	};
}; // namespace Tmpl8