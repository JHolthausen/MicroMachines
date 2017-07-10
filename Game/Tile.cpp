#include "Tile.h"

using namespace  Tmpl8;
 
Tile::Tile()
{
	TGraphic = new Surface(TILESIZE, TILESIZE); // all we reall need to do here is create a space for the graphic
}


Tile::~Tile()
{
}


void Tile::Draw(int x, int y, Surface* ScreenToDrawTo)
{
	TGraphic->CopyTo(ScreenToDrawTo, x, y);

}


bool Tile::Compare(Surface* CompareWith)
{
	for (int i = 0; i < TILESIZE * TILESIZE; i++)
	{
		if (TGraphic->GetBuffer()[i] != CompareWith->GetBuffer()[i]) return false;


	}

	return true;

}