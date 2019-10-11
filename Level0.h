#pragma once

#ifndef LEVEL0
#define LEVEL0

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
#include "Cut_Scene_0_1.h"
#include "Cut_Scene_0_2.h"

using namespace sf;
using namespace std;

class Level0
{
	Cut_Scene_0_1 Cut_Scene_0_1_Object;
	Cut_Scene_0_2 Cut_Scene_0_2_Object;

public:
	Level0();
	~Level0();

	void game(RenderWindow & window, Music & music);
};

#endif
