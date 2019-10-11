#pragma once

#ifndef CUT_SCENE_3_2
#define CUT_SCENE_3_2

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

class Cut_Scene_3_2
{
private:
	Texture texturesAlice;
	Texture texturesDragon;
	Texture texturesEnviroment;

	Sprite AliceSprite;
	Sprite cloudSprite;
	Sprite groundSprite;
	Sprite sunSprite;
	Sprite backGroundSprite;
	Sprite DragonSprite;
	Sprite AliceHeadSprite;
	Sprite DragonHeadSprite;

	double timer = 0;
	double timerRunningPhoto = 0;

	double positionDragonX = 600;
	double positionDragonY = MIN_DRAGON_DOWN_POSITION;
	double boostDragon = DRAGON_BOOST / 3;

	double positionAliceX = ALICE_FINISH_POSITION_IN_CUT_SCENE;
	double positionAliceY = MIN_ALICE_DOWN_POSITION;

	double cloudUpperPointer = 0;
	double cloudDownerPointer = 0;

	double timerStay = 0;

	int pointerRunningTexture = 0;
	int pointerDragonTexture = 0;

	int AliceVector = 0;
	int dragonVector = 0;

	int orientation = 1;

	double timerDragonFly = 0;

	int dialogPointer = 0;

	Clock myClock;

	bool pause = 0;
	bool movingIsOver = 0;

	void makeSound(Music & music);
	void makeSprites();
	void moveDragon(double timer);
	void moveAlice(double timer);
	void moveObjects(double timer);
	bool switchEvent(Event event, RenderWindow & window, Music & music);
	void moveClouds(double timer);
	void checkTime(RenderWindow & window);
	void drawPicture(RenderWindow & window);

public:
	void play(RenderWindow & window, Music & music);
	Cut_Scene_3_2();
	~Cut_Scene_3_2();
};

#endif
