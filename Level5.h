#pragma once

#ifndef LEVEL5
#define LEVEL5

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
#include "Cut_Scene_5_1.h"
#include "Cut_Scene_5_2.h"

using namespace sf;
using namespace std;

class Level5
{
	Cut_Scene_5_1 Cut_Scene_5_1_Object;
	Cut_Scene_5_2 Cut_Scene_5_2_Object;

public:
	Level5();
	~Level5();

	void game(RenderWindow & window, Music & music);
};

#endif
