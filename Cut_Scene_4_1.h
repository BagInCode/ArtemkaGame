#pragma once

#pragma once
#ifndef CUT_SCENE_4_1
#define CUT_SCENE_4_1

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

class Cut_Scene_4_1
{
private:

	Sprite AliceSprite;
	Sprite AliceHeadSprite;
	Texture textures;

	string replics[5]
	{
		"Yes! I have run away",
		"But where am I?",
		"It.. It.. It`s PacMans` world!",
		"I.. I.. I change!",
		"Nooo!"
	};

	bool movingIsOver = 0;
	bool pause = 0;

	double positionAliceX = ALICE_START_POSITION_IN_CUT_SCENES;
	double positionAliceY = MIN_ALICE_DOWN_POSITION;
	
	double timerRunningPhoto = 0;

	int pointerRunningTexture = 0;
	int dialogPointer = 0;
	
	int AliceVector = 1;

	double timerStay = 0;

	Clock myClock;

	RectangleShape dialogField;
	RectangleShape replicField;

	Vector2f vector1;

	Font font;
	Text text;

	bool finalScreen = 0;

	void makeSound(Music & music);
	void makeSprites();
	void checkTime(RenderWindow & window);
	void moveObjects(double timer);
	void moveAlice(double timer);
	void drawPicture(RenderWindow & window);
	bool switchEvent(Event event, RenderWindow & window, Music & music);
	void makeTextTTC();
	void dialog();
	void drawDialog(RenderWindow & window);

public:
	Cut_Scene_4_1();

	void play(RenderWindow & window, Music & music);

	~Cut_Scene_4_1();
};

#endif