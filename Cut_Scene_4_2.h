#pragma once

#ifndef CUT_SCENE_4_2
#define CUT_SCENE_4_2

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

using namespace std;
using namespace sf;

class Cut_Scene_4_2
{
private:
	Texture texturesAlice;
	Texture texturesEnviroment;
	Texture texturesDargon;

	Sprite AliceSprite;
	Sprite cloudSprite;
	Sprite groundSprite;
	Sprite sunSprite;
	Sprite backGroundSprite;
	Sprite DragonSprite;
	Sprite AliceHeadSprite;
	Sprite DragonHeadSprite;

	Font font;
	Text text;

	RectangleShape dialogField;
	RectangleShape replicField;

	Vector2f vector1;

	double timer = 0;

	double positionAliceX = ALICE_START_POSITION_IN_CUT_SCENES;
	double positionAliceY = MIN_ALICE_DOWN_POSITION;
	double timerRunningPhoto = 0;

	double cloudUpperPointer = 0;
	double cloudDownerPointer = 0;

	double timerStay = 0;

	int pointerRunningTexture = 0;
	int AliceVector = 1;

	int dialogPointer = 0;

	Clock myClock;

	bool pause = 0;
	bool movingIsOver = 0;

	string replics[6] =
	{
		"Muahaha!!",
		"I`ll get your tooth and do my mission!",
		"You need only tooth all this time?",
		"Yes.",
		"Why you don`t tell to me?",
		"I have one ill, get it!"
	};

	void makeSound(Music & music);
	void makeSprites();
	void drawDialog(RenderWindow & window);
	void moveObjects(double timer);
	bool switchEvent(Event event, RenderWindow & window, Music & music);
	void moveClouds(double timer);
	void moveAlice(double timer);
	void dialog();
	void makeTextTTC();
	void checkTime(RenderWindow & window);
	void drawPicture(RenderWindow & window);

public:
	void play(RenderWindow & window, Music & music);
	Cut_Scene_4_2();
	~Cut_Scene_4_2();
};

#endif