#pragma once
#ifndef CUT_SCENE_2_2
#define CUT_SCENE_2_2

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

class Cut_Scene_2_2
{
	Texture texturesEnviroment;
	Texture texturesOther;
	Texture texturesAlice;

	Sprite ScientistSprite;
	Sprite ScientistHeadSprite;
	Sprite AliceSprite;
	Sprite AliceHeadSprite;
	Sprite BackGroundSprite;

	bool movingIsOver = 0;
	bool pause = 0;

	double positionAliceX = ALICE_FINISH_POSITION_IN_CUT_SCENE;
	double positionAliceY = MIN_ALICE_DOWN_POSITION;

	double positionScientistX = SQUIRREL_START_POSITION_IN_CUT_SCENES;
	double positionScientistY = MIN_ALICE_DOWN_POSITION;

	double timerRunningPhoto_S = 0;
	int pointerRunningTexture_S = 0;
	int ScientistVector = -1;

	double timerStay = 0;

	Clock myClock;

	RectangleShape dialogField;
	RectangleShape replicField;

	Vector2f vector1;

	Font font;
	Text text;

	int dialogPointer = 0;

	string replics[5] =
	{
		"O my God! You have done this!",
		"Nobody can do it for 100 years!",
		"I have to help you! Get this arrmor!",
		"And this weapon!",
		"Em... Thank you"
	};

	void makeSprites();
	void checkTime(RenderWindow & window);
	void moveObjects(double timer);
	void moveScientist(double timer);
	void drawPicture(RenderWindow & window);
	bool switchEvent(Event event, RenderWindow & window, Music & music);
	void makeTextTTC();
	void dialog();
	void drawDialog(RenderWindow & window);

public:
	Cut_Scene_2_2();
	void play(RenderWindow & window, Music & music);
	~Cut_Scene_2_2();
};

#endif
