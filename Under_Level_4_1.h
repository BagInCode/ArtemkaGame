#pragma once

#ifndef UNDER_LEVEL_4_1
#define UNDER_LEVEL_4_1

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
#include "EnemyClass.h"
#include "PacManClass.h"
#include "Constants.db"

using namespace sf;
using namespace std;

class Under_Level_4_1
{
private:
	Font font;
	Text text;

	Texture texture;
	Sprite walls;
	Sprite eatMe;

	Clock myClock;

	Font pauseFont;
	Text pauseText;

	EnemyClass enemy[4];
	PacManClass pacman;

	bool pause = 0;

	pair < int, int > positionsEstMe[4];
	bool usedEatMe[4];

	int cntKill = 0;

	int FIELD[FIELD_HEIGH][FIELD_LENGTH] =
	{
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,
		1,0,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,0,1,
		1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1,
		1,1,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,1,
		1,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,1,
		1,0,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,0,1,
		1,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,
		1,0,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,0,1,
		1,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,1,
		1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1,
		1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,
		1,0,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,0,1,
		1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,
		1,1,0,1,0,1,0,1,1,1,1,1,0,1,0,1,0,1,1,
		1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1,
		1,0,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
	};

	void makeSound(Music & music);
	void makeSpries();
	void drawPicture(RenderWindow & window);
	void switchEvent(Event & event, RenderWindow & window, Music & music);
	void makePause(Music & music);
	bool checkTime(RenderWindow & window);
	bool move(double timer, RenderWindow & window);
	void createEnemies();
	void initializationEatMe();
	void makePauseTextTTC();
	void restart(RenderWindow & window);
	void checkEatMe();
	bool checkIntesect(RenderWindow & window);
	void makeTextTTC();
	void setString();
public:
	void game(RenderWindow & window, Music & music);
	Under_Level_4_1();
	~Under_Level_4_1();
};

#endif