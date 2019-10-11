#include "Cut_Scene_3_2.h"

void Cut_Scene_3_2::makeSound(Music & music)
{
	/*
	* function loading and start the sound
	*/

	music.openFromFile("Music\\RUUUUN.ogg");
	music.setLoop(1);

	music.play();

	return;
}

void Cut_Scene_3_2::makeSprites()
{
	/*
	* function of loading picture in sprites
	*/

	texturesAlice.loadFromFile("textures\\AliceTexture.png");

	AliceSprite.setTexture(texturesAlice);
	AliceSprite.setTextureRect(IntRect(POSITION_ALICE_ARMOR_LEFT, POSITION_ALICE_ARMOR_TOP, ALICE_ARMOR_LENGTH - 1, ALICE_ARMOR_HIGH));

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

	texturesDragon.loadFromFile("textures\\DragonTexture.png");

	DragonSprite.setTexture(texturesDragon);
	DragonSprite.setTextureRect(IntRect(POSITION_DRAGON_FLY_LEFT, POSITION_DRAGON_FLY_TOP, DRAGON_FLY_LENGTH, DRAGON_FLY_HIGH));

	DragonHeadSprite.setTexture(texturesDragon);
	DragonHeadSprite.setTextureRect(IntRect(POSITION_DRAGON_HEAD_PHOTO_LEFT, POSITION_DRAGON_HEAD_PHOTO_TOP, HEAD_PHOTO_LENGTH, HEAD_PHOTO_HIGH));

	return;
}

void Cut_Scene_3_2::moveDragon(double timer)
{
	/*
	* function of moving Dragon
	*/

	/// update Dragon position
	positionDragonY -= boostDragon;
	positionDragonX += timer / DRAGON_HORIZONTAL_SPEED * dragonVector;

	timerDragonFly += timer;

	if (timerDragonFly > TIMER_DRAGON_FLY)
	{
		timerDragonFly = 0;
		pointerDragonTexture = (pointerDragonTexture + 1) % COUNT_DRAGON_FLY_PHOTO;

		DragonSprite.setTextureRect(IntRect(POSITION_DRAGON_FLY_LEFT + pointerDragonTexture * DRAGON_FLY_LENGTH + DRAGON_FLY_LENGTH * (orientation == -1), POSITION_DRAGON_FLY_TOP, DRAGON_FLY_LENGTH * orientation, DRAGON_FLY_HIGH));
	}

	/// if Dragon in final position - stop moving, moving is over
	if (positionDragonY < FINAL_DRAGON_POSITION_Y_IN_CUT_SCENE_3_2)
	{
		positionDragonY = FINAL_DRAGON_POSITION_Y_IN_CUT_SCENE_3_2+1;
		boostDragon = 0;

		dragonVector = -1;
	}

	if (positionDragonX < FINAL_DRAGON_POSITION_X_IN_CUT_SCENE_3_2)
	{
		positionDragonX = FINAL_DRAGON_POSITION_X_IN_CUT_SCENE_3_2 + 1;
		dragonVector = 1;

		orientation = -1;

		AliceVector = 1;
	}

	if (positionDragonX > FINAL_DRAGON_POSITION_X_IN_CUT_SCENE_3_2_RIGHT)
	{
		positionDragonX = FINAL_DRAGON_POSITION_X_IN_CUT_SCENE_3_2_RIGHT - 1;
		dragonVector = 0;

		movingIsOver = 1;
	}

	return;
}

void Cut_Scene_3_2::moveAlice(double timer)
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

		/// if Alice move right - set picture from left to right, else - set picture back
		if (AliceVector > 0)
		{
			AliceSprite.setTextureRect(IntRect(POSITION_ALICE_ARMOR_LEFT + ALICE_ARMOR_LENGTH * (1 + pointerRunningTexture), POSITION_ALICE_ARMOR_TOP, ALICE_ARMOR_LENGTH - 1, ALICE_ARMOR_HIGH));
		}
		else
		{
			AliceSprite.setTextureRect(IntRect(POSITION_ALICE_ARMOR_LEFT + ALICE_ARMOR_LENGTH * (2 + pointerRunningTexture), POSITION_ALICE_ARMOR_TOP, -ALICE_ARMOR_LENGTH + 1, ALICE_ARMOR_HIGH));
		}
	}
	else
	{
		/// if Alice not move - set stay picture
		AliceSprite.setTextureRect(IntRect(POSITION_ALICE_ARMOR_LEFT, POSITION_ALICE_ARMOR_TOP, ALICE_ARMOR_LENGTH - 1, ALICE_ARMOR_HIGH));
	}

	/// update Alice sprite position
	positionAliceX += timer / ALICE_HORIZONTAL_SPEED * AliceVector;

	if (positionAliceX > FINAL_ALICE_POSITION_X_IN_CUT_SCENE_3_2)
	{
		AliceVector = 0;
		positionAliceX = FINAL_ALICE_POSITION_X_IN_CUT_SCENE_3_2-1;

		dragonVector = 1;
	}

	return;
}

void Cut_Scene_3_2::moveObjects(double timer)
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

	/// move Alice
	moveAlice(timer);

	/// move clouds
	moveClouds(timer);

	return;
}

bool Cut_Scene_3_2::switchEvent(Event event, RenderWindow & window, Music & music)
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

	if (movingIsOver)
	{
		return 1;
	}

	return 0;
}

void Cut_Scene_3_2::moveClouds(double timer)
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

void Cut_Scene_3_2::checkTime(RenderWindow & window)
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

void Cut_Scene_3_2::drawPicture(RenderWindow & window)
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

	AliceSprite.setPosition(positionAliceX, positionAliceY);
	window.draw(AliceSprite);

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

	window.display();

	return;
}

void Cut_Scene_3_2::play(RenderWindow & window, Music & music)
{
	/*
	* main function of class
	*/

	/// make music
	makeSound(music);

	/// make sprites
	makeSprites();

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

		if (movingIsOver)
		{
			return;
		}

		/// check time
		checkTime(window);
	}

	return;
}

Cut_Scene_3_2::Cut_Scene_3_2()
{
}

Cut_Scene_3_2::~Cut_Scene_3_2()
{
}
