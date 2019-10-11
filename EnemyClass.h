#pragma once

#ifndef ENEMY_PACMAN
#define ENEMY_PACMAN

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

class EnemyClass
{
private:
	Texture texture;
	Sprite sprite;

	double positionSpriteY = 0;

	double speed = 1;

	int lastChangedX = 0;
	int lastChangedY = 0;

	int positionX = 0;
	int positionY = 0;

	int vectorX = 0;
	int vectorY = 0;

	double timerMoving = 0;
	double timerScered = 0;

	bool kill = 0;
	bool sceared = 0;

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
	void setTexture();
	void setSpeedVector(int newVectorX, int newVectorY);
	void setPicture();
	void setPosition(int newX, int newY);
	void setTurn();
	void setColor(int color);
	void setKill();
	pair < int, int > getPosition();
	pair < int, int > getSpeedVector();
	bool getKill();
	bool getSceared();
	void checkMove();
	void move(double timer);
	void initialization(int color, int positionX, int positionY);
	void draw(RenderWindow & window);
	void makeSceared();
	void makeUnsceared();
	EnemyClass();
	~EnemyClass();
};

#endif
