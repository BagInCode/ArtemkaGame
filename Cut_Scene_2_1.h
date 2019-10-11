#pragma once
#ifndef CUT_SCENE_2_1
#define CUT_SCENE_2_1

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


class Cut_Scene_2_1
{
private:
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
	
	double positionAliceX = ALICE_START_POSITION_IN_CUT_SCENES;
	double positionAliceY = MIN_ALICE_DOWN_POSITION;
	
	int pointerRunningTexture = 0;
	double timerRunningPhoto = 0;
	int AliceVector = 1;

	double positionScientistX = SQUIRREL_START_POSITION_IN_CUT_SCENES;
	double positionScientistY = MIN_ALICE_DOWN_POSITION;

	double timerRunningPhoto_S = 0;
	int pointerRunningTexture_S = 0;
	int ScientistVector = 0;

	double timerStay = 0;

	Clock myClock;

	RectangleShape dialogField;
	RectangleShape replicField;

	Vector2f vector1;

	Font font;
	Text text;

	int dialogPointer = 0;

	string replics[4] = 
	{
		"Good morning, Scientist.",
		"Good time of day, lady.",
		"I need weapon to get dragons tooth, can you help me?",
		"Ou. You should show that you are clever, win the Game."
	};

	void makeSprites();
	void checkTime(RenderWindow & window);
	void moveObjects(double timer);
	void moveAlice(double timer);
	void moveScientist(double timer);
	void drawPicture(RenderWindow & window);
	bool switchEvent(Event event, RenderWindow & window, Music & music);
	void makeTextTTC();
	void dialog();
	void drawDialog(RenderWindow & window);
	void makeSound(Music & music);

public:
	Cut_Scene_2_1();
	void play(RenderWindow & window, Music & music);
	~Cut_Scene_2_1();
};

#endif