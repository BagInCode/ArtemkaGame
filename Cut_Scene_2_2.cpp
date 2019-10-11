#include "Cut_Scene_2_2.h"

Cut_Scene_2_2::Cut_Scene_2_2()
{
}


Cut_Scene_2_2::~Cut_Scene_2_2()
{
}


void Cut_Scene_2_2::makeSprites()
{
	/*
	* function of loading pictures in sprites
	*/
	texturesAlice.loadFromFile("textures\\AliceTexture.png");

	AliceHeadSprite.setTexture(texturesAlice);
	AliceHeadSprite.setTextureRect(IntRect(POSITION_ALICE_HEAD_PHOTO_LEFT, POSITION_ALICE_HEAD_PHOTO_TOP, HEAD_PHOTO_LENGTH, HEAD_PHOTO_HIGH));

	AliceSprite.setTexture(texturesAlice);
	AliceSprite.setTextureRect(IntRect(POSITION_ALICE_PHOTO_LEFT, POSITION_ALICE_PHOTO_TOP, ALICE_PHOTO_LENGTH - 1, ALICE_PHOTO_HIGH));

	texturesOther.loadFromFile("textures\\OtherCharactersTexture.png");

	ScientistHeadSprite.setTexture(texturesOther);
	ScientistHeadSprite.setTextureRect(IntRect(POSITION_SCIENTIST_HEAD_LEFT, POSITION_SCIENTIST_HEAD_TOP, HEAD_PHOTO_LENGTH, HEAD_PHOTO_HIGH));

	ScientistSprite.setTexture(texturesOther);
	ScientistSprite.setTextureRect(IntRect(POSITION_SCIENTIST_LEFT, POSITION_SCIENTIST_TOP, SCIENTIST_LENGTH, SCIENTIST_HIGH));

	texturesEnviroment.loadFromFile("textures\\EnviromentTexture.png");

	BackGroundSprite.setTexture(texturesEnviroment);
	BackGroundSprite.setTextureRect(IntRect(POSITION_SCIENTIST_BACKGROUND_LEFT, POSITION_SCIENTIST_BACKGROUND_TOP, SCIENTIST_BACKGROUND_LENGTH, SCIENTIST_BACKGROUND_HIGH));

	return;
}

void Cut_Scene_2_2::checkTime(RenderWindow & window)
{
	/*
	* function of checking time
	*/

	double timer;

	/// if too much time has passed - restart timer, move objects, draw picture
	if (myClock.getElapsedTime().asMilliseconds() > MILLI_SECOND_FOR_ACTION)
	{
		timer = myClock.restart().asMilliseconds();

		moveObjects(timer);
		drawPicture(window);
	}

	return;
}

void Cut_Scene_2_2::moveObjects(double timer)
{
	/*
	* function of updating position of all moving objects
	*/

	/// if pause - goodbye
	if (pause)
	{
		return;
	}

	/// move Alice
	moveScientist(timer);

	/// if moving is over - increse value of timer stay
	if (movingIsOver)
	{
		timerStay += timer;

		/// if we stay too long - don`t make value too much big
		if (timerStay > WAITING_AFTER_END_OF_MOVING)
		{
			timerStay = WAITING_AFTER_END_OF_MOVING + 1;
		}
	}

	return;
}

void Cut_Scene_2_2::dialog()
{
	/*
	* function of making main dialog field ttc
	*/

	vector1 = { 600, 600 };

	Color color(DIALOG_FIELD_COLOR_R, DIALOG_FIELD_COLOR_G, DIALOG_FIELD_COLOR_B);

	dialogField.setSize(vector1);
	dialogField.setFillColor(color);
	dialogField.setOutlineThickness(DIALOG_FIELD_OUTLINE_THICKNESS);
	dialogField.setOutlineColor(Color::Black);
	dialogField.setPosition(DIALOG_FIELD_POSITION_X, DIALOG_FIELD_POSITION_Y);

	return;
}

void Cut_Scene_2_2::drawDialog(RenderWindow & window)
{
	/*
	* function of drawing dialog on screen
	*/

	/// set text size
	text.setCharacterSize(STANDART_TEXT_SIZE);

	/// draw main dialog field
	window.draw(dialogField);

	/// do it as many times as user click LMB
	for (int i = 0; i < dialogPointer; i++)
	{
		if (i == COUNT_MOUSE_CLICK_CUT_SCENE_2_2 - 2)
		{
			/// do for Alice replic
			replicField.setFillColor(Color::White);
			AliceHeadSprite.setPosition(POSITION_ALICE_HEAD_SPRITE, 50 * (i + 1) + 5);
			window.draw(AliceHeadSprite);

			text.setString(replics[i]);
			text.setPosition(POSITION_REPLIC_FIELD_LEFT + 5, 50 * (i + 1) + 15);

			vector1 = { (float)(replics[i].size() * STANDART_TEXT_SIZE / 2 + 10), 40 };
			replicField.setSize(vector1);
			replicField.setPosition(POSITION_REPLIC_FIELD_LEFT, 50 * (i + 1) + 5);

			window.draw(replicField);
			window.draw(text);
		}
		else
		{
			/// do same for Sceintist replic
			replicField.setFillColor(Color::Green);
			ScientistHeadSprite.setPosition(POSITION_SQUIRREL_HEAD_SPRITE, 50 * (i + 1) + 5);
			window.draw(ScientistHeadSprite);

			vector1 = { (float)(replics[i].size() * STANDART_TEXT_SIZE / 2 + 12), 40 };
			replicField.setSize(vector1);
			replicField.setPosition(POSITION_REPLIC_FIELD_RIGHT - 5 - vector1.x, 50 * (i + 1) + 5);

			text.setString(replics[i]);
			text.setPosition(POSITION_REPLIC_FIELD_RIGHT - vector1.x, 50 * (i + 1) + 16);

			window.draw(replicField);
			window.draw(text);
		}
	}

	/// draw down next replic 
	text.setStyle(Text::Bold);
	text.setString("Press LMB to continue...");
	text.setCharacterSize(2 * STANDART_TEXT_SIZE);
	text.setPosition(POSITION_PRESS_LMB_TO_CONTINUE_X, POSITION_PRESS_LMB_TO_CONTINUE_Y);
	text.setStyle(Text::Regular);

	window.draw(text);

	return;
}

void Cut_Scene_2_2::drawPicture(RenderWindow & window)
{
	/*
	* function of drawing picture on screen
	*/

	/// if pause - goodbye
	if (pause)
	{
		return;
	}

	/// clear screen, make background colo - Cyan
	window.clear(Color::Black);

	/// draw backGround
	for (int i = 0; i < 7; i++)
	{
		BackGroundSprite.setPosition(i*SCIENTIST_BACKGROUND_LENGTH, 0);
		window.draw(BackGroundSprite);
	}

	/// draw Alice
	AliceSprite.setPosition(positionAliceX, positionAliceY);
	window.draw(AliceSprite);

	/// draw scientist
	ScientistSprite.setPosition(positionScientistX, positionScientistY);
	window.draw(ScientistSprite);

	/// if we stay too long - draw dialog
	if (timerStay > WAITING_AFTER_END_OF_MOVING)
	{
		drawDialog(window);
	}

	window.display();

	return;
}

bool Cut_Scene_2_2::switchEvent(Event event, RenderWindow & window, Music & music)
{
	/*
	* function of switching type of event
	*/

	/// if window lost focus - make pause
	if (event.type == Event::LostFocus)
	{
		pause = 1;
		music.pause();
	}

	/// if window gain focus - resume
	if (event.type == Event::GainedFocus)
	{
		pause = 0;
		music.play();
	}

	/// if window close - close
	if (event.type == Event::Closed)
	{
		window.close();
		exit(0);
	}

	/// if LMB pressed
	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
	{
		/// if it is time for showing dialog
		if (timerStay > WAITING_AFTER_END_OF_MOVING)
		{
			/// increase pointer of replics
			dialogPointer++;

			/// if all replics are said - time for final screen
			if (dialogPointer == COUNT_MOUSE_CLICK_CUT_SCENE_2_2)
			{
				return 1;
			}
		}
	}

	return 0;
}

void Cut_Scene_2_2::makeTextTTC()
{
	/*
	* function of making text ttc
	*/

	font.loadFromFile("Roboto-Regular.ttf");

	text.setFont(font);
	text.setCharacterSize(STANDART_TEXT_SIZE);
	text.setFillColor(Color::Black);

	return;
}

void Cut_Scene_2_2::play(RenderWindow & window, Music & music)
{
	/*
	* main function of class
	*/

	/// make sprites
	makeSprites();

	/// make dialog field
	dialog();

	/// make text ttc
	makeTextTTC();

	Event event;

	/// restart clock
	myClock.restart();

	while (window.isOpen())
	{
		/// if there if som events
		if (window.pollEvent(event))
		{
			/// if there is the end - goodbye
			if (switchEvent(event, window, music))
			{
				return;
			}
		}

		/// check time
		checkTime(window);
	}

	return;
}

void Cut_Scene_2_2::moveScientist(double timer)
{
	positionScientistX += ScientistVector * timer / ALICE_HORIZONTAL_SPEED;

	if (ScientistVector)
	{
		timerRunningPhoto_S += timer;

		if (timerRunningPhoto_S > 3 * MILLI_SECOND_FOR_ONE_PHOTO)
		{
			timerRunningPhoto_S = 0;
			pointerRunningTexture_S = (pointerRunningTexture_S + 1) % COUNT_SCIENTIST_PHOTO;

			ScientistSprite.setTextureRect(IntRect(POSITION_SCIENTIST_LEFT + pointerRunningTexture_S * SCIENTIST_LENGTH, POSITION_SCIENTIST_TOP, SCIENTIST_LENGTH, SCIENTIST_HIGH));
		}
	}
	else
	{
		pointerRunningTexture_S = 0;

		ScientistSprite.setTextureRect(IntRect(POSITION_SCIENTIST_LEFT, POSITION_SCIENTIST_TOP, SCIENTIST_LENGTH, SCIENTIST_HIGH));
	}

	if (positionScientistX < SQUIRREL_FINISH_POSITION_IN_CUT_SCENES)
	{
		ScientistVector = 0;
		movingIsOver = 1;
	}

	return;
}