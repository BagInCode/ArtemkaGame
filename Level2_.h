#pragma once

#ifndef LEVEL2_
#define LEVEL2_

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
#include "Cut_Scene_2_1.h"
#include "Cut_Scene_2_2.h"
#include "Under_Level_2_1.h"

using namespace sf;
using namespace std;

class Level2_
{
private:

	Under_Level_2_1 Under_Level_2_1_Object;
	Cut_Scene_2_1 Cut_Scene_2_1_Object;
	Cut_Scene_2_2 Cut_Scene_2_2_Object;

public:
	void game(RenderWindow & window, Music & music);
	Level2_();
	~Level2_();
};

#endif;

