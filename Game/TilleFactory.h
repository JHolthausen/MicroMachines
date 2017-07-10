#pragma once

#include "template.h"
#include "surface.h"
#include <vector>
#include "Tile.h"

namespace Tmpl8 {
	class TilleFactory
	{
	public:
		TilleFactory();
		~TilleFactory();

		int	GrabTile(int Rows, int Cols, Surface* img);
		std::vector<std::vector<int>> getArray(Surface* image);

		std::vector<Tile*> Tiles;
		int	SimpleCnt = 0;
		int TileCounter = 0;

		int index = 0; //if tiles > index then they are walls

	};

}