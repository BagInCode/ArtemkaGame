#include "Under_Level_1_1.h"

void Under_Level_1_1::makeSound(Music & music)
{
	/*
	* function loading and start the sound
	*/

	music.openFromFile("Music\\Archs.ogg");
	music.setLoop(1);

	music.play();

	return;
}

void Under_Level_1_1::makeSprites()
{
	/*
	*	function of loading pictures in sprites
	*/

	texturesAlice.loadFromFile("textures\\AliceTexture.png");

	AliceSprite.setTexture(texturesAlice);
	AliceSprite.setTextureRect(IntRect(POSITION_ALICE_PHOTO_LEFT, POSITION_ALICE_PHOTO_TOP, ALICE_PHOTO_LENGTH -1, ALICE_PHOTO_HIGH));

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

	ArchSprite[0].setTexture(texturesEnviroment);
	ArchSprite[1].setTexture(texturesEnviroment);
	ArchSprite[2].setTexture(texturesEnviroment);

	ArchSprite[0].setTextureRect(IntRect(POSITION_ARCH_PHOTO_LEFT, POSITION_ARCH_PHOTO_TOP, ARCH_PHOTO_LENGTH, ARCH_PHOTO_HIGH));
	ArchSprite[1].setTextureRect(IntRect(POSITION_ARCH_PHOTO_LEFT + ARCH_PHOTO_LENGTH, POSITION_ARCH_PHOTO_TOP, ARCH_PHOTO_LENGTH, ARCH_PHOTO_HIGH));
	ArchSprite[2].setTextureRect(IntRect(POSITION_ARCH_PHOTO_LEFT + 2 * ARCH_PHOTO_LENGTH, POSITION_ARCH_PHOTO_TOP, ARCH_PHOTO_LENGTH, ARCH_PHOTO_HIGH));

	/// set position for static sprite
	ArchSprite[0].setPosition(POSITION_ARCH_X, POSITION_ARCH_Y);
	ArchSprite[1].setPosition(POSITION_ARCH_X + ARCH_PHOTO_LENGTH, POSITION_ARCH_Y);
	ArchSprite[2].setPosition(POSITION_ARCH_X + 2 * ARCH_PHOTO_LENGTH, POSITION_ARCH_Y);

	nameplateSprite.setTexture(texturesEnviroment);
	nameplateSprite.setTextureRect(IntRect(POSITION_NAMEPLATE_PHOTO_LEFT, POSITION_NAMEPLATE_PHOTO_TOP, NAMEPLATE_PHOTO_LENGTH, NAMEPLATE_PHOTO_HIGH));
	nameplateSprite.setPosition(POSITION_NAMEPLATE_X, POSITION_NAMEPLATE_Y);/// set position for static sprite

	return;
}

void Under_Level_1_1::makePause(Music & music)
{
	/*
	* function of stoping moving
	*/

	music.pause();

	AliceVector = 0;
	AliceJump = 0;
	AliceDownJump = 0;
	keyWPressed = 0;
	keyAPressed = 0;
	keySPressed = 0;
	keyDPressed = 0;

	return;
}

void Under_Level_1_1::makeTextTTC()
{
	/*
	* function of making text TTC
	*/

	font.loadFromFile("Roboto-Regular.ttf");

	text.setFont(font);
	text.setCharacterSize(STANDART_TEXT_SIZE);
	text.setPosition(NAMEPLATE_TEXT_X, NAMEPLATE_TEXT_Y);
	text.setString(problems[pointerAliceStay]);
	text.setFillColor(Color::Black);

	return;
}

bool Under_Level_1_1::switchEvent(Event event, RenderWindow & window, Music & music)
{
	/*
	* function of switching types of event
	*/

	/// if window is close - close
	if (event.type == Event::Closed)
	{
		window.close();
		exit(0);
	}

	/// if widow lost focus - make pause
	if (event.type == Event::LostFocus)
	{
		pause = 1;
		makePause(music);
	}

	/// if Esc pressed - change pause value
	if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
	{
		pause = !pause;

		if (pause)
		{
			makePause(music);
		}
		else
		{
			music.play();
		}
	}

	/// if key D pressed - add to AliceVector one if key D has not already pressed
	if (event.type == Event::KeyPressed && event.key.code == Keyboard::D && !pause)
	{
		AliceVector += (!keyDPressed);
		keyDPressed = 1;
	}

	/// if key A released - add to AliceVector one if key A has not already released
	if (event.type == Event::KeyReleased && event.key.code == Keyboard::A && !pause)
	{
		AliceVector += keyAPressed;
		keyAPressed = 0;
	}

	/// if key A pressed - subtract from AliceVector one if key A has not already released
	if (event.type == Event::KeyPressed && event.key.code == Keyboard::A && !pause)
	{
		AliceVector -= (!keyAPressed);
		keyAPressed = 1;
	}

	/// if key D released - subtract from AliceVector one if key D has not already released
	if (event.type == Event::KeyReleased && event.key.code == Keyboard::D && !pause)
	{
		AliceVector -= keyDPressed;
		keyDPressed = 0;
	}

	/// if key W pressed - make AliceJump
	if (event.type == Event::KeyPressed && event.key.code == Keyboard::W && !pause)
	{
		AliceJump = 1;
		keyWPressed = 1;
	}

	/// if key W released - make AliceJump
	if (event.type == Event::KeyReleased && event.key.code == Keyboard::W && !pause)
	{
		AliceJump = 0;
		keyWPressed = 0;
	}

	/// if key S pressed - make AliceDownJump
	if (event.type == Event::KeyPressed && event.key.code == Keyboard::S && !pause)
	{
		AliceDownJump = 1;
		keySPressed = 1;
	}

	/// if key S released - make AliceDownJump
	if (event.type == Event::KeyReleased && event.key.code == Keyboard::S && !pause)
	{
		AliceDownJump = 0;
		keySPressed = 0;
	}

	/// if LMB pressed and not pause - check path
	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && !pause)
	{
		/// if Alice give all right answeres - return true
		if (!pause && checkPath(window))
		{
			return 1;
		}
	}

	return 0;
}

bool Under_Level_1_1::checkPath(RenderWindow & window)
{
	/*
	* function of checking path
	*/

	/// if Alice is near arch - go to next scene
	if (positionAliceX > COORDINATE_ZERO_ARCH_BEGIN && positionAliceX < COORDINATE_ZERO_ARCH_END)
	{
		pointerAliceStay = pointerAliceStay * (COUNT_ARCHS) + 1;
	}
	if (positionAliceX > COORDINATE_ONE_ARCH_BEGIN && positionAliceX < COORDINATE_ONE_ARCH_END)
	{
		pointerAliceStay = pointerAliceStay * (COUNT_ARCHS) + 2;
	}
	if (positionAliceX > COORDINATE_TWO_ARCH_BEGIN)
	{
		pointerAliceStay = pointerAliceStay * (COUNT_ARCHS) + 3;
	}

	/// if Alice give all right answeres - return true
	if (pointerAliceStay == trueFinish)
	{
		return true;
	}

	/// if Alice make mistake - restart underlevel
	if (pointerAliceStay >= COUNT_PROBLEMS)
	{
		restart(window);
	}

	/// if Alice go throug the arch and not finish path - reinitialization of scene
	if ((positionAliceX > COORDINATE_ZERO_ARCH_BEGIN && positionAliceX < COORDINATE_ZERO_ARCH_END) ||
		(positionAliceX > COORDINATE_ONE_ARCH_BEGIN && positionAliceX < COORDINATE_ONE_ARCH_END) ||
		(positionAliceX > COORDINATE_TWO_ARCH_BEGIN))
	{
		andAgain();
	}

	return false;
}

void Under_Level_1_1::andAgain()
{
	/*
	* function of reinitialization
	*/

	/// set new string
	text.setString(problems[pointerAliceStay]);

	/// set Alice position
	positionAliceX = MIN_ALICE_LEFT_POSITION;
	positionAliceY = MIN_ALICE_DOWN_POSITION;
}

void Under_Level_1_1::restart(RenderWindow & window)
{
	/*
	* function of restarting underlevel
	*/

	/// restart timer
	myClock.restart();

	/// show red screen
	while (myClock.getElapsedTime().asSeconds() < TIME_LOOSE_WAITING)
	{
		window.clear(Color::Red);
		window.display();
	}

	/// reinitialization all needed value
	positionAliceX = MIN_ALICE_LEFT_POSITION;
	positionAliceY = MIN_ALICE_DOWN_POSITION;
	boostAlice = 0;
	timer = 0;
	timerRunningPhoto = 0;
	cloudUpperPointer = 0;
	cloudDownerPointer = 0;
	trueFinish = 0;

	pointerAliceStay = 0;
	pointerRunningTexture = 0;

	pause = 0;

	text.setString(problems[pointerAliceStay]);

	myClock.restart();

	return;
}

void Under_Level_1_1::checkTime(RenderWindow & window)
{
	/*
	* finction of checking time
	*/

	/// if too much time has passed - restart time, move objects, draw picture
	if (myClock.getElapsedTime().asMilliseconds() > MILLI_SECOND_FOR_ACTION)
	{
		timer = myClock.restart().asMilliseconds();
		moveObjects(timer);
		drawPicture(window);
	}

	return;
}

void Under_Level_1_1::moveAlice(double timer)
{
	/*
	* function of updating Alice sprite
	*/

	/// if jump key pressed and Alice is "on ground" -> set Alice boost for jump
	if (AliceJump && round(positionAliceY) == round(MIN_ALICE_DOWN_POSITION))
	{
		boostAlice = ALICE_BOOST;
	}

	/// if down jump key pressed -> set Alice boost for down jump
	if (AliceDownJump)
	{
		boostAlice = -ALICE_BOOST;
	}

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
			AliceSprite.setTextureRect(IntRect(ALICE_PHOTO_LENGTH * (1 + pointerRunningTexture), POSITION_ALICE_PHOTO_TOP, ALICE_PHOTO_LENGTH -2, ALICE_PHOTO_HIGH));
		}
		else
		{
			AliceSprite.setTextureRect(IntRect(ALICE_PHOTO_LENGTH * (2 + pointerRunningTexture)-2, POSITION_ALICE_PHOTO_TOP, -ALICE_PHOTO_LENGTH , ALICE_PHOTO_HIGH));
		}
	}
	else
	{
		/// if Alice not move - set stay picture
		AliceSprite.setTextureRect(IntRect(POSITION_ALICE_PHOTO_LEFT, POSITION_ALICE_PHOTO_TOP, ALICE_PHOTO_LENGTH -1, ALICE_PHOTO_HIGH));
	}

	/// update Alice sprite position
	positionAliceX += timer / ALICE_HORIZONTAL_SPEED * AliceVector;
	positionAliceY -= boostAlice;

	/// check that position is inside window
	positionAliceX = min(positionAliceX, double(MAX_ALICE_RIGHT_POSITION));
	positionAliceX = max(positionAliceX, double(MIN_ALICE_LEFT_POSITION));

	positionAliceY = min(positionAliceY, double(MIN_ALICE_DOWN_POSITION));
	positionAliceY = max(positionAliceY, double(MAX_ALICE_UP_POSITION));

	/// update boost
	boostAlice -= timer / ALICE_BOOST_SPEED;

	/// check that boost is not too smal
	if (boostAlice < MIN_VALUE_BOOST)
	{
		boostAlice = MIN_VALUE_BOOST;
	}

	return;
}

void Under_Level_1_1::moveClouds(double timer)
{
	/*
	* finction of updating clouds sprites
	*/

	/// update clouds pisition
	cloudUpperPointer += timer / UPPER_CLOUDS_SPEED;
	cloudDownerPointer += timer / DOWNER_CLOUDS_SPEED;

	/// if cloud pointer is too big - strat again 
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

void Under_Level_1_1::moveObjects(double timer)
{
	/*
	* function of updating all moovin objects
	*/

	/// if there is pause - goodbye
	if (pause)
	{
		return;
	}

	/// updating objects
	moveAlice(timer);
	moveClouds(timer);

	return;
}

void Under_Level_1_1::drawPicture(RenderWindow & window)
{
	/*
	* function of drawing picture on screen
	*/

	/// clear window, set background colo Cyan
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

	/// draw archs
	window.draw(ArchSprite[0]);
	window.draw(ArchSprite[1]);
	window.draw(ArchSprite[2]);

	/// draw nameplate
	window.draw(nameplateSprite);

	/// draw text on nameplate
	window.draw(text);

	/// draw Alice
	AliceSprite.setPosition(positionAliceX, positionAliceY);
	window.draw(AliceSprite);

	/// if pause - draw pause text
	if (pause)
	{
		window.draw(pauseText);
	}

	window.display();

	return;
}

void Under_Level_1_1::makePauseTextTTC()
{
	/*
	* function of making pause text TTC
	*/

	pauseFont.loadFromFile("Roboto-Regular.ttf");

	pauseText.setFont(pauseFont);
	pauseText.setCharacterSize(pause_TEXT_SIZE);
	pauseText.setPosition(PAUSE_TEXT_X, PAUSE_TEXT_Y);
	pauseText.setString("pause");
	pauseText.setFillColor(Color::Red);
}

void Under_Level_1_1::game(RenderWindow & window, Music & music)
{
	/*
	* main function of class
	*/

	///
	makeSound(music);

	///
	makePauseTextTTC();

	/// make sprites
	makeSprites();

	/// make text TTC
	makeTextTTC();

	/// restart timer
	myClock.restart();

	/// while window not close
	while (window.isOpen())
	{
		Event event;

		/// if there is some events
		if (window.pollEvent(event))
		{
			/// if Alice finish underlevel - stop music and goodbye
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

Under_Level_1_1::Under_Level_1_1()
{
}

Under_Level_1_1::~Under_Level_1_1()
{
}
