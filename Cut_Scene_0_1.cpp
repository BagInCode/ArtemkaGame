#include "Cut_Scene_0_1.h"



Cut_Scene_0_1::Cut_Scene_0_1()
{

}


Cut_Scene_0_1::~Cut_Scene_0_1()
{

}

void Cut_Scene_0_1::makeSound(Music & music)
{
	/*
	* function loading and start the sound
	*/

	music.openFromFile("Music\\intro_ending.ogg");
	music.setLoop(1);

	music.play();

	return;
}

void Cut_Scene_0_1::makeSprites()
{
	/*
	* function of loading pictures in sprites
	*/

	texturesAlice.loadFromFile("textures\\AliceTexture.png");

	AliceHeadSprite.setTexture(texturesAlice);
	AliceHeadSprite.setTextureRect(IntRect(POSITION_ALICE_HEAD_WB_LEFT, POSITION_ALICE_HEAD_WB_TOP, HEAD_PHOTO_LENGTH, HEAD_PHOTO_HIGH));

	texturesEnviroment.loadFromFile("textures\\EnviromentTexture.png");

	cloudSprite.setTexture(texturesEnviroment);
	cloudSprite.setTextureRect(IntRect(POSITION_CLOUD_PHOTO_LEFT, POSITION_CLOUD_PHOTO_TOP, CLOUD_PHOTO_LENGTH, CLOUD_PHOTO_HIGH));

	AliceHomeSprite.setTexture(texturesEnviroment);
	AliceHomeSprite.setTextureRect(IntRect(POSITION_ALICE_HOUSE_LEFT, POSITION_ALICE_HOUSE_TOP, ALICE_HOUSE_LENGTH, ALICE_HOUSE_HIGH));
	AliceHomeSprite.setPosition(450, 0);

	OtherHomeLeftSprite.setTexture(texturesEnviroment);
	OtherHomeLeftSprite.setTextureRect(IntRect(POSITION_OTHER_HOUSE_LEFT, POSITION_OTHER_HOUSE_TOP, OTHER_HOUSE_LENGTH, OTHER_HOUSE_HIGH));
	OtherHomeLeftSprite.setPosition(0, 0);

	OtherHomeRightSprite.setTexture(texturesEnviroment);
	OtherHomeRightSprite.setTextureRect(IntRect(POSITION_OTHER_HOUSE_LEFT + OTHER_HOUSE_LENGTH, POSITION_OTHER_HOUSE_TOP, -OTHER_HOUSE_LENGTH, OTHER_HOUSE_HIGH));
	OtherHomeRightSprite.setPosition(850, 0);

	texturesOther.loadFromFile("textures\\OtherCharactersTexture.png");

	MomSprite.setTexture(texturesOther);
	MomSprite.setTextureRect(IntRect(POSITION_ALICE_MOM_LEFT, POSITION_ALICE_MOM_TOP, ALICE_MOM_LENGTH, ALICE_MOM_HIGH));

	AliceMomHeadSprite.setTexture(texturesOther);
	AliceMomHeadSprite.setTextureRect(IntRect(POSITION_ALICE_MOM_HEAD_LEFT + HEAD_PHOTO_LENGTH, POSITION_ALICE_MOM_HEAD_TOP, -HEAD_PHOTO_LENGTH, HEAD_PHOTO_HIGH));
	
	return;
}

void Cut_Scene_0_1::drawDialog(RenderWindow & window)
{
	/*
	* function of drawing dialog on screen
	*/

	/// set text size
	text.setCharacterSize(STANDART_TEXT_SIZE);

	/// draw main dialog field
	window.draw(dialogField);

	/// do as many times as user click LMB
	for (int i = 0; i < dialogPointer; i++)
	{
		/// if there is **** replic
		if (i > 0 && i < 6)
		{
			/// set replic field color, size, position, set text string, position and draw
			replicField.setFillColor(Color::Green);
			AliceMomHeadSprite.setPosition(POSITION_SQUIRREL_HEAD_SPRITE, 50 * (i + 1) + 5);
			window.draw(AliceMomHeadSprite);

			vector1 = { (float)(replics[i].size() * STANDART_TEXT_SIZE / 2 + 10), 40 };
			replicField.setSize(vector1);
			replicField.setPosition(POSITION_REPLIC_FIELD_RIGHT - 5 - vector1.x, 50 * (i + 1) + 5);

			text.setString(replics[i]);
			text.setPosition(POSITION_REPLIC_FIELD_RIGHT - vector1.x, 50 * (i + 1) + 15);

			window.draw(replicField);
			window.draw(text);
		}
		else
		{
			/// do same for Alice replics
			replicField.setFillColor(Color::White);
			AliceHeadSprite.setPosition(POSITION_ALICE_HEAD_SPRITE, 50 * (i + 1) + 5);
			window.draw(AliceHeadSprite);

			text.setString(replics[i]);
			text.setPosition(POSITION_REPLIC_FIELD_LEFT + 2, 50 * (i + 1) + 15);

			vector1 = { (float)(replics[i].size() * STANDART_TEXT_SIZE / 2 + 10), 40 };
			replicField.setSize(vector1);
			replicField.setPosition(POSITION_REPLIC_FIELD_LEFT, 50 * (i + 1) + 5);

			window.draw(replicField);
			window.draw(text);
		}
	}

	/// set ttc for last words
	text.setStyle(Text::Bold);
	text.setString("Press LMB to continue...");
	text.setCharacterSize(2 * STANDART_TEXT_SIZE);
	text.setPosition(POSITION_PRESS_LMB_TO_CONTINUE_X, POSITION_PRESS_LMB_TO_CONTINUE_Y);
	text.setStyle(Text::Regular);

	window.draw(text);

	return;
}

void Cut_Scene_0_1::moveObjects(double timer)
{
	/*
	* function of updating all moving objects
	*/

	/// if pause - goodbye
	if (pause)
	{
		return;
	}

	/// moving Alice Mom
	moveAliceMom(timer);

	/// move clouds
	moveClouds(timer);

	/// if moving is over
	if (movingIsOver)
	{
		/// increase timer how long stay
		timerStay += timer;

		/// if stay too long - don`t make this value too big
		if (timerStay > WAITING_AFTER_END_OF_MOVING)
		{
			timerStay = WAITING_AFTER_END_OF_MOVING + 1;
		}
	}

	return;
}

bool Cut_Scene_0_1::switchEvent(Event event, RenderWindow & window, Music & music)
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

	/// if indow gain focus - resume
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
		/// if there is time for dialog
		if (timerStay > WAITING_AFTER_END_OF_MOVING)
		{
			/// increase dialog pointer
			dialogPointer++;

			/// if finish - time for final screen
			if (dialogPointer == COUNT_MOUSE_CLICK_CUT_SCENE_0_1)
			{
				return 1;
			}
		}
	}

	return 0;
}

void Cut_Scene_0_1::dialog()
{
	/*
	* function of setting main dialog field ttc
	*/

	/// set size color and position of main dialog field
	vector1 = { 600, 600 };

	Color color(DIALOG_FIELD_COLOR_R, DIALOG_FIELD_COLOR_G, DIALOG_FIELD_COLOR_B);

	dialogField.setSize(vector1);
	dialogField.setFillColor(color);
	dialogField.setOutlineThickness(DIALOG_FIELD_OUTLINE_THICKNESS);
	dialogField.setOutlineColor(Color::Black);
	dialogField.setPosition(DIALOG_FIELD_POSITION_X, DIALOG_FIELD_POSITION_Y);

	return;
}

void Cut_Scene_0_1::makeTextTTC()
{
	/*
	* function of setting text ttc
	*/

	font.loadFromFile("Roboto-Regular.ttf");

	text.setFont(font);
	text.setCharacterSize(STANDART_TEXT_SIZE);
	text.setFillColor(Color::Black);

	return;
}

void Cut_Scene_0_1::checkTime(RenderWindow & window)
{
	/*
	* function of checking time
	*/

	/// if too many time has passed - restart timer, move objects, draw picture
	if (myClock.getElapsedTime().asMilliseconds() > MILLI_SECOND_FOR_ACTION)
	{
		double timer = myClock.getElapsedTime().asMilliseconds();
		myClock.restart();

		moveObjects(timer);
		drawPicture(window);
	}

	return;
}

void Cut_Scene_0_1::drawPicture(RenderWindow & window)
{
	/*
	* function of drawing picture on screen
	*/

	/// if pause - goodbye
	if (pause)
	{
		return;
	}

	/// clear window, set background color Cyan
	window.clear(Color(189, 189, 189));

	window.draw(OtherHomeLeftSprite);
	window.draw(AliceHomeSprite);
	window.draw(OtherHomeRightSprite);

	MomSprite.setPosition(positionAliceMomX, positionAliceMomY);
	window.draw(MomSprite);

	/// draw clouds
	for (int i = 0; i < COUNT_CLOUD_SPRITES_ON_SCREEN; i++)
	{
		cloudSprite.setPosition(POSITION_CLOUD_SPRITE_X *i + cloudDownerPointer - 3 * CLOUD_DISPLACEMENT_BY_X, POSITION_DOWNER_CLOUD_SPRITE_Y);
		window.draw(cloudSprite);
	}

	for (int i = 0; i < COUNT_CLOUD_SPRITES_ON_SCREEN; i++)
	{
		cloudSprite.setPosition(POSITION_CLOUD_SPRITE_X *i + cloudUpperPointer - 2 * CLOUD_DISPLACEMENT_BY_X, POSITION_UPPER_CLOUD_SPRITE_Y);
		window.draw(cloudSprite);
	}

	/// if there is time for dialog - draw dialog
	if (timerStay > WAITING_AFTER_END_OF_MOVING)
	{
		drawDialog(window);
	}

	window.display();

	return;
}

void Cut_Scene_0_1::play(RenderWindow & window, Music & music)
{
	/*
	* main function of class
	*/

	/// make music
	makeSound(music);

	/// make sprites
	makeSprites();

	/// make main dialog field
	dialog();

	/// make text ttc
	makeTextTTC();

	Event event;

	/// restart timer
	myClock.restart();

	/// while windon not closed
	while (window.isOpen())
	{
		/// if there if some event
		if (window.pollEvent(event))
		{
			/// if finish - goodbye
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

void Cut_Scene_0_1::moveAliceMom(double timer)
{
	positionAliceMomX += AliceMomVector * timer / ALICE_HORIZONTAL_SPEED/ 5;

	if (AliceMomVector)
	{
		timerRunningPhoto += timer;

		if (timerRunningPhoto > 3 * MILLI_SECOND_FOR_ONE_PHOTO)
		{
			timerRunningPhoto = 0;
			pointerRunningTexture = (pointerRunningTexture + 1) % COUNT_SCIENTIST_PHOTO;

			MomSprite.setTextureRect(IntRect(POSITION_ALICE_MOM_LEFT + pointerRunningTexture * ALICE_MOM_LENGTH, POSITION_ALICE_MOM_TOP, ALICE_MOM_LENGTH, ALICE_MOM_HIGH));
		}
	}
	else
	{
		pointerRunningTexture = 0;
	}

	if (positionAliceMomX > ALICE_MOM_FINISH_POSITION)
	{
		AliceMomVector = 0;
		movingIsOver = 1;
	}

	return;
}

void Cut_Scene_0_1::moveClouds(double timer)
{
	/*
	* function of updating clouds position
	*/

	/// update clouds position
	cloudUpperPointer += timer / UPPER_CLOUDS_SPEED;
	cloudDownerPointer += timer / DOWNER_CLOUDS_SPEED;

	/// if clouds pointers is too big - null them
	if (cloudUpperPointer > MAX_CLOUDS_DISPLACEMENT)
	{
		cloudUpperPointer = 0;
	}
	if (cloudDownerPointer > MAX_CLOUDS_DISPLACEMENT)
	{
		cloudDownerPointer = 0;
	}

	return;
}