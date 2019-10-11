#pragma once

#ifndef CUT_SCENE_1_2
#define CUT_SCENE_1_2

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
#include "Constants.db"
#include "Cut_Scene_1_2_1.h"
#include "Cut_Scene_1_2_2.h"

using namespace std;
using namespace sf;

class Cut_Scene_1_2
{
private:
	Cut_Scene_1_2_1 Cut_Scene_1_2_1_Object;
	Cut_Scene_1_2_2 Cut_Scene_1_2_2_Object;

public:
	void play(RenderWindow & window, Music & music);
	Cut_Scene_1_2();
	~Cut_Scene_1_2();
};

#endif