#pragma once

#ifndef CUT_SCENE_5_2
#define CUT_SCENE_5_2

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

class Cut_Scene_5_2
{
	Sprite MomSprite;
	Sprite AliceHomeSprite;
	Sprite OtherHomeLeftSprite;
	Sprite OtherHomeRightSprite;
	Sprite AliceHeadSprite;
	Sprite AliceMomHeadSprite;
	Sprite cloudSprite;

	Texture texturesAlice;
	Texture texturesEnviroment;
	Texture texturesOther;

	bool movingIsOver = 0;
	bool pause = 0;

	double positionAliceMomX = ALICE_MOM_START_POSITION;
	double positionAliceMomY = MIN_ALICE_DOWN_POSITION;

	int pointerRunningTexture = 0;
	double timerRunningPhoto = 0;
	int AliceMomVector = 1;

	double timerStay = 0;

	double cloudUpperPointer = 0;
	double cloudDownerPointer = 0;

	Clock myClock;

	RectangleShape dialogField;
	RectangleShape replicField;

	Vector2f vector1;

	Font font;
	Text text;

	int dialogPointer = 0;

	string replics[6] =
	{
		"Alice",
		"Alice, doughter",
		"it is time to stand up",
		"let`s go to kindergarten",
		"What?",
		"It was only a dream?"
	};

	void makeSprites();
	void checkTime(RenderWindow & window);
	void moveObjects(double timer);
	void moveAliceMom(double timer);
	void drawPicture(RenderWindow & window);
	bool switchEvent(Event event, RenderWindow & window, Music & music);
	void makeTextTTC();
	void dialog();
	void drawDialog(RenderWindow & window);
	void moveClouds(double timer);
public:
	Cut_Scene_5_2();
	void play(RenderWindow & window, Music & music);
	~Cut_Scene_5_2();
};

#endif

