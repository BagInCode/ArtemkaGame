#include "Cut_Scene_4_1.h"



Cut_Scene_4_1::Cut_Scene_4_1()
{
}

void Cut_Scene_4_1::makeSound(Music & music)
{
	/*
	* function loading and start the sound
	*/

	music.openFromFile("Music\\PacManIntro.ogg");
	music.setLoop(0);

	music.play();

	return;
}

void Cut_Scene_4_1::makeSprites()
{
	/*
	* function of loading pictures in sprites
	*/
	textures.loadFromFile("textures\\AliceTexture.png");
	
	AliceHeadSprite.setTexture(textures);
	AliceHeadSprite.setTextureRect(IntRect(POSITION_ALICE_ARMOR_HEAD_LEFT, POSITION_ALICE_ARMOR_HEAD_TOP, HEAD_PHOTO_LENGTH, HEAD_PHOTO_HIGH));

	AliceSprite.setTexture(textures);
	AliceSprite.setTextureRect(IntRect(POSITION_ALICE_ARMOR_LEFT, POSITION_ALICE_ARMOR_TOP, ALICE_ARMOR_LENGTH, ALICE_ARMOR_HIGH));

	return;
}

void Cut_Scene_4_1::checkTime(RenderWindow & window)
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

void Cut_Scene_4_1::moveObjects(double timer)
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
	moveAlice(timer);

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


void Cut_Scene_4_1::moveAlice(double timer)
{
	/*
	* function of updating Alice sprite
	*/

	/// if Alice move horizontally
	if (AliceVector)
	{
		/// timerRunningPhoto - how long we show current run picture, increse this value
		timerRunningPhoto += timer;

		/// if we show current run picture too long - set pointer on next picture and start timer again
		if (timerRunningPhoto > MILLI_SECOND_FOR_ONE_PHOTO)
		{
			timerRunningPhoto = 0;
			pointerRunningTexture = (pointerRunningTexture + 1) % (COUNT_ALICE_PHOTO - 1);
		}

		AliceSprite.setTextureRect(IntRect(ALICE_ARMOR_LENGTH * (1 + pointerRunningTexture), POSITION_ALICE_ARMOR_TOP, ALICE_ARMOR_LENGTH-2, ALICE_ARMOR_HIGH));
	}
	else
	{
		/// if Alice not move - set stay picture
		AliceSprite.setTextureRect(IntRect(POSITION_ALICE_ARMOR_LEFT, POSITION_ALICE_ARMOR_TOP, ALICE_ARMOR_LENGTH, ALICE_ARMOR_HIGH));
	}

	/// update Alice sprite position
	positionAliceX += timer / ALICE_HORIZONTAL_SPEED * AliceVector;

	if (positionAliceX > ALICE_FINISH_POSITION_IN_CUT_SCENE)
	{
		AliceVector = 0;
		positionAliceX = ALICE_FINISH_POSITION_IN_CUT_SCENE;

		movingIsOver = 1;
	}

	return;
}



void Cut_Scene_4_1::dialog()
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

void Cut_Scene_4_1::drawDialog(RenderWindow & window)
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
		
		{
			/// do same for Alice replic
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

void Cut_Scene_4_1::drawPicture(RenderWindow & window)
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

	/// draw Alice
	AliceSprite.setPosition(positionAliceX, positionAliceY);
	window.draw(AliceSprite);

	/// if we stay too long - draw dialog
	if (timerStay > WAITING_AFTER_END_OF_MOVING && !finalScreen)
	{
		drawDialog(window);
	}

	window.display();

	return;
}

bool Cut_Scene_4_1::switchEvent(Event event, RenderWindow & window, Music & music)
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
			if (dialogPointer == COUNT_MOUSE_CLICK_CUT_SCENE_4_1)
			{
				return 1;
			}
		}
	}

	return 0;
}

void Cut_Scene_4_1::makeTextTTC()
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

void Cut_Scene_4_1::play(RenderWindow & window, Music & music)
{
	/*
	* main function of class
	*/

	/// make music
	makeSound(music);

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

Cut_Scene_4_1::~Cut_Scene_4_1()
{
}
