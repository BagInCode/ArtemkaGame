#include "Cut_Scene_1_1.h"

void Cut_Scene_1_1::makeSprites()
{
	/*
	* function of loading pictures in sprites
	*/
	texturesEnviroment.loadFromFile("textures\\EnviromentTexture.png");

	cloudSprite.setTexture(texturesEnviroment);
	cloudSprite.setTextureRect(IntRect(POSITION_CLOUD_PHOTO_LEFT, POSITION_CLOUD_PHOTO_TOP, CLOUD_PHOTO_LENGTH, CLOUD_PHOTO_HIGH));

	groundSprite.setTexture(texturesEnviroment);
	groundSprite.setTextureRect(IntRect(POSITION_GROUND_PHOTO_LEFT, POSITION_GROUND_PHOTO_TOP, GROUND_PHOTO_LENGTH, GROUND_PHOTO_HIGH));

	backGroundSprite.setTexture(texturesEnviroment);
	backGroundSprite.setTextureRect(IntRect(POSITION_BACKGROUND_PHOTO_LEFT, POSITION_BACKGROUND_PHOTO_TOP, BACKGROUND_PHOTO_LENGTH, BACKGROUND_PHOTO_HIGH));

	sunSprite.setTexture(texturesEnviroment);
	sunSprite.setTextureRect(IntRect(POSITION_SUN_PHOTO_LEFT, POSITION_SUN_PHOTO_TOP, SUN_PHOTO_LENGTH, SUN_PHOTO_HIGH));
	sunSprite.setPosition(POSITION_SUN_X, POSITION_SUN_Y); /// set position for static sprite

	texturesOther.loadFromFile("textures\\OtherCharactersTexture.png");

	squirrelSprite.setTexture(texturesOther);
	squirrelSprite.setTextureRect(IntRect(POSITION_SQUIRREL_PHOTO_LEFT, POSITION_SQUIRREL_PHOTO_TOP, SQUIRREL_PHOTO_LENGTH, SQUIRREL_PHOTO_HIGH));
	
	squirrelHeadSprite.setTexture(texturesOther);
	squirrelHeadSprite.setTextureRect(IntRect(POSITION_SQUIRREL_HEAD_PHOTO_LEFT, POSITION_SQUIRREL_HEAD_PHOTO_TOP, HEAD_PHOTO_LENGTH, HEAD_PHOTO_HIGH));

	texturesAlice.loadFromFile("textures\\AliceTexture.png");
	
	AliceHeadSprite.setTexture(texturesAlice);
	AliceHeadSprite.setTextureRect(IntRect(POSITION_ALICE_HEAD_PHOTO_LEFT, POSITION_ALICE_HEAD_PHOTO_TOP, HEAD_PHOTO_LENGTH, HEAD_PHOTO_HIGH));

	AliceSprite.setTexture(texturesAlice);
	AliceSprite.setTextureRect(IntRect(POSITION_ALICE_PHOTO_LEFT, POSITION_ALICE_PHOTO_TOP, ALICE_PHOTO_LENGTH - 2, ALICE_PHOTO_HIGH));

	return;
}

void Cut_Scene_1_1::checkTime(RenderWindow & window)
{
	/*
	* function of checking time
	*/

	/// if too much time has passed - restart timer, move objects, draw picture
	if (myClock.getElapsedTime().asMilliseconds() > MILLI_SECOND_FOR_ACTION)
	{
		timer = myClock.restart().asMilliseconds();

		moveObjects(timer);
		drawPicture(window);
	}

	return;
}

void Cut_Scene_1_1::moveObjects(double timer)
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
	
	/// if Alice stop - squirell start
	if (AliceVector == 0 && !movingIsOver)
	{
		squirrelVector = -1;
	}

	/// move Squirrel
	moveSquirrel(timer);

	/// move clouds
	moveClouds(timer);

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

void Cut_Scene_1_1::moveSquirrel(double timer)
{
	/*
	* function of updating squirrel sprite
	*/

	/// if squirrel move
	if (squirrelVector)
	{
		/// increse value of time how long show current run picture
		timerRunningPhoto_S += timer;

		/// if show current run picture too long - restart timer, set new picture
		if (timerRunningPhoto_S > MILLI_SECOND_FOR_ONE_PHOTO)
		{
			timerRunningPhoto_S = 0;
			pointerRunningTexture_S = (pointerRunningTexture_S + 1) % (COUNT_SQUIRREL_PHOTO - 1);
		}

		squirrelSprite.setTextureRect(IntRect(POSITION_SQUIRREL_PHOTO_LEFT + SQUIRREL_PHOTO_LENGTH*(1 + pointerRunningTexture_S), POSITION_SQUIRREL_PHOTO_TOP, SQUIRREL_PHOTO_LENGTH, SQUIRREL_PHOTO_HIGH));
	}
	else
	{
		/// set stay picture
		squirrelSprite.setTextureRect(IntRect(POSITION_SQUIRREL_PHOTO_LEFT, POSITION_SQUIRREL_PHOTO_TOP, SQUIRREL_PHOTO_LENGTH, SQUIRREL_PHOTO_HIGH));
	}

	/// update Squirrel position
	positionSquirrelX += timer / ALICE_HORIZONTAL_SPEED * squirrelVector;

	/// if squirrel in final position - stop squirrel, finish moving
	if (positionSquirrelX < SQUIRREL_FINISH_POSITION_IN_CUT_SCENES)
	{
		positionSquirrelX = SQUIRREL_FINISH_POSITION_IN_CUT_SCENES;
		squirrelVector = 0;
		movingIsOver = 1;
	}

	return;
}

void Cut_Scene_1_1::moveClouds(double timer)
{
	/*
	* function of updating cloud sprite
	*/

	/// update positions of clouds sprites
	cloudUpperPointer += timer / UPPER_CLOUDS_SPEED;
	cloudDownerPointer += timer / DOWNER_CLOUDS_SPEED;

	/// if clouds pointer is too big - null it
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

void Cut_Scene_1_1::drawPicture(RenderWindow & window)
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

	/// draw squirrel
	squirrelSprite.setPosition(positionSquirrelX, positionSquirrelY);
	window.draw(squirrelSprite);

	/// if we stay too long - draw dialog
	if (timerStay > WAITING_AFTER_END_OF_MOVING)
	{
		drawDialog(window);
	}

	window.display();

	return;
}

bool Cut_Scene_1_1::switchEvent(Event event, RenderWindow & window, Music & music)
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
			if (dialogPointer == COUNT_MOUSE_CLICK_CUT_SCENE_1_1)
			{
				return 1;
			}
		}
	}

	return 0;
}

void Cut_Scene_1_1::makeTextTTC()
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

void Cut_Scene_1_1::dialog()
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

void Cut_Scene_1_1::drawDialog(RenderWindow & window)
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
		/// if there is squirrel replic - set field color Green, set position, set size, set text and draw 
		if (i & 1)
		{
			replicField.setFillColor(Color::Green);
			squirrelHeadSprite.setPosition(POSITION_SQUIRREL_HEAD_SPRITE, 50 * (i + 1) + 5);
			window.draw(squirrelHeadSprite);

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

void Cut_Scene_1_1::makeSound(Music & music)
{
	/*
	* function loading and start the sound
	*/

	music.openFromFile("Music\\Cut_Scene_1_1.ogg");
	music.setLoop(0);

	music.play();

	return;
}

void Cut_Scene_1_1::play(RenderWindow & window, Music & music)
{
	/*
	* main function of class
	*/
	
	/// make sound
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

void Cut_Scene_1_1::moveAlice(double timer)
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
			AliceSprite.setTextureRect(IntRect(POSITION_ALICE_PHOTO_LEFT + ALICE_PHOTO_LENGTH * (1 + pointerRunningTexture), POSITION_ALICE_PHOTO_TOP, ALICE_PHOTO_LENGTH - 2, ALICE_PHOTO_HIGH));
		}
		else
		{
			AliceSprite.setTextureRect(IntRect(POSITION_ALICE_PHOTO_LEFT + ALICE_PHOTO_LENGTH * (2 + pointerRunningTexture), POSITION_ALICE_PHOTO_TOP, -ALICE_PHOTO_LENGTH - 2, ALICE_PHOTO_HIGH));
		}
	}
	else
	{
		/// if Alice not move - set stay picture
		AliceSprite.setTextureRect(IntRect(POSITION_ALICE_PHOTO_LEFT + POSITION_ALICE_PHOTO_LEFT, POSITION_ALICE_PHOTO_TOP, ALICE_PHOTO_LENGTH - 2, ALICE_PHOTO_HIGH));
	}

	/// update Alice sprite position
	positionAliceX += timer / ALICE_HORIZONTAL_SPEED * AliceVector;

	if (positionAliceX > ALICE_FINISH_POSITION_IN_CUT_SCENE)
	{
		AliceVector = 0;
		positionAliceX = ALICE_FINISH_POSITION_IN_CUT_SCENE;
	}

	return;
}

Cut_Scene_1_1::Cut_Scene_1_1()
{
}

Cut_Scene_1_1::~Cut_Scene_1_1()
{
}
