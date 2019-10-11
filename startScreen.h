#pragma once

#ifndef START_SCREEN
#define START_SCREEN

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

class startScreen
{
	Texture texturesAlice;
	Texture texturesDargon;

	Sprite AliceSprite;
	Sprite DragonSprite;
	Sprite AliceHeadSprite;

	CircleShape Circle;

	double positionAliceX = -1000;
	double positionAliceY = 0;

	double positionDragonX = -1000;
	double positionDragonY = 0;

	double vectorAliceX = 0;
	double vectorAliceY = 0;

	double vectorDragonX = 0;
	double vectorDragonY = 0;

	double timerRunningPhotoAlice = 0;
	double timerRunningPhotoDragon = 0;

	int pointerRunningTextureAlice = 0;
	int pointerRunningTextureDragon = 0;

	Font font;
	Text text;
	Clock myClock;

	bool pause = 0;
	bool secondScreen = 0;
	bool inverseAlice = 0;
	bool inverseDragon = 0;

	double pi = acos(-1);

	double mas[12] = {pi/6, pi/4, pi/3, 2*pi/3, 3*pi/4, 5*pi/6, 7*pi/6, 5*pi/4, 4*pi/3, 5*pi/3, 7*pi/4, 11*pi/6};

	void makeSprites();
	void moveObjects(double timer);
	bool switchEvent(Event event, RenderWindow & window);
	void moveAlice(double timer);
	void moveDragon(double timer);
	void makeTextTTC();
	void checkTime(RenderWindow & window);
	void drawPicture(RenderWindow & window);
	void checkAlice();
	void checkDragon();

public:
	
	void start(RenderWindow & window);
	startScreen();
	~startScreen();
};

#endif
