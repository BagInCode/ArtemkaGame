#pragma once

#ifndef CUT_SCENE_1_3
#define CUT_SCENE_1_3

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

class Cut_Scene_1_3
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

	double positionDragonX = 600;
	double positionDragonY = MIN_DRAGON_DOWN_POSITION;
	double boostDragon = DRAGON_BOOST / 3;

	double cloudUpperPointer = 0;
	double cloudDownerPointer = 0;

	double timerStay = 0;

	int pointerRunningTexture = 0;
	int pointerDragonTexture = 0;

	double timerDragonFly = 0;

	int dialogPointer = 0;

	Clock myClock;

	bool pause = 0;
	bool movingIsOver = 0;
	bool finalScreen = 0;

	string replics[3] =
	{
		"No! Where are you going?! Stop!",
		"Stop I say! I have to get your tooth!",
		"Agr! No, it doesn`t work, I have to get a gun..."
	};

	void makeSprites();
	void moveDragon(double timer);
	void drawDialog(RenderWindow & window);
	void moveObjects(double timer);
	bool switchEvent(Event event, RenderWindow & window, Music & music);
	void moveClouds(double timer);
	void dialog();
	void makeTextTTC();
	void checkTime(RenderWindow & window);
	void drawPicture(RenderWindow & window);

public:
	void play(RenderWindow & window, Music & music);
	Cut_Scene_1_3();
	~Cut_Scene_1_3();
};

#endif
