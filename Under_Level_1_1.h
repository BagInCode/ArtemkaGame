#pragma once

#ifndef UNDER_LEVEL_1_1
#define UNDER_LEVEL_1_1

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

class Under_Level_1_1
{
private:
	Music music;

	Sprite AliceSprite;
	Sprite backGroundSprite;
	Sprite cloudSprite;
	Sprite sunSprite;
	Sprite groundSprite;
	Sprite ArchSprite[COUNT_ARCHS];
	Sprite nameplateSprite;

	Texture texturesAlice;
	Texture texturesEnviroment;

	Text text;
	Font font;

	Font pauseFont;
	Text pauseText;

	Clock myClock;

	int trueFinish = 32;

	int answers[COUNT_PROBLEMS] = {3,2,2,1,3,3,1,1,2,2,2,3,2};

	string problems[COUNT_PROBLEMS] =
	{
	"sqrt(4)=?",
	"Count Dolmatins\nmod 100?",
	"A+A=4\nA/2=?",
	"68=3  42=1\n90=2  11=?",
	"dog=4 chicken=2\ncow=4 parrot=?",
	"pow(8, 1/3)=?",
	"arcsin(sin(pi))=?",
	"arccos(0)=?",
	"sign(5)=?",
	"e^ln(1)=?",
	"[1.5]=?",
	"2!=?",
	"lim(sin(x)/x)=?\nx->0"
	};

	double positionAliceX = MIN_ALICE_LEFT_POSITION;
	double positionAliceY = MIN_ALICE_DOWN_POSITION;
	double boostAlice = 0;
	double timer = 0;
	double timerRunningPhoto = 0;
	double cloudUpperPointer = 0;
	double cloudDownerPointer = 0;

	int AliceVector = 0;
	int pointerAliceStay = 0;
	int pointerRunningTexture = 0;

	bool AliceJump = 0;
	bool AliceDownJump = 0;
	bool pause = 0;

	bool keyWPressed = 0;
	bool keyAPressed = 0;
	bool keySPressed = 0;
	bool keyDPressed = 0;

	void makeSprites();
	void makePause(Music & music);
	void makeTextTTC();
	bool checkPath(RenderWindow & window);
	void andAgain();
	void checkTime(RenderWindow & window);
	void moveAlice(double timer);
	void moveClouds(double timer);
	void moveObjects(double timer);
	void drawPicture(RenderWindow & window);
	void makePauseTextTTC();
	void restart(RenderWindow & window); 
	bool switchEvent(Event event, RenderWindow & window, Music & music);
	void makeSound(Music & music);

public:
	void game(RenderWindow & window, Music & music);
	Under_Level_1_1();
	~Under_Level_1_1();
};

#endif

