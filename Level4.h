#pragma once

#ifndef LEVEL4
#define LEVEL4

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <math.h>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <time.h>
#include <random>
#include <fstream>
#include "Constants.db"
#include "Under_Level_4_1.h"
#include "Cut_Scene_4_1.h"
#include "Cut_Scene_4_2.h"

using namespace sf;
using namespace std;

class Level4
{
private:
	Under_Level_4_1 Under_Level_4_1_Object;
	Cut_Scene_4_1 Cut_Scene_4_1_Object;
	Cut_Scene_4_2 Cut_Scene_4_2_Object;

public:
	void game(RenderWindow & window, Music & music);

	Level4();
	~Level4();
};

#endif