#include "Cut_Scene_3_1.h"

void Cut_Scene_3_1::makeSound(Music & music)
{
	/*
	* function loading and start the sound
	*/

	music.openFromFile("Music\\DragonSecondMetting.ogg");
	music.setLoop(1);

	music.play();

	return;
}

void Cut_Scene_3_1::makeSprites()
{
	/*
	* function of loading pictures in sprites
	*/

	texturesAlice.loadFromFile("textures\\AliceTexture.png");

	AliceSprite.setTexture(texturesAlice);
	AliceSprite.setTextureRect(IntRect(POSITION_ALICE_ARMOR_LEFT, POSITION_ALICE_ARMOR_TOP, ALICE_ARMOR_LENGTH - 1, ALICE_ARMOR_HIGH));

	AliceHeadSprite.setTexture(texturesAlice);
	AliceHeadSprite.setTextureRect(IntRect(POSITION_ALICE_ARMOR_HEAD_LEFT, POSITION_ALICE_ARMOR_HEAD_TOP, HEAD_PHOTO_LENGTH, HEAD_PHOTO_HIGH));

	texturesEnviroment.loadFromFile("textures\\EnviromentTexture.png");

	cloudSprite.setTexture(texturesEnviroment);
	cloudSprite.setTextureRect(IntRect(POSITION_CLOUD_PHOTO_LEFT, POSITION_CLOUD_PHOTO_TOP, CLOUD_PHOTO_LENGTH, CLOUD_PHOTO_HIGH));

	groundSprite.setTexture(texturesEnviroment);
	groundSprite.setTextureRect(IntRect(POSITION_GROUND_PHOTO_LEFT, POSITION_GROUND_PHOTO_TOP, GROUND_PHOTO_LENGTH, GROUND_PHOTO_HIGH));

	backGroundSprite.setTexture(texturesEnviroment);
	backGroundSprite.setTextureRect(IntRect(POSITION_BACKGROUND_PHOTO_LEFT, POSITION_BACKGROUND_PHOTO_TOP, BACKGROUND_PHOTO_LENGTH, BACKGROUND_PHOTO_HIGH));

	sunSprite.setTexture(texturesEnviroment);
	sunSprite.setTextureRect(IntRect(POSITION_SUN_PHOTO_LEFT, POSITION_SUN_PHOTO_TOP, SUN_PHOTO_LENGTH, SUN_PHOTO_HIGH));
	sunSprite.setPosition(POSITION_SUN_X, POSITION_SUN_Y);

	texturesDragon.loadFromFile("textures\\DragonTexture.png");

	DragonSprite.setTexture(texturesDragon);
	DragonSprite.setTextureRect(IntRect(POSITION_DRAGON_PHOTO_LEFT, POSITION_DRAGON_PHOTO_TOP, DRAGON_PHOTO_LENGTH, DRAGON_PHOTO_HIGH + 1));
	DragonSprite.setPosition(600, MIN_DRAGON_DOWN_POSITION);

	DragonHeadSprite.setTexture(texturesDragon);
	DragonHeadSprite.setTextureRect(IntRect(POSITION_DRAGON_HEAD_PHOTO_LEFT, POSITION_DRAGON_HEAD_PHOTO_TOP, HEAD_PHOTO_LENGTH, HEAD_PHOTO_HIGH));

	return;
}

void Cut_Scene_3_1::drawDialog(RenderWindow & window)
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
		/// if there is dragons replic
		if (i & 1)
		{
			/// set replic field color, size, position, set text string, position and draw
			replicField.setFillColor(Color::Green);
			DragonHeadSprite.setPosition(POSITION_SQUIRREL_HEAD_SPRITE, 50 * (i + 1) + 5);
			window.draw(DragonHeadSprite);

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
			text.setPosition(POSITION_REPLIC_FIELD_LEFT + 5, 50 * (i + 1) + 15);

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

void Cut_Scene_3_1::moveObjects(double timer)
{
	/*
	* function of updating all moving objects
	*/

	/// if pause - goodbye
	if (pause)
	{
		return;
	}

	/// moving Alice
	moveAlice(timer);

	/// moving clouds
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

bool Cut_Scene_3_1::switchEvent(Event event, RenderWindow & window, Music & music)
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
			if (dialogPointer == COUNT_MOUSE_CLICK_CUT_SCENE_3_1)
			{
				return 1;
			}
		}
	}

	return 0;
}

void Cut_Scene_3_1::moveClouds(double timer)
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

void Cut_Scene_3_1::moveAlice(double timer)
{
	/*
	* function of updating Alice sprite
	*/

	/// if Alice move
	if (AliceVector)
	{
		/// increase timer how long show current running picture
		timerRunningPhoto += timer;

		/// if show too long - null timer, set pointer on next picture
		if (timerRunningPhoto > MILLI_SECOND_FOR_ONE_PHOTO)
		{
			timerRunningPhoto = 0;
			pointerRunningTexture = (pointerRunningTexture + 1) % (COUNT_ALICE_PHOTO - 1);
		}

		/// set running picture
		AliceSprite.setTextureRect(IntRect(POSITION_ALICE_ARMOR_LEFT + ALICE_ARMOR_LENGTH * (1 + pointerRunningTexture), POSITION_ALICE_ARMOR_TOP, ALICE_ARMOR_LENGTH - 1, ALICE_ARMOR_HIGH));
	}
	else
	{
		/// set stay picture
		AliceSprite.setTextureRect(IntRect(POSITION_ALICE_ARMOR_LEFT, POSITION_ALICE_ARMOR_TOP, ALICE_ARMOR_LENGTH - 1, ALICE_ARMOR_HIGH));
	}

	/// update position
	positionAliceX += timer / ALICE_HORIZONTAL_SPEED * AliceVector;

	/// if Alice in finish position - stop moving, moving is over
	if (positionAliceX > ALICE_FINISH_POSITION_IN_CUT_SCENE)
	{
		positionAliceX = ALICE_FINISH_POSITION_IN_CUT_SCENE;
		AliceVector = 0;

		movingIsOver = 1;
	}

	return;
}

void Cut_Scene_3_1::dialog()
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

void Cut_Scene_3_1::makeTextTTC()
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

void Cut_Scene_3_1::checkTime(RenderWindow & window)
{
	/*
	* function of checking time
	*/

	/// if too many time has passed - restart timer, move objects, draw picture
	if (myClock.getElapsedTime().asMilliseconds() > MILLI_SECOND_FOR_ACTION)
	{
		timer = myClock.getElapsedTime().asMilliseconds();
		myClock.restart();

		moveObjects(timer);
		drawPicture(window);
	}

	return;
}

void Cut_Scene_3_1::drawPicture(RenderWindow & window)
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

	/// draw Alice
	AliceSprite.setPosition(positionAliceX, positionAliceY);
	window.draw(AliceSprite);

	/// draw Dragon
	window.draw(DragonSprite);

	/// if there is time for dialog - draw dialog
	if (timerStay > WAITING_AFTER_END_OF_MOVING && !finalScreen)
	{
		drawDialog(window);
	}

	window.display();

	return;
}

void Cut_Scene_3_1::play(RenderWindow & window, Music & music)
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

Cut_Scene_3_1::Cut_Scene_3_1()
{
}

Cut_Scene_3_1::~Cut_Scene_3_1()
{
}
