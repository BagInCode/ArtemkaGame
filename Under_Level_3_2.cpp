#include "Under_Level_3_2.h"

void Under_Level_3_2::makeSprites()
{
	/*
	*	function of loading pictures in sprites
	*/

	texturesEnviroment.loadFromFile("textures\\EnviromentTexture.png");
	texturesAlice.loadFromFile("textures\\AliceTexture.png");
	texturesDragon.loadFromFile("textures\\DragonTexture.png");

	AliceSprite.setTexture(texturesAlice);
	AliceSprite.setTextureRect(IntRect(POSITION_ALICE_ARMOR_LEFT, POSITION_ALICE_ARMOR_TOP, ALICE_ARMOR_LENGTH - 1, ALICE_ARMOR_HIGH));

	cloudSprite.setTexture(texturesEnviroment);
	cloudSprite.setTextureRect(IntRect(POSITION_CLOUD_PHOTO_LEFT, POSITION_CLOUD_PHOTO_TOP, CLOUD_PHOTO_LENGTH, CLOUD_PHOTO_HIGH));

	groundSprite.setTexture(texturesEnviroment);
	groundSprite.setTextureRect(IntRect(POSITION_GROUND_PHOTO_LEFT, POSITION_GROUND_PHOTO_TOP, GROUND_PHOTO_LENGTH, GROUND_PHOTO_HIGH));

	backGroundSprite.setTexture(texturesEnviroment);
	backGroundSprite.setTextureRect(IntRect(POSITION_BACKGROUND_PHOTO_LEFT, POSITION_BACKGROUND_PHOTO_TOP, BACKGROUND_PHOTO_LENGTH, BACKGROUND_PHOTO_HIGH));

	sunSprite.setTexture(texturesEnviroment);
	sunSprite.setTextureRect(IntRect(POSITION_SUN_PHOTO_LEFT, POSITION_SUN_PHOTO_TOP, SUN_PHOTO_LENGTH, SUN_PHOTO_HIGH));
	sunSprite.setPosition(POSITION_SUN_X, POSITION_SUN_Y); /// set position for static sprite
	
	cactusSprite.setTexture(texturesEnviroment);
	cactusSprite.setTextureRect(IntRect(POSITION_CACTUS_BIG_LEFT, POSITION_CACTUS_BIG_TOP, CACTUS_BIG_LENGTH, CACTUS_BIG_HIGH));

	return;
}

void Under_Level_3_2::moveAlice(double timer)
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

	/// timerRunningPhoto - how long we show current run picture, increse this value
	timerRunningPhoto += timer;

	/// if we show current run picture too long - set pointer on next picture and start timer again
	if (timerRunningPhoto > MILLI_SECOND_FOR_ONE_PHOTO)
	{
		timerRunningPhoto = 0;
		pointerRunningTexture = (pointerRunningTexture + 1) % (COUNT_ALICE_PHOTO - 1);
	}

	AliceSprite.setTextureRect(IntRect(POSITION_ALICE_ARMOR_LEFT + ALICE_ARMOR_LENGTH * (1 + pointerRunningTexture), POSITION_ALICE_ARMOR_TOP + KICK_PHOTO_DISPLACEMENT, ALICE_ARMOR_LENGTH - 1, ALICE_ARMOR_HIGH));

	/// update position
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

void Under_Level_3_2::generateCactusesPosition()
{
	srand(time(0));

	cactusesPositions.clear();

	int position = rand() % 150;

	position += WINDOW_LENGTH;

	cactusesPositions.push_back({ position, rand() % 3 +1 });

	for (int i = 1; i < COUNT_CACTUSES; i++)
	{
		position = cactusesPositions.back().first + DISPLACEMENT_BY_CACTUSES;

		position += rand() % 150;

		cactusesPositions.push_back({ position, rand() % 3 + 1 });
	}

	return;
}


void Under_Level_3_2::moveClouds(double timer)
{
	/*
	* finction of updating clouds sprite
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

void Under_Level_3_2::makePause(Music & music)
{
	/*
	* function of stoping moving on pause
	*/

	music.pause();

	pause = 1;

	AliceVector = 0;
	AliceJump = 0;
	keyWPressed = 0;
	keyAPressed = 0;
	keySPressed = 0;
	keyDPressed = 0;

	return;
}

void Under_Level_3_2::restart(RenderWindow & window)
{
	/*
	* function of restarting underlevel
	*/

	/// restart clock
	myClock.restart();

	/// show the red screen
	while (myClock.getElapsedTime().asSeconds() < TIME_LOOSE_WAITING)
	{
		window.clear(Color::Red);
		window.display();
	}

	/// reinitialization of all needed value
	timer = 0;

	positionAliceX = MIN_ALICE_LEFT_POSITION;
	positionAliceY = MIN_ALICE_DOWN_POSITION;
	timerRunningPhoto = 0;
	boostAlice = 0;

	cloudUpperPointer = 0;
	cloudDownerPointer = 0;

	pointerRunningTexture = 0;

	globalDisplacement = 0;
	backGroundDisplacement = 0;

	pause = 0;

	generateCactusesPosition();

	myClock.restart();

	return;
}

void Under_Level_3_2::checkIntersect(RenderWindow & window)
{
	/*
	* function if checking intersection of Dragon sprite and Alice sprite
	*/

	for (int i = 0; i < cactusesPositions.size(); i++)
	{
		/// finding vertex of rectngle of intersection 
		int leftX = round(max(positionAliceX + globalDisplacement, cactusesPositions[i].first + 0.));
		int rightX = round(min(positionAliceX + globalDisplacement + ALICE_ARMOR_LENGTH, cactusesPositions[i].first + CACTUS_BIG_LENGTH * cactusesPositions[i].second + 0.));
		int upY = round(max(positionAliceY, MIN_ALICE_DOWN_POSITION));
		int downY = round(min(positionAliceY + ALICE_ARMOR_HIGH, MIN_ALICE_DOWN_POSITION + CACTUS_BIG_HIGH));

		/// if rectangle with not positive square - goodbye 
		if (downY < upY || leftX > rightX) continue;

		/// if intersection came - restart
		restart(window);
		return;
	}

	return;
}

void Under_Level_3_2::moveObjects(RenderWindow & window, double timer)
{
	/*
	* function of updating all moving objects
	*/

	/// if there is pause - don`t move anything
	if (pause)
	{
		return;
	}

	/// update objects
	moveAlice(timer);
	moveClouds(timer);

	/// check that everthing is good
	checkIntersect(window);

	return;
}

bool Under_Level_3_2::switchEvent(Event event, RenderWindow & window, Music & music)
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

	if (globalDisplacement > 
		cactusesPositions.back().first)
	{
		return 1;
	}

	return 0;
}

void Under_Level_3_2::checkTime(RenderWindow & window)
{
	/*
	* function of checking time
	*/

	/// if too much time has passed - restart timer, move objects and draw new picture on screen
	if (myClock.getElapsedTime().asMilliseconds() > MILLI_SECOND_FOR_ACTION)
	{
		timer = myClock.restart().asMilliseconds();

		if (!pause)
		{
			globalDisplacement += ALICE_HORIZONTAL_SPEED * timer / 10;
			groundDisplacement += ALICE_HORIZONTAL_SPEED * timer / 10;
			backGroundDisplacement += ALICE_HORIZONTAL_SPEED * timer / 50;

			for(; backGroundDisplacement > BACKGROUND_PHOTO_LENGTH; backGroundDisplacement -= BACKGROUND_PHOTO_LENGTH){}
			for(; groundDisplacement > GROUND_PHOTO_LENGTH; groundDisplacement -= GROUND_PHOTO_LENGTH) {}

			moveObjects(window, timer);
		}

		drawPicture(window);
		
	}

	return;
}

void Under_Level_3_2::drawPicture(RenderWindow & window)
{
	/*
	* function of drawing picture on screen
	*/

	/// clear window, set background colo Cyan
	window.clear(Color::Cyan);

	/// drawing ground
	for (int i = 0; i < COUNT_GROUND_SPRITES_ON_SCREEN + 5; i++)
	{
		groundSprite.setPosition(POSITION_GROUND_SPRITE_X*i - groundDisplacement, POSITION_GROUND_SPRITE_Y);
		window.draw(groundSprite);
	}

	/// drawing background 
	for (int i = 0; i < COUNT_BACKGROUND_SPRITES_ON_SCREEN + 1; i++)
	{
		backGroundSprite.setPosition(POSITION_BACKGROUND_SPRITE_X*i - backGroundDisplacement, POSITION_BACKGROUND_SPRITE_Y);
		window.draw(backGroundSprite);
	}

	/// drawing sun
	window.draw(sunSprite);

	/// drawing clouds
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

	///drawing Alice
	AliceSprite.setPosition(positionAliceX, positionAliceY);
	window.draw(AliceSprite);

	/// draw cactuses
	for (int i = 0; i < cactusesPositions.size(); i++)
	{
		for (int j = 0; j < cactusesPositions[i].second; j++)
		{
			cactusSprite.setPosition(cactusesPositions[i].first - globalDisplacement + CACTUS_BIG_LENGTH * j, MIN_ALICE_DOWN_POSITION);
			window.draw(cactusSprite);
		}
	}
	

	/// if there is pause - drawing pause text
	if (pause)
	{
		window.draw(pauseText);
	}

	window.display();

	return;
}

void Under_Level_3_2::game(RenderWindow & window, Music & music)
{
	/*
	* main function of class
	*/

	/// make pause text TTC
	pauseFont.loadFromFile("Roboto-Regular.ttf");

	pauseText.setFont(pauseFont);
	pauseText.setCharacterSize(pause_TEXT_SIZE);
	pauseText.setPosition(PAUSE_TEXT_X, PAUSE_TEXT_Y);
	pauseText.setString("pause");
	pauseText.setFillColor(Color::Red);

	/// make random more randomly
	srand(time(0));

	generateCactusesPosition();

	/// make sprites
	makeSprites();

	/// restart timer
	myClock.restart();

	/// while not window close
	while (window.isOpen())
	{
		Event event;

		/// if there is some events
		if (window.pollEvent(event))
		{
			/// if Alice make final kick - finish underlevel
			if (switchEvent(event, window, music))
			{
				music.stop();
				return;
			}
		}

		/// check time
		checkTime(window);
	}

	return;
}

Under_Level_3_2::Under_Level_3_2()
{
}


Under_Level_3_2::~Under_Level_3_2()
{
}
