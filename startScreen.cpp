#include "startScreen.h"

void startScreen::makeSprites()
{
	/*
	* function of loading pictures in sprites
	*/

	texturesAlice.loadFromFile("textures\\AliceTexture.png");

	AliceSprite.setTexture(texturesAlice);
	AliceSprite.setTextureRect(IntRect(POSITION_ALICE_PHOTO_LEFT, POSITION_ALICE_PHOTO_TOP, ALICE_PHOTO_LENGTH - 1, ALICE_PHOTO_HIGH));

	AliceHeadSprite.setTexture(texturesAlice);
	AliceHeadSprite.setTextureRect(IntRect(POSITION_ALICE_HEAD_PHOTO_LEFT, POSITION_ALICE_HEAD_PHOTO_TOP, HEAD_PHOTO_LENGTH, HEAD_PHOTO_HIGH));
	AliceHeadSprite.setPosition(629, 310);

	texturesDargon.loadFromFile("textures\\DragonTexture.png");

	DragonSprite.setTexture(texturesDargon);
	DragonSprite.setTextureRect(IntRect(POSITION_DRAGON_PHOTO_LEFT, POSITION_DRAGON_PHOTO_TOP, DRAGON_PHOTO_LENGTH, DRAGON_PHOTO_HIGH));
	DragonSprite.setPosition(600, MIN_DRAGON_DOWN_POSITION);

	Circle = CircleShape(35);
	Circle.setFillColor(Color::White);
	Circle.setPosition(615, 300);

	return;
}

void startScreen::moveObjects(double timer)
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

	/// check Alice position
	checkAlice();

	/// moveing Dragon
	moveDragon(timer);

	/// checkDragonPosition
	checkDragon();

	return;
}

bool startScreen::switchEvent(Event event, RenderWindow & window)
{
	/*
	* function of switching type of event
	*/

	/// if window lost focus - make pause
	if (event.type == Event::LostFocus)
	{
		pause = 1;
	}

	/// if indow gain focus - resume
	if (event.type == Event::GainedFocus)
	{
		pause = 0;
	}

	/// if window close - close
	if (event.type == Event::Closed)
	{
		window.close();
		exit(0);
	}

	/// if LMB pressed
	if (event.type == Event::MouseButtonPressed || event.type == Event::KeyPressed)
	{
		if (secondScreen)
		{
			return 1;
		}
		else
		{
			secondScreen = 1;
		}
	}

	return 0;
}

void startScreen::moveAlice(double timer)
{
	/*
	* function of updating Alice sprite
	*/

	/// increase timer how long show current running picture
	timerRunningPhotoAlice += timer;

	/// if show too long - null timer, set pointer on next picture
	if (timerRunningPhotoAlice > MILLI_SECOND_FOR_ONE_PHOTO)
	{
		timerRunningPhotoAlice = 0;
		pointerRunningTextureAlice = (pointerRunningTextureAlice + 1) % (COUNT_ALICE_PHOTO - 1);
	}

	/// set running picture
	if (vectorAliceX > 0)
	{
		if (inverseAlice)
		{
			AliceSprite.setTextureRect(IntRect(ALICE_PHOTO_LENGTH * (2 + pointerRunningTextureAlice), POSITION_ALICE_PHOTO_TOP, -ALICE_PHOTO_LENGTH + 1, ALICE_PHOTO_HIGH));
		}
		else
		{
			AliceSprite.setTextureRect(IntRect(ALICE_PHOTO_LENGTH * (1 + pointerRunningTextureAlice), POSITION_ALICE_PHOTO_TOP, ALICE_PHOTO_LENGTH - 1, ALICE_PHOTO_HIGH));
		}
	}
	else
	{
		if (inverseAlice)
		{
			AliceSprite.setTextureRect(IntRect(ALICE_PHOTO_LENGTH * (1 + pointerRunningTextureAlice), POSITION_ALICE_PHOTO_TOP, ALICE_PHOTO_LENGTH - 1, ALICE_PHOTO_HIGH));
		}
		else
		{
			AliceSprite.setTextureRect(IntRect(ALICE_PHOTO_LENGTH * (2 + pointerRunningTextureAlice), POSITION_ALICE_PHOTO_TOP, -ALICE_PHOTO_LENGTH + 1, ALICE_PHOTO_HIGH));
		}
	}
	/// update position
	positionAliceX += timer / ALICE_HORIZONTAL_SPEED * vectorAliceX;
	positionAliceY += timer / ALICE_HORIZONTAL_SPEED * vectorAliceY;

	return;
}

void startScreen::checkAlice()
{
	if (positionAliceX > -ALICE_PHOTO_LENGTH - 1 && positionAliceX < WINDOW_LENGTH + ALICE_PHOTO_LENGTH + 1 &&
		positionAliceY < WINDOW_HEIGH + ALICE_PHOTO_HIGH +1 && positionAliceY > -ALICE_PHOTO_HIGH -1)
	{
		return;
	}

	srand(time(0));

	int x = rand() % 12;

	vectorAliceX = cos(mas[x]);
	vectorAliceY = sin(mas[x]);

	if (vectorAliceX > 0)
	{
		positionAliceX = -ALICE_PHOTO_LENGTH;
	}
	else
	{
		positionAliceX = WINDOW_LENGTH + ALICE_PHOTO_LENGTH;
	}

	positionAliceY = rand() % (WINDOW_HEIGH - ALICE_PHOTO_HIGH + 1); 
	inverseAlice = rand() % 10;
	inverseAlice = !inverseAlice;

	return;
}

void startScreen::moveDragon(double timer)
{
	/*
	* function of updating dragon sprite
	*/

	/// increase timer how long show current running picture
	timerRunningPhotoDragon += timer;

	/// if show too long - null timer, set pointer on next picture
	if (timerRunningPhotoDragon > TIMER_DRAGON_STEP)
	{
		timerRunningPhotoDragon = 0;
		pointerRunningTextureDragon = (pointerRunningTextureDragon + 1) % (COUNT_DRAGON_PHOTO - 1);
	}

	/// set running picture
	if (vectorDragonX > 0)
	{
		if (inverseDragon)
		{
			DragonSprite.setTextureRect(IntRect(DRAGON_PHOTO_LENGTH * (1 + pointerRunningTextureDragon), POSITION_DRAGON_PHOTO_TOP, DRAGON_PHOTO_LENGTH - 1, DRAGON_PHOTO_HIGH));
		}
		else
		{
			DragonSprite.setTextureRect(IntRect(DRAGON_PHOTO_LENGTH * (2 + pointerRunningTextureDragon), POSITION_DRAGON_PHOTO_TOP, -DRAGON_PHOTO_LENGTH + 1, DRAGON_PHOTO_HIGH));
		}
	}
	else
	{
		if (inverseDragon)
		{
			DragonSprite.setTextureRect(IntRect(DRAGON_PHOTO_LENGTH * (2 + pointerRunningTextureDragon), POSITION_DRAGON_PHOTO_TOP, -DRAGON_PHOTO_LENGTH + 1, DRAGON_PHOTO_HIGH));
		}
		else
		{
			DragonSprite.setTextureRect(IntRect(DRAGON_PHOTO_LENGTH * (1 + pointerRunningTextureDragon), POSITION_DRAGON_PHOTO_TOP, DRAGON_PHOTO_LENGTH - 1, DRAGON_PHOTO_HIGH));
		}
		
	}

	/// update position
	positionDragonX += timer / DRAGON_HORIZONTAL_SPEED * vectorDragonX;
	positionDragonY += timer / DRAGON_HORIZONTAL_SPEED * vectorDragonY;

	return;
}

void startScreen::checkDragon()
{
	if (positionDragonX > -DRAGON_PHOTO_LENGTH - 1 && positionDragonX < WINDOW_LENGTH + DRAGON_PHOTO_LENGTH + 1 &&
		positionDragonY < WINDOW_HEIGH + DRAGON_PHOTO_HIGH +1 && positionDragonY > -DRAGON_PHOTO_HIGH -1)
	{
		return;
	}

	srand(time(0));

	int x = rand() % 12;

	vectorDragonX = cos(mas[x]);
	vectorDragonY = sin(mas[x]);

	if (vectorDragonX > 0)
	{
		positionDragonX = -DRAGON_PHOTO_LENGTH;
	}
	else
	{
		positionDragonX = WINDOW_LENGTH + DRAGON_PHOTO_LENGTH;
	}

	positionDragonY = rand() % (WINDOW_HEIGH - DRAGON_PHOTO_HIGH + 1);
	inverseDragon = rand() % 10;
	inverseDragon = !inverseDragon;

	return;
}

void startScreen::makeTextTTC()
{
	/*
	* function of setting text ttc
	*/

	font.loadFromFile("Roboto-Regular.ttf");

	text.setFont(font);
	text.setCharacterSize(STANDART_TEXT_SIZE*2);
	text.setFillColor(Color::White);
	text.setString("Press any key to continue");
	text.setPosition(500, 380);
	text.setStyle(Text::Bold);

	return;
}

void startScreen::checkTime(RenderWindow & window)
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

void startScreen::drawPicture(RenderWindow & window)
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
	window.clear(Color::Black);
	
	AliceSprite.setPosition(positionAliceX, positionAliceY);
	DragonSprite.setPosition(positionDragonX, positionDragonY);

	window.draw(AliceSprite);
	window.draw(DragonSprite);

	window.draw(Circle);
	window.draw(AliceHeadSprite);
	window.draw(text);

	if (secondScreen)
	{
		window.clear(Color::Black);

		text.setString("\tControl\nA - move left\nW - jump/move up\nS - down jump/moveDown\nD - move right\nLMB - choose/attack\n(To choose arch stay insight and press LMB)");
	
		text.setPosition(10, 10);

		window.draw(text);
	}

	window.display();

	return;
}

void startScreen::start(RenderWindow & window)
{
	/*
	* main function of class
	*/

	/// make sprites
	makeSprites();

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
			if (switchEvent(event, window))
			{
				return;
			}
		}

		/// check time
		checkTime(window);
	}

	return;
}

startScreen::startScreen()
{
}


startScreen::~startScreen()
{
}
