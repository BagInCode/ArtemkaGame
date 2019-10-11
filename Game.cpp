#pragma once

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <math.h>
#include <cmath>
#include <iomanip>
#include <iostream>

#include "startScreen.h"
#include "Level0.h"
#include "Level1.h"
#include "Level2_.h"
#include "Level3.h"
#include "Level4.h"
#include "Level5.h"

using namespace sf;
using namespace std;

const string WINDOW_NAME = "ArtemkaGame";

class Game
{
private:
	startScreen startScreen_Object;
	Level0 Level0_Object;
	Level1 Level1_Object;
	Level2_ Level2_Object;
	Level3 Level3_Object;
	Level4 Level4_Object;
	Level5 Level5_Object;

public:
	void play()
	{
		RenderWindow window(VideoMode(WINDOW_LENGTH, WINDOW_HEIGH), WINDOW_NAME);
		window.setKeyRepeatEnabled(false);

		Music music;

		startScreen_Object.start(window);
		Level0_Object.game(window, music);
		Level1_Object.game(window, music);
		Level2_Object.game(window, music);
		Level3_Object.game(window, music);
		Level4_Object.game(window, music);
		Level5_Object.game(window, music);

		return;
	}
};

Game Game_Object;


int main()
{
	Game_Object.play();

	return 0;
}