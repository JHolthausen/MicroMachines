#include "TilleFactory.h"

using namespace Tmpl8;				// to use template classes
using namespace glm;				// to use glm vector stuff


TilleFactory::TilleFactory()
{
	Surface* s = new Surface("assets/tilesheet.png");
	int width = s->GetWidth();
	int height = s->GetHeight();

	for (int i = 0; i < height / TILESIZE; i++)
	{
		for (int j = 0; j < width / TILESIZE; j++)
		{
			GrabTile(i, j, s);
		}
	}
	index = TileCounter;
	delete s;
}


TilleFactory::~TilleFactory()
{
}



std::vector<std::vector<int>> TilleFactory::getArray(Surface* image)
{
	int width = image->GetWidth();
	int height = image->GetHeight();
	std::vector<std::vector<int>> tmp;

	for (int i = 0; i < height / TILESIZE; i++)
	{
		std::vector<int> t;
		for (int j = 0; j < width / TILESIZE; j++)
		{
			t.push_back(GrabTile(i, j, image));
			SimpleCnt++;
		}
		tmp.push_back(t);
	}

	delete image; // delete image cuz u give in new surface
	return tmp;

}



int TilleFactory::GrabTile(int Rows, int Cols,Surface* img)
{
	Tile* T = new Tile();
	img->CopyTo(T->TGraphic, 0 - (Cols * TILESIZE), 0 - (Rows * TILESIZE));


	// T has a graphic
	if (Tiles.size() == 0)
	{
		// there is no doubt this is a new unique graphic to go in
		Tiles.push_back(T);
		TileCounter++;
		return 0;

	}

	else
	{
		for (int i = 0; i < Tiles.size(); i++)
		{
			if (T->Compare(Tiles[i]->TGraphic))
			{ // we found this so it already exists
				delete T;
				T = NULL;
				return i; // the index of the value we found for insertion into that map

			}


		}

		// we competed the loop so that means we found no match.
		Tiles.push_back(T);
		TileCounter++;
		return TileCounter - 1;


	}






	Tiles.push_back(T);
	return SimpleCnt;



}
