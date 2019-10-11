#pragma once
#ifndef CUT_SCENE_1_1
#define CUT_SCENE_1_1

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

class Cut_Scene_1_1
{
private:
	Sprite groundSprite;
	Sprite backGroundSprite;
	Sprite cloudSprite;
	Sprite sunSprite;
	Sprite squirrelSprite;
	Sprite AliceHeadSprite;
	Sprite squirrelHeadSprite;
	Sprite AliceSprite;

	Texture texturesEnviroment;
	Texture texturesAlice;
	Texture texturesOther;

	Font font;
	Text text;

	Clock myClock;

	RectangleShape dialogField;
	RectangleShape replicField;

	Vector2f vector1;
		
	double positionSquirrelX = SQUIRREL_START_POSITION_IN_CUT_SCENES;
	double positionSquirrelY = MIN_ALICE_DOWN_POSITION;

	double timer = 0;
	double timerStay = 0;

	double timerRunningPhoto_S = 0;

	double cloudUpperPointer = 0;
	double cloudDownerPointer = 0;

	int squirrelVector = 0;

	int pointerRunningTexture_S = 0;

	int dialogPointer = 0;

	bool pause = 0;
	bool movingIsOver = 0;

	int AliceVector = 1;
	int pointerRunningTexture = 0;

	double timerRunningPhoto = 0;
	double positionAliceX = ALICE_START_POSITION_IN_CUT_SCENES;
	double positionAliceY = MIN_ALICE_DOWN_POSITION;

	string replics[7] =
	{
		"Hi, squirrel! Can you help me?",
		"Hi girl, how can i help you?",
		"I need tooth of the Dragon! Do you have any dragons there?",
		"But you need some special instruments.",
		"Oh, yeah! Do you have any sword there?",
		"Yes, but deep in forest.",
		"Oh! Thank you!"
	};

	void makeSprites();
	void checkTime(RenderWindow & window);
	void moveObjects(double timer);
	void moveAlice(double timer);
	void moveSquirrel(double timer);
	void moveClouds(double timer);
	void drawPicture(RenderWindow & window);
	bool switchEvent(Event event, RenderWindow & window, Music & music);
	void makeTextTTC();
	void dialog();
	void drawDialog(RenderWindow & window);
	void makeSound(Music & music);
public:

	void play(RenderWindow & window, Music & music);
	Cut_Scene_1_1();
	~Cut_Scene_1_1();
};

#endif