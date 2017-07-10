#pragma once

#include "template.h"
#include "surface.h"

#include <vector>
#include "Trackpiece.h"
#include "InputListener.h"
#include <string>
#include <iostream>
#include <stdio.h>

#include <fstream>
#include <sstream>      // std::stringstream


namespace Tmpl8 {
	class TrackBuilder
	{
	public:
		TrackBuilder(Surface* screen);
		TrackBuilder(){};
		~TrackBuilder();

		int Update();
		void Draw();
		void SelectTile();
		void switchTile();
		void Save();
		void RotateTile();
		std::pair<Surface*, std::vector<glm::vec2> > Load();
		std::vector<glm::vec2> getStartPos();

		int HandleMenu();



		int tilesize = 64;
		Surface* screen;
		Surface* map = new Surface(tilesize * 10 + 1, tilesize * 9 + 1);
		Surface* previewPane = new Surface(tilesize, tilesize); //each trackpiece is 320x320

		std::vector<Trackpiece*> tracks;
		int index = 0;

		glm::vec2 mapgrid[9][10];
		InputListener il;

		bool holdstile = false;
		glm::vec2 trackpiece; // wich one and index

		bool startPlaced = false;

		std::vector<glm::vec2> trackRoute;
		std::vector<glm::vec2> startPositions;


	};
}