#include "Cut_Scene_1_2_1.h"

void Cut_Scene_1_2_1::makeSprites()
{
	/*
	* function of loading picture in sprite
	*/

	texturesAlice.loadFromFile("textures\\AliceTexture.png");

	AliceSprite.setTexture(texturesAlice);
	AliceSprite.setTextureRect(IntRect(POSITION_ALICE_PHOTO_LEFT, POSITION_ALICE_PHOTO_TOP, ALICE_PHOTO_LENGTH - 1, ALICE_PHOTO_HIGH));

	AliceHeadSprite.setTexture(texturesAlice);
	AliceHeadSprite.setTextureRect(IntRect(POSITION_ALICE_HEAD_PHOTO_LEFT, POSITION_ALICE_HEAD_PHOTO_TOP, HEAD_PHOTO_LENGTH, HEAD_PHOTO_HIGH));

	texturesEnviroment.loadFromFile("textures\\EnviromentTexture.png");

	cloudSprite.setTexture(texturesEnviroment);
	cloudSprite.setTextureRect(IntRect(POSITION_CLOUD_PHOTO_LEFT, POSITION_CLOUD_PHOTO_TOP, CLOUD_PHOTO_LENGTH, CLOUD_PHOTO_HIGH));

	groundSprite.setTexture(texturesEnviroment);
	groundSprite.setTextureRect(IntRect(POSITION_GROUND_PHOTO_LEFT, POSITION_GROUND_PHOTO_TOP, GROUND_PHOTO_LENGTH, GROUND_PHOTO_HIGH));

	backGroundSprite.setTexture(texturesEnviroment);
	backGroundSprite.setTextureRect(IntRect(POSITION_BACKGROUND_PHOTO_LEFT, POSITION_BACKGROUND_PHOTO_TOP, BACKGROUND_PHOTO_LENGTH, BACKGROUND_PHOTO_HIGH));

	sunSprite.setTexture(texturesEnviroment);
	sunSprite.setTextureRect(IntRect(POSITION_SUN_PHOTO_LEFT, POSITION_SUN_PHOTO_TOP, SUN_PHOTO_LENGTH, SUN_PHOTO_HIGH));
	sunSprite.setPosition(POSITION_SUN_X, POSITION_SUN_Y);;

	stoneSprite.setTexture(texturesEnviroment);
	stoneSprite.setTextureRect(IntRect(POSITION_STONE_PHOTO_LEFT, POSITION_STONE_PHOTO_TOP, STONE_PHOTO_LENGTH, STONE_PHOTO_HIGH));
	stoneSprite.setPosition(STONE_POSITION_X, STONE_POSITION_Y);

	swordSprite.setTexture(texturesEnviroment);
	swordSprite.setTextureRect(IntRect(POSITION_SWORD_PHOTO_LEFT, POSITION_SWORD_PHOTO_TOP, SWORD_PHOTO_LENGTH, SWORD_PHOTO_HIGH));
	swordSprite.setPosition(SWORD_POSITION_X, SWORD_POSITION_Y);

	return;
}

void Cut_Scene_1_2_1::drawPicture(RenderWindow & window)
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
	window.clear(Color::Cyan);

	/// draw ground
	for (int i = 0; i < COUNT_GROUND_SPRITES_ON_SCREEN; i++)
	{
		groundSprite.setPosition(POSITION_GROUND_SPRITE_X*i, POSITION_GROUND_SPRITE_Y);
		window.draw(groundSprite);
	}

	/// draw background
	for (int i = 0; i < COUNT_BACKGROUND_SPRITES_ON_SCREEN; i++)
	{
		backGroundSprite.setPosition(POSITION_BACKGROUND_SPRITE_X*i, POSITION_BACKGROUND_SPRITE_Y);
		window.draw(backGroundSprite);
	}

	/// draw sun
	window.draw(sunSprite);

	/// draw cloud
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

	/// draw Alice
	AliceSprite.setPosition(positionAliceX, positionAliceY);
	window.draw(AliceSprite);

	/// draw sword and stone
	window.draw(swordSprite);
	window.draw(stoneSprite);

	/// if it is time for dialog - draw dialog
	if (timerStay > WAITING_AFTER_END_OF_MOVING)
	{
		drawDialog(window);
	}

	window.display();

	return;
}

void Cut_Scene_1_2_1::drawDialog(RenderWindow & window)
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
		/// set replic field color, position, size, set text string, position and draw
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

	/// draw down next words
	text.setStyle(Text::Bold);
	text.setString("Press LMB to continue...");
	text.setCharacterSize(2 * STANDART_TEXT_SIZE);
	text.setPosition(POSITION_PRESS_LMB_TO_CONTINUE_X, POSITION_PRESS_LMB_TO_CONTINUE_Y);
	text.setStyle(Text::Regular);

	window.draw(text);

	return;
}

void Cut_Scene_1_2_1::moveObjects(double timer)
{
	/*
	* function of updating positions of all moving objects
	*/

	/// if pause - goodbye
	if (pause)
	{
		return;
	}

	/// move Alice
	moveAlice(timer);

	/// if Alice stop - mooving is over
	if (AliceVector == 0)
	{
		movingIsOver = 1;
	}

	/// move clouds 
	moveClouds(timer);

	/// if moving is over
	if (movingIsOver)
	{
		/// increase timer how long stay
		timerStay += timer;

		/// if we stay too long, don`t make this value too big
		if (timerStay > WAITING_AFTER_END_OF_MOVING)
		{
			timerStay = WAITING_AFTER_END_OF_MOVING + 1;
		}
	}

	return;
}

bool Cut_Scene_1_2_1::switchEvent(Event event, RenderWindow & window, Music & music)
{
	/*
	* function of switching event type
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
		/// if stay too long 
		if (timerStay > WAITING_AFTER_END_OF_MOVING)
		{
			/// increase dialog pointer
			dialogPointer++;

			/// if dialog is finished
			if (dialogPointer == COUNT_MOUSE_CLICK_CUT_SCENE_1_2_1)
			{
				return 1;
			}
		}
	}

	return 0;
}

void Cut_Scene_1_2_1::moveClouds(double timer)
{
	/*
	* function of updating clouds positions
	*/

	/// update cloud positions
	cloudUpperPointer += timer / UPPER_CLOUDS_SPEED;
	cloudDownerPointer += timer / DOWNER_CLOUDS_SPEED;

	/// if cloud pointer is too big - null it
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

void Cut_Scene_1_2_1::moveAlice(double timer)
{
	/*
	* function of updating Alice sprite
	*/

	/// if Alice move
	if (AliceVector)
	{
		/// incrise timer how long show current running picture
		timerRunningPhoto += timer;

		/// if show current photo too long - set pointer on nex picture 
		if (timerRunningPhoto > MILLI_SECOND_FOR_ONE_PHOTO)
		{
			timerRunningPhoto = 0;
			pointerRunningTexture = (pointerRunningTexture + 1) % (COUNT_ALICE_PHOTO - 1);
		}

		/// set picture
		AliceSprite.setTextureRect(IntRect(ALICE_PHOTO_LENGTH * (1 + pointerRunningTexture), POSITION_ALICE_PHOTO_TOP, ALICE_PHOTO_LENGTH - 1, ALICE_PHOTO_HIGH));
	}
	else
	{
		/// set stay picture
		AliceSprite.setTextureRect(IntRect(POSITION_ALICE_PHOTO_LEFT, POSITION_ALICE_PHOTO_TOP, ALICE_PHOTO_LENGTH - 1, ALICE_PHOTO_HIGH));
	}

	/// update Alice position
	positionAliceX += timer / ALICE_HORIZONTAL_SPEED * AliceVector;

	/// if Alice in final position - stop moving, moving is over
	if (positionAliceX > ALICE_FINISH_POSITION_IN_CUT_SCENE)
	{
		positionAliceX = ALICE_FINISH_POSITION_IN_CUT_SCENE;
		AliceVector = 0;

		movingIsOver = 1;
	}

	return;
}

void Cut_Scene_1_2_1::dialog()
{
	/*
	* function of setting man dialog field ttc
	*/

	/// set size, color and position of main dialog field
	vector1 = { 600, 600 };

	Color color(DIALOG_FIELD_COLOR_R, DIALOG_FIELD_COLOR_G, DIALOG_FIELD_COLOR_B);

	dialogField.setSize(vector1);
	dialogField.setFillColor(color);
	dialogField.setOutlineThickness(DIALOG_FIELD_OUTLINE_THICKNESS);
	dialogField.setOutlineColor(Color::Black);
	dialogField.setPosition(DIALOG_FIELD_POSITION_X, DIALOG_FIELD_POSITION_Y);

	return;
}

void Cut_Scene_1_2_1::makeTextTTC()
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

void Cut_Scene_1_2_1::checkTime(RenderWindow & window)
{
	/*
	* function of checking time
	*/

	/// if too long time has passed - restart timer, move objects, draw picture
	if (myClock.getElapsedTime().asMilliseconds() > MILLI_SECOND_FOR_ACTION)
	{
		timer = myClock.getElapsedTime().asMilliseconds();
		myClock.restart();

		moveObjects(timer);
		drawPicture(window);
	}

	return;
}

void Cut_Scene_1_2_1::play(RenderWindow & window, Music & music)
{
	/*
	* main function of class
	*/

	/// make sprites
	makeSprites();
	
	/// make main dialog field
	dialog();

	/// make text ttc
	makeTextTTC();

	Event event;

	/// restart timer
	myClock.restart();

	/// while window is not closed
	while (window.isOpen())
	{
		/// if there is some events
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

Cut_Scene_1_2_1::Cut_Scene_1_2_1()
{
}

Cut_Scene_1_2_1::~Cut_Scene_1_2_1()
{
}
