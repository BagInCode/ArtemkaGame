#pragma once

#ifndef UNDER_LEVEL_2_1
#define UNDER_LEVEL_2_1

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

class Under_Level_2_1
{
	Font pauseFont;
	Text pauseText;

	RectangleShape plank;
	RectangleShape target;
	RectangleShape ball;

	Clock myClock;

	int FIELD[FIELD_HIGH_ARKANOID][FIELD_LENGTH_ARKANOID] =
	{
		0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0,
		0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 3, 0, 3, 0, 3, 0, 3, 0,
		0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0,
		0, 2, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 2, 0, 2, 0, 2, 0,
		0, 2, 2, 2, 2, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 2, 0, 2, 0,
		1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
		1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0
	};

	bool used[FIELD_HIGH_ARKANOID][FIELD_LENGTH_ARKANOID] = { 0 };
	bool start = 0;
	bool pause = 0;
	bool keyAPressed = 0;
	bool keyDPressed = 0;

	int countTargets = 95;
	int countLives = 2;

	double speed = 2;

	double ballVectorX = 0;
	double ballVectorY = -1;
	double positionBallX = 645;
	double positionBallY = 590;

	double plankPositionX = 600;
	double plankPositionY = 600;
	int plankVector = 0;

	double pi = acos(-1);

	void makeSpries();
	void drawPicture(RenderWindow & window);
	void switchEvent(Event & event, RenderWindow & window, Music & music);
	void makePause(Music & music);
	bool checkTime(RenderWindow & window);
	void makePauseTextTTC();;
	void restart(RenderWindow & window);
	void moveObjects(double timer, RenderWindow & window);
	void moveBall(double timer);
	void movePlank(double timer);
	void checkIntersect(RenderWindow & window);

public:
	void game(RenderWindow & window, Music & music);
	Under_Level_2_1();
	~Under_Level_2_1();
};

#endif
