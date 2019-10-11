#pragma once

#ifndef PAC_MAN_CLASS
#define PAC_MAN_CLASS

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

class PacManClass
{
private:
	Texture texture;
	Sprite sprite;

	int positionX = 0;
	int positionY = 0;

	int vectorX = 0;
	int vectorY = 0;

	int nextVectorX = 0;
	int nextVectorY = 0;

	double timerMoving = 0;
	double timerPicture = 0;

	bool openMouth = 0;

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

public:
	void setSpeedVector(int newVectorX, int newVectorY);
	void setPosition(int newX, int newY);
	void setPicture();
	void setTexture();
	pair < int, int > getPosition();
	pair < int, int > getSpeedVector();
	void checkMove();
	void move(double timer);
	void checkTurn(bool zeroVal = 0);
	void initialization(int positionX, int positionY);
	void draw(RenderWindow & window);
	PacManClass();
	~PacManClass();
};

#endif
