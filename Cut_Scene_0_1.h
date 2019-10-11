#pragma once

#ifndef CUT_SCENE_0_1
#define CUT_SCENE_0_1

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

class Cut_Scene_0_1
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

	string replics[10] =
	{
		"Mom, read me the fairytale please",
		"Ok, listen.",
		"Long long time ago...",
		"...",
		"and knight defiet Dragon, and safe princes",
		"Good night, Alice.",
		"Good night Mom",
		"And they wiil have children",
		"And will be they Artemoviches...",
		"I have no Artemovich in friend!"
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
	void makeSound(Music & music);

public:
	Cut_Scene_0_1();
	void play(RenderWindow & window, Music & music);
	~Cut_Scene_0_1();
};

#endif

