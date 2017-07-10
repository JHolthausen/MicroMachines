#include "TrackBuilder.h"

using namespace Tmpl8;				// to use template classes
using namespace glm;				// to use glm vector stuff

TrackBuilder::TrackBuilder(Surface* screen)
{
	this->screen = screen;

	tracks.push_back(new Trackpiece(1));
	tracks.push_back(new Trackpiece(2));
	tracks.push_back(new Trackpiece(3));

	tracks[0]->images.push_back(new Surface("assets/start1.png"));
	tracks[0]->images.push_back(new Surface("assets/start2.png"));
	tracks[0]->images.push_back(new Surface("assets/start3.png"));
	tracks[0]->images.push_back(new Surface("assets/start4.png"));
	tracks[0]->image = tracks[0]->images[tracks[0]->index];

	tracks[1]->images.push_back(new Surface("assets/straight1.png"));
	tracks[1]->images.push_back(new Surface("assets/straight2.png"));
	tracks[1]->images.push_back(new Surface("assets/straight1.png"));
	tracks[1]->images.push_back(new Surface("assets/straight2.png"));
	tracks[1]->image = tracks[1]->images[tracks[1]->index];

	tracks[2]->images.push_back(new Surface("assets/curve1.png"));
	tracks[2]->images.push_back(new Surface("assets/curve2.png"));
	tracks[2]->images.push_back(new Surface("assets/curve3.png"));
	tracks[2]->images.push_back(new Surface("assets/curve4.png"));

	tracks[2]->images.push_back(new Surface("assets/curve1.png"));
	tracks[2]->images.push_back(new Surface("assets/curve2.png"));
	tracks[2]->images.push_back(new Surface("assets/curve3.png"));
	tracks[2]->images.push_back(new Surface("assets/curve4.png"));


	tracks[2]->image = tracks[2]->images[tracks[2]->index];

	tracks[0]->inPoints.push_back(glm::vec2(320, 640));
	tracks[0]->inPoints.push_back(glm::vec2(640, 320));
	tracks[0]->inPoints.push_back(glm::vec2(320, 0));
	tracks[0]->inPoints.push_back(glm::vec2(0, 320));

	tracks[0]->outPoints.push_back(glm::vec2(320, 0));
	tracks[0]->outPoints.push_back(glm::vec2(0, 320));
	tracks[0]->outPoints.push_back(glm::vec2(320, 640));
	tracks[0]->outPoints.push_back(glm::vec2(640, 320));

	//set start poss
	tracks[0]->startPositions[0].push_back(glm::vec2(128, 320));
	tracks[0]->startPositions[0].push_back(glm::vec2(256, 320));
	tracks[0]->startPositions[0].push_back(glm::vec2(384, 320));
	tracks[0]->startPositions[0].push_back(glm::vec2(512, 320));

	tracks[0]->startPositions[1].push_back(glm::vec2(320, 128));
	tracks[0]->startPositions[1].push_back(glm::vec2(320, 256));
	tracks[0]->startPositions[1].push_back(glm::vec2(320, 384));
	tracks[0]->startPositions[1].push_back(glm::vec2(320, 512));


	tracks[0]->startPositions[2].push_back(glm::vec2(128, 320));
	tracks[0]->startPositions[2].push_back(glm::vec2(256, 320));
	tracks[0]->startPositions[2].push_back(glm::vec2(384, 320));
	tracks[0]->startPositions[2].push_back(glm::vec2(512, 320));


	tracks[0]->startPositions[3].push_back(glm::vec2(320, 128));
	tracks[0]->startPositions[3].push_back(glm::vec2(320, 256));
	tracks[0]->startPositions[3].push_back(glm::vec2(320, 384));
	tracks[0]->startPositions[3].push_back(glm::vec2(320, 512));




	tracks[1]->inPoints.push_back(glm::vec2(320, 640));
	tracks[1]->inPoints.push_back(glm::vec2(640, 320));
	tracks[1]->inPoints.push_back(glm::vec2(320, 0));
	tracks[1]->inPoints.push_back(glm::vec2(0, 320));

	tracks[1]->outPoints.push_back(glm::vec2(320, 0));
	tracks[1]->outPoints.push_back(glm::vec2(0, 320));
	tracks[1]->outPoints.push_back(glm::vec2(320, 640));
	tracks[1]->outPoints.push_back(glm::vec2(640, 320));

	tracks[2]->inPoints.push_back(glm::vec2(320, 640));
	tracks[2]->inPoints.push_back(glm::vec2(640, 320));
	tracks[2]->inPoints.push_back(glm::vec2(320, 0));
	tracks[2]->inPoints.push_back(glm::vec2(0, 320));
	tracks[2]->inPoints.push_back(glm::vec2(640, 320));
	tracks[2]->inPoints.push_back(glm::vec2(320, 0));
	tracks[2]->inPoints.push_back(glm::vec2(0, 320));
	tracks[2]->inPoints.push_back(glm::vec2(320, 640));

	tracks[2]->outPoints.push_back(glm::vec2(640, 320));
	tracks[2]->outPoints.push_back(glm::vec2(320, 0));
	tracks[2]->outPoints.push_back(glm::vec2(0, 320));
	tracks[2]->outPoints.push_back(glm::vec2(320, 640));
	tracks[2]->outPoints.push_back(glm::vec2(320, 640));
	tracks[2]->outPoints.push_back(glm::vec2(640, 320));
	tracks[2]->outPoints.push_back(glm::vec2(320, 0));
	tracks[2]->outPoints.push_back(glm::vec2(0, 320));

	//for (int i = 0; i < 9; i++)
	//{
	//	for (int j = 0; j < 10; j++)
	//	{
	//		mapgrid[i][j] = glm::vec2(0, 0);
	//	}
	//}
}

TrackBuilder::~TrackBuilder()
{
	for (int i = 0; i < tracks.size(); i++)
	{
		delete tracks[i];
		tracks.erase(tracks.begin() + i);
	}
}

int  TrackBuilder::Update()
{
	Draw();
	SelectTile();
	//switchTile();
	return HandleMenu();
}

void TrackBuilder::Draw()
{
	//map->Clear(0);

	//show grid
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			map->Box(0 + tilesize*j, 0 + tilesize*i, tilesize + tilesize*j, tilesize + tilesize*i, 0x0000ff);

			/*if (mapgrid[i][j].x >= 0)
			{
			Surface* s = tracks[mapgrid[i][j]].x]->image;
			Sprite* ss = new Sprite(s, 1);
			int a = 0 + tilesize*j;
			int b = 0 + tilesize*i;
			int c = tilesize + tilesize*j;
			int d = tilesize + tilesize*i;

			ss->DrawScaled(mapgrid[i][j].x, mapgrid[i][j].y, mapgrid[i][j].x + tilesize, mapgrid[i][j].y + tilesize, map);
			}*/
		}
	}

	Surface* ss = tracks[index]->image;
	map->CopyTo(screen, 10, 10);

	if (tracks[index]->inPoints[tracks[index]->index].x < 640 &&
		tracks[index]->inPoints[tracks[index]->index].y < 640)
	{
		ss->Bar(tracks[index]->inPoints[tracks[index]->index].x,
			tracks[index]->inPoints[tracks[index]->index].y,
			tracks[index]->inPoints[tracks[index]->index].x + 20,
			tracks[index]->inPoints[tracks[index]->index].y + 20,
			0x00ff00);
	}
	else
	{
		ss->Bar(tracks[index]->inPoints[tracks[index]->index].x - 20,
			tracks[index]->inPoints[tracks[index]->index].y - 20,
			tracks[index]->inPoints[tracks[index]->index].x,
			tracks[index]->inPoints[tracks[index]->index].y,
			0x00ff00);
	}

	if (tracks[index]->outPoints[tracks[index]->index].x < 640 &&
		tracks[index]->outPoints[tracks[index]->index].y < 640)
	{
		ss->Bar(tracks[index]->outPoints[tracks[index]->index].x,
			tracks[index]->outPoints[tracks[index]->index].y,
			tracks[index]->outPoints[tracks[index]->index].x + 20,
			tracks[index]->outPoints[tracks[index]->index].y + 20,
			0xff0000);
	}
	else
	{
		ss->Bar(tracks[index]->outPoints[tracks[index]->index].x - 20,
			tracks[index]->outPoints[tracks[index]->index].y - 20,
			tracks[index]->outPoints[tracks[index]->index].x,
			tracks[index]->outPoints[tracks[index]->index].y,
			0xff0000);
	}

	Sprite* s = new Sprite(ss, 1);
	s->DrawScaled(0, 0, previewPane->GetWidth(), previewPane->GetHeight(), previewPane);
	previewPane->CopyTo(screen, 670, 10);
}

void TrackBuilder::SelectTile()
{
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		if (il.GetMousePos().x >= 670 && il.GetMousePos().x <= 734 &&
			il.GetMousePos().y >= 10 && il.GetMousePos().y <= 74)
		{
			holdstile = true;
			trackpiece = glm::vec2(tracks[index]->tracknumber, tracks[index]->index);
		}
	}
	else if (holdstile)
	{
		holdstile = false;

		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (il.GetMousePos().x >= 10 + tilesize*j && il.GetMousePos().x <= 10 + tilesize + tilesize*j &&
					il.GetMousePos().y >= 10 + tilesize*i && il.GetMousePos().y <= 10 + tilesize + tilesize*i)
				{
					int a = 640*j + tracks[trackpiece.x-1]->outPoints[trackpiece.y].x; 
					int b = 640 * i + tracks[trackpiece.x - 1]->outPoints[trackpiece.y].y;

					trackRoute.push_back(glm::vec2(a, b));

					if (trackpiece.x == 1)
					{
						if (!startPlaced)
						{
							startPlaced = true;
							mapgrid[i][j] = trackpiece;
							previewPane->CopyTo(map, 0 + tilesize*j, 0 + tilesize*i);
							index++;


							startPositions = tracks[trackpiece.x - 1]->startPositions[tracks[trackpiece.x - 1]->index] ;

							for (int q = 0; q < startPositions.size(); q++)
							{
								startPositions[q] += glm::vec2(640 * j, 640 * i);
							}


						}



					}
					else
					{
						mapgrid[i][j] = trackpiece;
						previewPane->CopyTo(map, 0 + tilesize*j, 0 + tilesize*i);
					}

					break;
				}
			}
		}
	}


}

void TrackBuilder::switchTile()
{
	if (startPlaced)
	{
			if (startPlaced){
				index++;

				if (index == tracks.size())
				{
					index = 1;
				}
				Sleep(200);
			}
			else
			{
				std::cout << "place start first" << std::endl;
			}
		
	}
	/*if (il.IsKeyPressed("d"))
	{
		tracks[index]->Rotate();
		Sleep(200);
	}*/

	//if (il.IsKeyPressed("q"))
	//{
	//	Save();
	//	int i = 0;
	//}

	
}

void TrackBuilder::RotateTile()
{
	tracks[index]->Rotate();
	Sleep(200);
}

void TrackBuilder::Save()
{
	//Sprite* fill = new Sprite(new Surface("assets/trackpiece_fill.png"), 1);
	std::vector<std::string> savelist;

	//save tiles
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			savelist.push_back(std::to_string(mapgrid[i][j].x));
			savelist.push_back(std::to_string(mapgrid[i][j].y));

			//if (mapgrid[i][j].x == 0)
			//{
			//}
		}
	}
	savelist.push_back("");
	//save route
	for (int i = 0; i < trackRoute.size();i++)
	{
		savelist.push_back(std::to_string(trackRoute[i].x));
		savelist.push_back(std::to_string(trackRoute[i].y));

	}


	std::ofstream a_file("assets/test.txt");
	// save tile coords

	for each (std::string s in savelist)
	{
		a_file << s << std::endl;
	}

	
	// Close the file
	a_file.close();

	std::ofstream c_file("assets/startpos.txt");
	// save tile coords

	//save start pos
	for each (glm::vec2 s in startPositions)
	{
		std::string a = std::to_string(s.x);
		c_file << a << std::endl;
		a = std::to_string(s.y);
		c_file << a << std::endl;
	}


	// Close the file
	c_file.close();








}

//didnt know how to proper split a string, so everything is one line 
 std::pair<Surface*, std::vector<glm::vec2>> TrackBuilder::Load()
{
	std::vector<std::string> test;
	//set the highscore
	std::string line;

	//Opens file
	std::ifstream b_file("assets/test.txt");
	while (std::getline(b_file, line)) {
		test.push_back(line);
	}
	//close file stream
	b_file.close();



	std::vector<glm::vec2> tiles;
	std::vector<glm::vec2> route;


	int i = 0;
	while (test[i] != "")
	{
		double a;
		std::stringstream sd(test[i]); //turn the string into a stream
		sd >> a; //convert

		double b;
		std::stringstream sdsd(test[i + 1]); //turn the string into a stream
		sdsd >> b; //convert

		tiles.push_back(glm::vec2(a,b));
		i += 2;
	}

	for (i++; i < test.size(); i += 2)
	{
		double a;
		std::stringstream sd(test[i]); //turn the string into a stream
		sd >> a; //convert

		double b;
		std::stringstream sdsd(test[i + 1]); //turn the string into a stream
		sdsd >> b; //convert

		route.push_back(glm::vec2(a, b));
	}

	Surface* s = new Surface(10 * 640, 9 * 640);
	
	int cntr = 0;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (tiles[cntr].x >= 1 && tiles[cntr].x <= 4)
			{
				int a = tiles[cntr].x - 1;
				int b = tiles[cntr].y;

				tracks[a]->images[b]->CopyTo(s,j*640,i*640);



			}
			//tracks

			cntr++;

		}
	}

	std::pair<Surface*, std::vector<glm::vec2>> p(s, route);
	return p;
}

 int TrackBuilder::HandleMenu()
 {
	 Surface* DrawPane = screen;



	 //first button
	 int buttonwidth = 100;
	 int buttonheight = 20;
	 int x1 = 670;
	 int y1 = 90;
	 int x2 = x1 + buttonwidth;
	 int y2 = y1 + buttonheight;

	 DrawPane->Bar(x1, y1, x2, y2, 0x0000CC);//button
	 DrawPane->Print("Next Track", x1, y1, 0xffffff);//text;

	 if (GetAsyncKeyState(VK_LBUTTON))
	 {
		 if (il.GetMousePos().x >= x1 && il.GetMousePos().x <= x2 &&
			 il.GetMousePos().y >= y1 && il.GetMousePos().y <= y2)
		 {
			switchTile();
		 }
	 }

	 //2nd button
	 x1 = 670;
	 y1 = 130;
	 x2 = x1 + buttonwidth;
	 y2 = y1 + buttonheight;

	 DrawPane->Bar(x1, y1, x2, y2, 0x0000CC);//button
	 DrawPane->Print("rotate", x1, y1, 0xffffff);//text;

	 if (GetAsyncKeyState(VK_LBUTTON))
	 {
		 if (il.GetMousePos().x >= x1 && il.GetMousePos().x <= x2 &&
			 il.GetMousePos().y >= y1 && il.GetMousePos().y <= y2)
		 {
			 RotateTile();
		 }
	 }

	 //3rd button
	 x1 = 670;
     y1 = 170;
	 x2 = x1 + buttonwidth;
	 y2 = y1 + buttonheight;

	 DrawPane->Bar(x1, y1, x2, y2, 0x0000CC);//button
	 DrawPane->Print("Save", x1, y1, 0xffffff);//text;

	 if (GetAsyncKeyState(VK_LBUTTON))
	 {
		 if (il.GetMousePos().x >= x1 && il.GetMousePos().x <= x2 &&
			 il.GetMousePos().y >= y1 && il.GetMousePos().y <= y2)
		 {
			 Save();
		 }
	 }

	 //4th button
	 x1 = 670;
	 y1 = 210;
	 x2 = x1 + buttonwidth;
	 y2 = y1 + buttonheight;

	 DrawPane->Bar(x1, y1, x2, y2, 0x0000CC);//button
	 DrawPane->Print("Back", x1, y1, 0xffffff);//text;

	 if (GetAsyncKeyState(VK_LBUTTON))
	 {
		 if (il.GetMousePos().x >= x1 && il.GetMousePos().x <= x2 &&
			 il.GetMousePos().y >= y1 && il.GetMousePos().y <= y2)
		 {
			 screen->Clear(0);
			 return 1;
		 }
	 }



	 return 3; // default to stay in builder
 }

 std::vector<glm::vec2> TrackBuilder::getStartPos()
 {
	 std::string line;
	 std::vector<std::string> test;
	 std::vector<glm::vec2> temp;

	 std::ifstream b_file("assets/startpos.txt");
	 while (std::getline(b_file, line)) {
		 test.push_back(line);
	 }

	 b_file.close();

	 for (int i = 0; i < test.size(); i = i + 2)
	 {
		 double a;
		 std::stringstream sd(test[i]); //turn the string into a stream
		 sd >> a; //convert

		 double b;
		 std::stringstream sdsd(test[i + 1]); //turn the string into a stream
		 sdsd >> b; //convert

		 temp.push_back(glm::vec2(a, b));
	 }

	 return temp;

 }