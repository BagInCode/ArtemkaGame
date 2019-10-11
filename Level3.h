#pragma once

#ifndef LEVEL3
#define LEVEL3

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
#include "Cut_Scene_3_1.h"
#include "Cut_Scene_3_2.h"
#include "Under_level_3_1.h"
#include "Under_Level_3_2.h"

using namespace sf;
using namespace std;

class Level3
{
private:
	Music music;

	Cut_Scene_3_1 Cut_Scene_3_1_Object;
	Cut_Scene_3_2 Cut_Scene_3_2_Object;
	Under_Level_3_1 Under_Level_3_1_Object;
	Under_Level_3_2 Under_Level_3_2_Object;

public:
	void game(RenderWindow & window, Music & music);
	Level3();
	~Level3();
};



#endif