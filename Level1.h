#pragma once

#ifndef LEVEL1
#define LEVEL1

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <algorithm>
#include <math.h>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <time.h>
#include <random>
#include <fstream>
#include "Constants.db"
#include "Under_Level_1_1.h"
#include "Under_Level_1_2.h"
#include "Cut_Scene_1_1.h"
#include "Cut_Scene_1_2.h"
#include "Cut_Scene_1_3.h"

using namespace sf;
using namespace std;

class Level1
{
private:
	Music music;

	Under_Level_1_2 Under_Level_1_2_Object;
	Under_Level_1_1 Under_Level_1_1_Object;

	Cut_Scene_1_1 Cut_Scene_1_1_Object;
	Cut_Scene_1_2 Cut_Scene_1_2_Object;
	Cut_Scene_1_3 Cut_Scene_1_3_Object;

public:
	void game(RenderWindow & window, Music & music);
	Level1();
	~Level1();
};

#endif;

