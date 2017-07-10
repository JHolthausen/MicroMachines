#include "game.h"
#include "InputListener.h"
#include <vector>
#include "TilleFactory.h"
#include "TrackBuilder.h"

#include <thread>         // std::thread
std::thread* first;

using namespace Tmpl8;				// to use template classes
using namespace glm;				// to use glm vector stuff

Surface imageTest("assets/loading.png");
InputListener il;
std::vector<Bubble*> Bubbles;
TilleFactory tf;
Surface* bubimg = new Surface("assets/bubble3.png");

std::vector<int> playerfinish;

Bubble* d = new Bubble();
TrackBuilder* tb;

//sound tread
void BackGroundMusic()
{
	PlaySound(TEXT("assets/dropkick"), NULL, SND_LOOP);
}

// -----------------------------------------------------------
// Initialize the game
// -----------------------------------------------------------
void Game::Init()
{
	//InitGame();
}

// -----------------------------------------------------------
// Main game tick function
// -----------------------------------------------------------
void Game::Tick(float _DT)
{
	// clear the canvas
	screen->Clear(0);

	static int state = 1;

	switch (state)
	{
	case 1:  // main menu
		state = MainMenu();
		if (state == 3)
		{
			tb = new TrackBuilder(screen);
		}
		break;
	case 2:  // init play

		state = SelectPlayersMenu();
		if (state == 3)
		{
			tb = new TrackBuilder(screen);
		}
		break;

	case 3:  //trackbuilder

		state = tb->Update();
		if (state == 1)
		{
			delete tb;
		}

		//state = MainMenu();
		break;

	case 4:  // exit
		std::exit(0);
		break;
	case 5: // initialize the game
		imageTest.CopyTo(screen, 0, 0);
		srand(1);//get new random
		state = 7;
		break;

	case 6:
		PlayGame();

		for (int i = 0; i < playersList.size(); i++)
		{
			if (playersList[i]->laps > 3 && playersList[i]->isfinished == false)
			{
				playersList[i]->isfinished = true;
				playerfinish.push_back(playersList[i]->PlayerNumber);
			}
		}

		if (playerfinish.size() == humans)
		{
			state = 8;
		}
		if (state == 8)
		{
			TerminateThread(first, 0);
			//			CloseHandle(first);
		}

		break;
	case 7:

		InitGame();
		state = 6;
		first = new std::thread(BackGroundMusic);

		break;
	case 8:
		if (il.IsKeyPressed("e"))
		{
			state = 1;
			Delete();
			break;
		}//screen->Print("end of game")

		screen->Print("place:", screen->GetWidth() / 2 - 30, 0, 0xffffff);

		for (int i = 0; i < playerfinish.size(); i++)
		{
			char points[50];

			int n, a = playerfinish[i];
			n = sprintf(points, "%d", a);

			screen->Print("player : ", screen->GetWidth() / 2 - 30, 20 + i * 20, 0xffffff);
			screen->Print(points, screen->GetWidth() / 2 + 30, 20 + i * 20, 0xffffff);
		}

		screen->Print("press  >> E << to continue", screen->GetWidth() / 2 - 30, screen->GetHeight() / 2, 0xffffff);

		break;
	}
}

int Game::MainMenu()
{
	Surface* DrawPane = screen;

	//first button
	int buttonwidth = 100;
	int buttonheight = 20;
	int x1 = SCRWIDTH / 2 - buttonwidth / 2;
	int y1 = 20;
	int x2 = SCRWIDTH / 2 + buttonwidth / 2;
	int y2 = y1 + buttonheight;

	DrawPane->Bar(x1, y1, x2, y2, 0x0000CC);//button
	DrawPane->Print("Play", x1, y1, 0xffffff);//text;

	if (GetAsyncKeyState(VK_LBUTTON))
	{
		if (il.GetMousePos().x >= x1 && il.GetMousePos().x <= x2 &&
			il.GetMousePos().y >= y1 && il.GetMousePos().y <= y2)
		{
			return 2;
		}
	}

	//second button
	x1 = SCRWIDTH / 2 - buttonwidth / 2;
	y1 = 50;
	x2 = SCRWIDTH / 2 + buttonwidth / 2;
	y2 = y1 + buttonheight;

	DrawPane->Bar(x1, y1, x2, y2, 0x0000CC);//button
	DrawPane->Print("TrackBuilder", x1, y1, 0xffffff);//text;

	if (GetAsyncKeyState(VK_LBUTTON))
	{
		if (il.GetMousePos().x >= x1 && il.GetMousePos().x <= x2 &&
			il.GetMousePos().y >= y1 && il.GetMousePos().y <= y2)
		{
			return 3;
		}
	}

	//3rd button
	x1 = SCRWIDTH / 2 - buttonwidth / 2;
	y1 = 80;
	x2 = SCRWIDTH / 2 + buttonwidth / 2;
	y2 = y1 + buttonheight;

	DrawPane->Bar(x1, y1, x2, y2, 0x0000CC);//button
	DrawPane->Print("Exit", x1, y1, 0xffffff);//text;

	if (GetAsyncKeyState(VK_LBUTTON))
	{
		if (il.GetMousePos().x >= x1 && il.GetMousePos().x <= x2 &&
			il.GetMousePos().y >= y1 && il.GetMousePos().y <= y2)
		{
			return 4;
		}
	}

	DrawPane->CopyTo(screen, 0, 0);

	return 1;
}

void Game::InitCams()
{
	/*RECT t;
	t.top = t.left = 0;
	t.right = SCRWIDTH;
	t.bottom = SCRHEIGHT;

	glm::vec2 pos = glm::vec2(SCRWIDTH / 2, SCRHEIGHT / 2);

	cams.push_back(new Camera(pos,t));
	*/
	//set cameras
	switch (humans)
	{
		Camera* cam;

	case 1:
		cam = new Camera(RECT{ 0, 0, SCRWIDTH, SCRHEIGHT });
		cams.push_back(cam);
		break;

	case 2:
		cam = new Camera(RECT{ 0, 0, SCRWIDTH, SCRHEIGHT / 2 });
		cams.push_back(cam);

		cam = new Camera(RECT{ 0, SCRHEIGHT / 2, SCRWIDTH, SCRHEIGHT });
		cams.push_back(cam);
		break;

	case 3:
		cam = new Camera(RECT{ 0, 0, SCRWIDTH, SCRHEIGHT / 2 });
		cams.push_back(cam);

		cam = new Camera(RECT{ 0, SCRHEIGHT / 2, SCRWIDTH / 2, SCRHEIGHT });
		cams.push_back(cam);

		cam = new Camera(RECT{ SCRWIDTH / 2, SCRHEIGHT / 2, SCRWIDTH, SCRHEIGHT });
		cams.push_back(cam);
		break;

	case 4:
		cam = new Camera(RECT{ 0, 0, SCRWIDTH / 2, SCRHEIGHT / 2 });
		cams.push_back(cam);

		cam = new Camera(RECT{ SCRWIDTH / 2, 0, SCRWIDTH, SCRHEIGHT / 2 });
		cams.push_back(cam);

		cam = new Camera(RECT{ 0, SCRHEIGHT / 2, SCRWIDTH / 2, SCRHEIGHT });
		cams.push_back(cam);

		cam = new Camera(RECT{ SCRWIDTH / 2, SCRHEIGHT / 2, SCRWIDTH, SCRHEIGHT });
		cams.push_back(cam);
		break;
	}
}

int Game::SelectPlayersMenu()
{
	int buttonwidth = 100;
	int buttonheight = 20;
	int x1 = SCRWIDTH / 2 - buttonwidth / 2;
	int y1 = 20;
	int x2 = SCRWIDTH / 2 + buttonwidth / 2;
	int y2 = y1 + buttonheight;

	screen->Bar(x1, y1, x2, y2, 0x0000CC);//button
	screen->Print("Players : ", x1, y1, 0xffffff);//text;

	//amount of players
	x1 = x2 + 10;
	x2 = x1 + buttonwidth;
	y2 = y1 + buttonheight;

	screen->Bar(x1, y1, x2, y2, 0x0000CC);//button

	char points[50];

	int n, a = players;
	n = sprintf(points, "%d", a);
	screen->Print(points, x1, y1, 0xffffff);//text;

	if (GetAsyncKeyState(VK_LBUTTON))
	{
		if (il.GetMousePos().x >= x1 && il.GetMousePos().x <= x2 &&
			il.GetMousePos().y >= y1 && il.GetMousePos().y <= y2)
		{
			players++;
			if (players > 4)
			{
				players = 1;
			}
			Sleep(200);
		}
	}

	/////////humans

	x1 = SCRWIDTH / 2 - buttonwidth / 2;
	y1 = 50;
	x2 = SCRWIDTH / 2 + buttonwidth / 2;
	y2 = y1 + buttonheight;

	screen->Bar(x1, y1, x2, y2, 0x0000CC);//button
	screen->Print("Humans : ", x1, y1, 0xffffff);//text;

	//amount of players
	x1 = x2 + 10;
	x2 = x1 + buttonwidth;
	y2 = y1 + buttonheight;

	screen->Bar(x1, y1, x2, y2, 0x0000CC);//button

	points[50];

	a = humans;
	n = sprintf(points, "%d", a);
	screen->Print(points, x1, y1, 0xffffff);//text;

	if (GetAsyncKeyState(VK_LBUTTON))
	{
		if (il.GetMousePos().x >= x1 && il.GetMousePos().x <= x2 &&
			il.GetMousePos().y >= y1 && il.GetMousePos().y <= y2)
		{
			humans++;
			if (humans > players)
			{
				humans = 1;
			}
			Sleep(200);
		}
	}

	//info labels

	x1 = SCRWIDTH / 2 - buttonwidth / 2;
	y1 = 120;
	x2 = SCRWIDTH / 2 + buttonwidth / 2;
	y2 = y1 + buttonheight;

	screen->Bar(x1, y1, x2, y2, 0x0000CC);//button
	screen->Print("Player:", x1, y1, 0xffffff);//text;

	x1 = x2 + 10;
	x2 = x1 + 50;

	screen->Bar(x1, y1, x2, y2, 0x0000CC);//button
	screen->Print("leftkey", x1, y1, 0xffffff);//text;

	x1 = x2 + 10;
	x2 = x1 + 50;

	screen->Bar(x1, y1, x2, y2, 0x0000CC);//button
	screen->Print("upkey", x1, y1, 0xffffff);//text;

	x1 = x2 + 10;
	x2 = x1 + 50;

	screen->Bar(x1, y1, x2, y2, 0x0000CC);//button
	screen->Print("rightkey", x1, y1, 0xffffff);//text;

	HandleButtonSelect(humans);

	//playbutton

	x1 = SCRWIDTH / 2 - buttonwidth / 2;
	y1 = 300;
	x2 = SCRWIDTH / 2 + buttonwidth / 2;
	y2 = y1 + buttonheight;

	screen->Bar(x1, y1, x2, y2, 0x0000CC);//button
	screen->Print("play", x1, y1, 0xffffff);//text;

	if (GetAsyncKeyState(VK_LBUTTON))
	{
		if (il.GetMousePos().x >= x1 && il.GetMousePos().x <= x2 &&
			il.GetMousePos().y >= y1 && il.GetMousePos().y <= y2)
		{
			return 5;
		}
	}

	//return button
	x1 = SCRWIDTH / 2 - buttonwidth / 2;
	y1 = 340;
	x2 = SCRWIDTH / 2 + buttonwidth / 2;
	y2 = y1 + buttonheight;

	screen->Bar(x1, y1, x2, y2, 0x0000CC);//button
	screen->Print("back", x1, y1, 0xffffff);//text;

	if (GetAsyncKeyState(VK_LBUTTON))
	{
		if (il.GetMousePos().x >= x1 && il.GetMousePos().x <= x2 &&
			il.GetMousePos().y >= y1 && il.GetMousePos().y <= y2)
		{
			return 1;
		}
	}
	return 2;
}

void Game::HandleButtonSelect(int humans)
{
	int buttonwidth = 100;
	int buttonheight = 20;
	int x1, y1, x2, y2;

	std::string tmp;
	char tab2[1024];

	static bool hasFocus = false;
	static glm::vec2 focus;

	for (int i = 0; i < humans; i++)
	{
		x1 = SCRWIDTH / 2 - buttonwidth / 2;
		y1 = 150 + (buttonheight + 10)*i;
		x2 = SCRWIDTH / 2 + buttonwidth / 2;
		y2 = y1 + buttonheight;

		screen->Bar(x1, y1, x2, y2, 0x0000CC);//button

		//text;
		tmp = "Player " + std::to_string(i + 1);
		strcpy(tab2, tmp.c_str());
		screen->Print(tab2, x1, y1, 0xffffff);//text;

		for (int j = 0; j < 3; j++)
		{
			x1 = x2 + 10;
			x2 = x1 + 50;

			screen->Bar(x1, y1, x2, y2, 0x0000CC);//button

			//text;
			tmp = keyArray[i][j];
			strcpy(tab2, tmp.c_str());
			screen->Print(tab2, x1, y1, 0xffffff);//text;

			if (GetAsyncKeyState(VK_LBUTTON))
			{
				if (il.GetMousePos().x >= x1 && il.GetMousePos().x <= x2 &&
					il.GetMousePos().y >= y1 && il.GetMousePos().y <= y2)
				{
					focus = glm::vec2(j, i);
					keyArray[i][j] = "?";
					hasFocus = true;
				}
			}
		}
	}

	if (hasFocus)
	{
		std::string s1 = il.GetKeyPressed();

		if (s1 != "")
		{
			hasFocus = false;
			int a = focus.y;
			int b = focus.x;

			keyArray[a][b] = s1;
		}
	}
}

Surface* Game::CameraRecord(Camera* cam)
{
	RECT camRECT;
	camRECT.top = cam->position.y - cam->height / 2;
	camRECT.bottom = cam->position.y + cam->height / 2;
	camRECT.left = cam->position.x - cam->width / 2;
	camRECT.right = cam->position.x + cam->width / 2;

	int a = cam->width;
	int b = cam->height;
	Surface* viewPane = new Surface(a, b);

	//1st layer back ground
	for (int i = 0; i <= cam->height / TILESIZE; i++)
	{
		for (int j = 0; j <= cam->width / TILESIZE; j++)
		{
			tf.Tiles[1]->TGraphic->CopyTo(viewPane, TILESIZE*j, TILESIZE*i);
			//imageTest.CopyTo(viewPane, *TILESIZE + camRECT.left, i*TILESIZE + camRECT.top);
		}
	}

	double aa, bb;
	int r = 0;
	//world
	for (int i = 0; i < worldGrid.size(); i++)
	{
		for (int j = 0; j < worldGrid[i].size(); j++)
		{
			if (worldGrid[i][j] == 0)
			{
				RECT t;
				t.top = i*TILESIZE;
				t.left = j*TILESIZE;
				t.bottom = t.top + TILESIZE;
				t.right = t.left + TILESIZE;

				//is tile within cam view
				if (t.left < camRECT.right && t.right > camRECT.left &&
					t.top < camRECT.bottom && t.bottom > camRECT.top)
				{
					if (r == 0)
					{
						aa = 0 + (j*TILESIZE - camRECT.left);
						bb = 0 + (i*TILESIZE - camRECT.top);
						r = 1;
					}

					double a = 0 + (j*TILESIZE - camRECT.left);
					double b = 0 + (i*TILESIZE - camRECT.top);

					tf.Tiles[worldGrid[i][j]]->TGraphic->CopyTo(viewPane, a, b);
				}
			}
		}
	}

	// record bubbles
	tree->Draw(camRECT, viewPane);

	//record bombs
	for (int i = 0; i < bombs.size(); i++)
	{
		bombs[i]->Draw(camRECT, viewPane);
	}

	//record ships
	for (int i = 0; i < playersList.size(); i++)
	{
		if (playersList[i]->position.x >= camRECT.left &&
			playersList[i]->position.x <= camRECT.right &&
			playersList[i]->position.y >= camRECT.top &&
			playersList[i]->position.y <= camRECT.bottom)
		{
			double a = playersList[i]->position.x + -camRECT.left;
			double b = playersList[i]->position.y + -camRECT.top;
			glm::vec2 pos(a, b);

			playersList[i]->Draw(viewPane, pos);
		}
	}

	return viewPane;
}

void Game::PlayGame()
{
	//update bubbles
	tree->Update();

	//update bom
	for (int it = 0; it < bombs.size(); it++)
	{
		if (bombs[it]->isHit)
		{
			bombs[it]->Update();
			//tree->CheckCollision(bombs[it]);

			//check player collsion
			for (int y = 0; y < playersList.size(); y++)
			{
				double r1 = bombs[it]->radius;
				double r2 = playersList[y]->radius;
				glm::vec2 p1 = bombs[it]->position;
				glm::vec2 p2 = playersList[y]->position;

				if (bombs[it]->CheckCircleCollision(r1, p1, r2, p2))
				{
					playersList[y]->velocity += glm::normalize(playersList[y]->position - bombs[it]->position);
					playersList[y]->speed = bombs[it]->blastspeed;
				}
			}

			//bubble collision
			for (int f = 0; f < Bubbles.size(); f++)
			{
				double r1 = bombs[it]->radius;
				double r2 = Bubbles[f]->radius;
				glm::vec2 p1 = bombs[it]->position;
				glm::vec2 p2 = Bubbles[f]->position;

				if (bombs[it]->CheckCircleCollision(r1, p1, r2, p2))
				{
					Bubbles[f]->velocity = glm::normalize(Bubbles[f]->position - bombs[it]->position);
					Bubbles[f]->speed = bombs[it]->blastspeed;
				}
			}

			//check bom with bom collsion
			for (int itt = 0; itt < bombs.size(); itt++)
			{
				if (it != itt)
				{
					double r1 = bombs[it]->radius;
					double r2 = bombs[itt]->radius;
					glm::vec2 p1 = bombs[it]->position;
					glm::vec2 p2 = bombs[itt]->position;

					if (bombs[it]->CheckCircleCollision(r1, p1, r2, p2))
					{
						bombs[itt]->isHit = true;
						//s->speed = -s->speed;
					}
				}
			}
		}

		/*for (int f = 0; f < Bubbles.size(); f++)
		{
		double r2 = Bubbles[f]->radius;
		glm::vec2 p2 = Bubbles[f]->position;

		for (int ff = 0; ff < Bubbles2.size(); ff++)
		{
		if (f != ff && Bubbles2[ff]->isWall && !Bubbles[f]->isWall)
		{
		double r1 = Bubbles2[ff]->radius;
		glm::vec2 p1 = Bubbles2[ff]->position;

		if (Bubbles2[ff]->CheckCircleCollision(r1, p1, r2, p2))
		{
		Bubbles[f]->speed = -Bubbles[f]->speed;
		}
		}
		}
		}
		*/
		if (bombs[it]->isKill)
		{
			delete bombs[it];
			bombs.erase(bombs.begin() + it);
		}
	}

	//update ships
	for (int i = 0; i < playersList.size(); i++)
	{
		if (!playersList[i]->isfinished)
		{
			playersList[i]->Update(route);
		}
		//check bom collision
		for (int k = 0; k < bombs.size(); k++)
		{
			if (!bombs[k]->isHit)
			{
				double r1 = bombs[k]->radius;
				double r2 = playersList[i]->radius;
				glm::vec2 p1 = bombs[k]->position;
				glm::vec2 p2 = playersList[i]->position;

				if (bombs[k]->CheckCircleCollision(r1, p1, r2, p2))
				{
					bombs[k]->isHit = true;
					//s->speed = -s->speed;
				}
			}
		}

		//check for collision
		tree->CheckCollision(playersList[i]);

		for (int j = 0; j < playersList.size(); j++)
		{
			if (j != i)
			{
				double r1 = playersList[i]->radius;
				double r2 = playersList[j]->radius;
				glm::vec2 p1 = playersList[i]->position;
				glm::vec2 p2 = playersList[j]->position;

				if (playersList[i]->CheckCircleCollision(r1, p1, r2, p2))
				{
					playersList[i]->position -= playersList[i]->velocity*playersList[i]->speed + playersList[i]->velocity*playersList[i]->speed;
					playersList[j]->position += playersList[i]->velocity*playersList[i]->speed + playersList[i]->velocity*playersList[i]->speed;
				}
			}
		}
	}

	//record and display
	//cams == players and first ships are players
	for (int i = 0; i < cams.size(); i++)
	{
		cams[i]->position = playersList[i]->position;
		Surface* s = CameraRecord(cams[i]);

		char points[50];

		int n, a = playersList[i]->laps;
		n = sprintf(points, "%d", a);

		s->CopyTo(screen, cams[i]->camView.left, cams[i]->camView.top);
		screen->Print(points, cams[i]->camView.left + 20, cams[i]->camView.top + 20, 0xffffff);

		//bars to devide screen
		switch (humans)
		{
		case 2:
			screen->Bar(0, SCRHEIGHT / 2 - 10, SCRWIDTH, SCRHEIGHT / 2 + 10, 0);
			break;
		case 3:
			screen->Bar(0, SCRHEIGHT / 2 - 10, SCRWIDTH, SCRHEIGHT / 2 + 10, 0);
			screen->Bar(SCRWIDTH / 2 - 10, SCRHEIGHT / 2, SCRWIDTH / 2 + 10, SCRHEIGHT - 1, 0);
			break;
		case 4:
			screen->Bar(0, SCRHEIGHT / 2 - 10, SCRWIDTH, SCRHEIGHT / 2 + 10, 0);
			screen->Bar(SCRWIDTH / 2 - 10, 0, SCRWIDTH / 2 + 10, SCRHEIGHT - 1, 0);
			break;
		}

		delete s;
	}
}

void Game::InitQuadTree()
{
	//init tree start
	RECT t;
	t.top = t.left = 0;
	t.right = worldWidth;
	t.bottom = worldHeight;
	tree = new QuadTree(t);

	Bubble* bub;
	//check what tile is an bubble
	for (int i = 0; i < worldGrid.size(); i++)
	{
		for (int j = 0; j < worldGrid[i].size(); j++)
		{
			if (worldGrid[i][j] == 3)// || worldGrid[i][j] > 4)
			{
				bub = new Bubble();

				double a = (j * TILESIZE) + (TILESIZE / 2);
				double b = (i * TILESIZE) + (TILESIZE / 2);

				bub->position = glm::vec2(a, b);
				bub->isWall = true;
				tree->Add(bub);
				Bubbles2.push_back(bub);
			}
			if (worldGrid[i][j] == 2)
			{
				bub = new Bubble();

				double a = (j * TILESIZE) + (TILESIZE / 4);
				double b = (i * TILESIZE) + (TILESIZE / 4);

				bub->position = glm::vec2(a, b);
				bub->setImage(bubimg);
				//bub->isWall = true;
				tree->Add(bub);
				Bubbles.push_back(bub);

				bub = new Bubble();

				a = (j * TILESIZE) + (TILESIZE / 4 * 3);
				b = (i * TILESIZE) + (TILESIZE / 4);

				bub->position = glm::vec2(a, b);
				bub->setImage(bubimg);
				//bub->isWall = true;
				tree->Add(bub);
				Bubbles.push_back(bub);

				bub = new Bubble();

				a = (j * TILESIZE) + (TILESIZE / 4);
				b = (i * TILESIZE) + (TILESIZE / 4 * 3);

				bub->position = glm::vec2(a, b);
				bub->setImage(bubimg);
				//bub->isWall = true;
				tree->Add(bub);
				Bubbles.push_back(bub);

				bub = new Bubble();

				a = (j * TILESIZE) + (TILESIZE / 4 * 3);
				b = (i * TILESIZE) + (TILESIZE / 4 * 3);

				bub->position = glm::vec2(a, b);
				bub->setImage(bubimg);
				//bub->isWall = true;
				tree->Add(bub);
				Bubbles.push_back(bub);
			}
		}
	}

	//ad bombs
	for (int i = 1; i < route.size(); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			Bom* bom = new Bom();
			double a = route[i].x + ((rand() % 400) - 200);
			double b = route[i].y + ((rand() % 400) - 200);

			bom->position = glm::vec2(a, b);
			bombs.push_back(bom);
		}
	}

	//add random bubble aroun the track

	for (int i = 1; i < route.size(); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			Bubble* bub = new Bubble();
			double a = route[i].x + ((rand() % 400) - 200);
			double b = route[i].y + ((rand() % 400) - 200);

			bub->position = glm::vec2(a, b);
			tree->Add(bub);
			Bubbles.push_back(bub);
		}
	}
}

void Game::InitShips()
{
	for (int i = 0; i < humans; i++)
	{
		playersList.push_back(new Ship());
		playersList[i]->SetKeys(keyArray[i][0],
			keyArray[i][1],
			keyArray[i][2]);
	}

	//init ai

	for (int i = humans; i < players; i++)
	{
		playersList.push_back(new Ship());
		playersList[i]->isAi = true;
	}

	//get start pos
	std::vector<glm::vec2> t = tb->getStartPos();

	for (int i = 0; i < playersList.size(); i++)
	{
		playersList[i]->position = t[i];
		playersList[i]->PlayerNumber = i + 1;
		playersList[i]->SetDest(route);

		float a = route[0].y - playersList[i]->linesPoints[0].y;
		float b = route[0].x - playersList[i]->linesPoints[0].x;
		float angle = std::atan2(a, b);

		double xx = angle / (PI * 2) * 360;

		if (xx > 10 && xx < 100)
		{
			playersList[i]->rotateLeft(90);
		}
		if (xx < 190 && xx> 100)
		{
			playersList[i]->rotateLeft(180);
		}
		if (xx > 190 && xx < 280)
		{
			playersList[i]->rotateLeft(270);
		}
	}
}

void Game::InitGame()
{
	screen->Clear(0);

	InitWorld();
	InitQuadTree();
	InitShips();
	InitCams();
}

void Game::Delete()
{
	for (int i = 0; i < playerfinish.size(); i++)
	{
		playerfinish.erase(playerfinish.begin() + i);
	}

	for (int i = 0; i < playersList.size(); i++)
	{
		delete playersList[i];
		playersList.erase(playersList.begin() + i);
	}

	for (int i = 0; i < cams.size(); i++)
	{
		delete cams[i];
		cams.erase(cams.begin() + i);
	}
	for (int i = 0; i < Bubbles.size(); i++)
	{
		delete Bubbles[i];
		Bubbles.erase(Bubbles.begin() + i);
	}

	//	delete tree;
}

void Game::InitWorld()
{
	tb = new TrackBuilder(screen);
	std::pair<Surface*, std::vector<glm::vec2>> p = tb->Load();

	//route
	route = p.second;

	//init world grid
	worldGrid = tf.getArray(p.first);

	worldWidth = worldGrid.size() * TILESIZE;
	worldHeight = worldGrid[0].size() * TILESIZE;

	delete tb;
}