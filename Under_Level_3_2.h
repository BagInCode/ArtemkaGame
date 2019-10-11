#pragma once

#ifndef UNDER_LEVEL_3_2
#define UNDER_LEVEL_3_2

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

using namespace sf;
using namespace std;

class Under_Level_3_2
{
private:
	Music music;

	Texture texturesEnviroment;
	Texture texturesAlice;
	Texture texturesDragon;

	Sprite AliceSprite;
	Sprite cloudSprite;
	Sprite groundSprite;
	Sprite sunSprite;
	Sprite backGroundSprite;
	Sprite cactusSprite;

	Font pauseFont;
	Text pauseText;

	double timer = 0;

	double positionAliceX = MIN_ALICE_LEFT_POSITION;
	double positionAliceY = MIN_ALICE_DOWN_POSITION;
	double timerRunningPhoto = 0;
	double boostAlice = 0;

	double cloudUpperPointer = 0;
	double cloudDownerPointer = 0;
	
	double backGroundDisplacement = 0;
	double globalDisplacement = 0;

	int pointerRunningTexture = 0;
	int AliceVector = 0;

	double groundDisplacement = 0;

	Clock myClock;

	bool pause = 0;
	bool AliceJump = 0;
	bool AliceDownJump = 0;
	bool keyWPressed = 0;
	bool keyAPressed = 0;
	bool keySPressed = 0;
	bool keyDPressed = 0;

	vector < pair < int, int > > cactusesPositions;

	void makeSprites();
	void generateCactusesPosition();
	void makePause(Music & music);
	void moveAlice(double timer);
	void moveClouds(double timer);
	void restart(RenderWindow & window);
	void checkIntersect(RenderWindow & window);
	void moveObjects(RenderWindow & window, double timer);
	void drawPicture(RenderWindow & window);
	bool switchEvent(Event event, RenderWindow & window, Music & music);
	void checkTime(RenderWindow & window);

public:

	void game(RenderWindow & window, Music & music);
	Under_Level_3_2();
	~Under_Level_3_2();
};

#endif