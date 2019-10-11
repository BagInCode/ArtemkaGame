#include "Cut_Scene_1_3.h"

void Cut_Scene_1_3::makeSprites()
{
	/*
	* function of loading picture in sprites
	*/
	texturesAlice.loadFromFile("textures\\AliceTexture.png");

	AliceSprite.setTexture(texturesAlice);
	AliceSprite.setTextureRect(IntRect(POSITION_ALICE_PHOTO_LEFT, POSITION_ALICE_PHOTO_TOP, ALICE_PHOTO_LENGTH - 1, ALICE_PHOTO_HIGH));
	AliceSprite.setPosition(ALICE_FINISH_POSITION_IN_CUT_SCENE, MIN_ALICE_DOWN_POSITION);

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
	sunSprite.setPosition(POSITION_SUN_X, POSITION_SUN_Y);

	texturesDargon.loadFromFile("textures\\DragonTexture.png");

	DragonSprite.setTexture(texturesDargon);
	DragonSprite.setTextureRect(IntRect(POSITION_DRAGON_FLY_LEFT, POSITION_DRAGON_FLY_TOP, DRAGON_FLY_LENGTH, DRAGON_FLY_HIGH));

	DragonHeadSprite.setTexture(texturesDargon);
	DragonHeadSprite.setTextureRect(IntRect(POSITION_DRAGON_HEAD_PHOTO_LEFT, POSITION_DRAGON_HEAD_PHOTO_TOP, HEAD_PHOTO_LENGTH, HEAD_PHOTO_HIGH));

	return;
}

void Cut_Scene_1_3::moveDragon(double timer)
{
	/*
	* function of moving Dragon
	*/

	/// update Dragon position
	positionDragonY -= boostDragon;

	timerDragonFly += timer;

	if (timerDragonFly > TIMER_DRAGON_FLY)
	{
		timerDragonFly = 0;
		pointerDragonTexture = (pointerDragonTexture + 1) % COUNT_DRAGON_FLY_PHOTO;
	
		DragonSprite.setTextureRect(IntRect(POSITION_DRAGON_FLY_LEFT + pointerDragonTexture * DRAGON_FLY_LENGTH, POSITION_DRAGON_FLY_TOP, DRAGON_FLY_LENGTH, DRAGON_FLY_HIGH));
	}

	/// if Dragon in final position - stop moving, moving is over
	if (positionDragonY < FINAL_DRAGON_POSITION_IN_CUT_SCENE_1_3)
	{
		positionDragonY = FINAL_DRAGON_POSITION_IN_CUT_SCENE_1_3;
		boostDragon = 0;

		movingIsOver = 1;
	}

	return;
}

void Cut_Scene_1_3::drawDialog(RenderWindow & window)
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
		/// set replic field size, clor, position, set text string, position and draw 
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

	/// set and draw next words:
	text.setStyle(Text::Bold);
	text.setString("Press LMB to continue...");
	text.setCharacterSize(2 * STANDART_TEXT_SIZE);
	text.setPosition(POSITION_PRESS_LMB_TO_CONTINUE_X, POSITION_PRESS_LMB_TO_CONTINUE_Y);
	text.setStyle(Text::Regular);

	window.draw(text);

	return;
}

void Cut_Scene_1_3::moveObjects(double timer)
{
	/*
	* function of updatig all moving objects
	*/

	/// if pause - goodbye
	if (pause)
	{
		return;
	}

	/// move Dragon
	moveDragon(timer);

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

bool Cut_Scene_1_3::switchEvent(Event event, RenderWindow & window, Music & music)
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
		/// if there is time for dialog
		if (timerStay > WAITING_AFTER_END_OF_MOVING)
		{
			/// increase dialog pointer
			dialogPointer++;

			/// if there is finish - return true
			if (dialogPointer == COUNT_MOUSE_CLICK_CUT_SCENE_1_3)
			{
				return 1;
			}
		}
	}

	return 0;
}

void Cut_Scene_1_3::moveClouds(double timer)
{
	/*
	* function of moving clouds
	*/

	/// update clouds positions
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

void Cut_Scene_1_3::dialog()
{
	/*
	* function of setting main dialog field ttc
	*/

	/// set main dialog field size, color and position
	vector1 = { 600, 600 };

	Color color(DIALOG_FIELD_COLOR_R, DIALOG_FIELD_COLOR_G, DIALOG_FIELD_COLOR_B);

	dialogField.setSize(vector1);
	dialogField.setFillColor(color);
	dialogField.setOutlineThickness(DIALOG_FIELD_OUTLINE_THICKNESS);
	dialogField.setOutlineColor(Color::Black);
	dialogField.setPosition(DIALOG_FIELD_POSITION_X, DIALOG_FIELD_POSITION_Y);

	return;
}

void Cut_Scene_1_3::makeTextTTC()
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

void Cut_Scene_1_3::checkTime(RenderWindow & window)
{
	/*
	* function of checking time
	*/

	/// if to much time has passed - restart timer, move objects and draw picture
	if (myClock.getElapsedTime().asMilliseconds() > MILLI_SECOND_FOR_ACTION)
	{
		timer = myClock.getElapsedTime().asMilliseconds();
		myClock.restart();

		moveObjects(timer);
		drawPicture(window);
	}

	return;
}

void Cut_Scene_1_3::drawPicture(RenderWindow & window)
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
	window.draw(AliceSprite);

	/// draw Dragon
	DragonSprite.setPosition(positionDragonX, positionDragonY);
	window.draw(DragonSprite);

	/// if there is time for dialog - draw dialog
	if (timerStay > WAITING_AFTER_END_OF_MOVING)
	{
		drawDialog(window);
	}

	window.display();

	return;
}

void Cut_Scene_1_3::play(RenderWindow & window, Music & music)
{
	/*
	* main function of class
	*/

	/// make sprites
	makeSprites();

	/// set main dialog field ttc
	dialog();

	/// set text ttc
	makeTextTTC();

	Event event;

	/// resrart timer
	myClock.restart();

	/// while windows not close
	while (window.isOpen())
	{
		/// if there is some event
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

Cut_Scene_1_3::Cut_Scene_1_3()
{
}

Cut_Scene_1_3::~Cut_Scene_1_3()
{
}
