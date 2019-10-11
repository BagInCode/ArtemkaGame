#include "Under_Level_1_2.h"

void Under_Level_1_2::makeSprites()
{
	/*
	*	function of loading pictures in sprites
	*/

	texturesEnviroment.loadFromFile("textures\\EnviromentTexture.png");
	texturesAlice.loadFromFile("textures\\AliceTexture.png");
	texturesDragon.loadFromFile("textures\\DragonTexture.png");

	AliceSprite.setTexture(texturesAlice);
	AliceSprite.setTextureRect(IntRect(POSITION_ALICE_PHOTO_LEFT, POSITION_ALICE_PHOTO_TOP, ALICE_PHOTO_LENGTH-1, ALICE_PHOTO_HIGH));

	cloudSprite.setTexture(texturesEnviroment);
	cloudSprite.setTextureRect(IntRect(POSITION_CLOUD_PHOTO_LEFT, POSITION_CLOUD_PHOTO_TOP, CLOUD_PHOTO_LENGTH, CLOUD_PHOTO_HIGH));

	groundSprite.setTexture(texturesEnviroment);
	groundSprite.setTextureRect(IntRect(POSITION_GROUND_PHOTO_LEFT, POSITION_GROUND_PHOTO_TOP, GROUND_PHOTO_LENGTH, GROUND_PHOTO_HIGH));

	backGroundSprite.setTexture(texturesEnviroment);
	backGroundSprite.setTextureRect(IntRect(POSITION_BACKGROUND_PHOTO_LEFT, POSITION_BACKGROUND_PHOTO_TOP, BACKGROUND_PHOTO_LENGTH, BACKGROUND_PHOTO_HIGH));

	sunSprite.setTexture(texturesEnviroment);
	sunSprite.setTextureRect(IntRect(POSITION_SUN_PHOTO_LEFT, POSITION_SUN_PHOTO_TOP, SUN_PHOTO_LENGTH, SUN_PHOTO_HIGH));
	sunSprite.setPosition(POSITION_SUN_X, POSITION_SUN_Y); /// set position for static sprite

	fireSprite.setTexture(texturesDragon);

	DragonSprite.setTexture(texturesDragon);
	DragonSprite.setTextureRect(IntRect(POSITION_DRAGON_PHOTO_LEFT, POSITION_DRAGON_PHOTO_TOP, DRAGON_PHOTO_LENGTH, DRAGON_PHOTO_HIGH));

	return;
}

void Under_Level_1_2::makePause(Music & music)
{
	/*
	* function of stoping moving on pause
	*/

	music.pause();

	AliceVector = 0;
	AliceJump = 0;
	keyWPressed = 0;
	keyAPressed = 0;
	keySPressed = 0;
	keyDPressed = 0;

	return;
}

void Under_Level_1_2::moveAlice(double timer)
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

	/// if Alice kick Dragon
	if (AliceKick)
	{
		/// timerKickPhoto - how long we show kick pictures, increse this value
		timerKickPhoto += timer;

		/// if time for kick is finish, we stop kicking and make timer equal 0
		if (timerKickPhoto > MILLI_SECOND_FOR_KICK_PHOTO)
		{
			timerKickPhoto = 0;
			AliceKick = 0;
		}
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
			AliceSprite.setTextureRect(IntRect(ALICE_PHOTO_LENGTH * (1 + pointerRunningTexture), KICK_PHOTO_DISPLACEMENT * AliceKick, ALICE_PHOTO_LENGTH-1, ALICE_PHOTO_HIGH));
		}
		else
		{
			AliceSprite.setTextureRect(IntRect(ALICE_PHOTO_LENGTH * (2 + pointerRunningTexture)-1, KICK_PHOTO_DISPLACEMENT * AliceKick, -ALICE_PHOTO_LENGTH+1, ALICE_PHOTO_HIGH));
		}
	}
	else
	{
		/// if Alice if right from dragon - set picture from left to right, else - set picture back
		if (positionAliceX < positionDragonX + TURN_DRAGON_DISPLACEMENT)
		{
			AliceSprite.setTextureRect(IntRect(0, KICK_PHOTO_DISPLACEMENT * AliceKick, ALICE_PHOTO_LENGTH-1, ALICE_PHOTO_HIGH));
		}
		else
		{
			AliceSprite.setTextureRect(IntRect(ALICE_PHOTO_LENGTH, KICK_PHOTO_DISPLACEMENT * AliceKick, -ALICE_PHOTO_LENGTH, ALICE_PHOTO_HIGH));
		}
	}

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

void Under_Level_1_2::moveClouds(double timer)
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

void Under_Level_1_2::moveDragon(double timer)
{
	/*
	* function of updating dragon sprite
	*/

	/// if dragon move horizontally, and it is in final position - stop horizontally moving
	if ((dragonVector > 0) == (positionDragonX > finalPositionDragon))
	{
		dragonVector = 0;
		positionDragonX = finalPositionDragon;
	}

	/// if dragon stop moving (so it is in final position) and "on ground" - start time of stay, else - it isn`t stay
	if (dragonVector == 0 && round(positionDragonY) == round(MIN_DRAGON_DOWN_POSITION))
	{
		positionDragonY = MIN_DRAGON_DOWN_POSITION;

		timerDragonStay += timer;
	}
	else
	{
		timerDragonStay = 0;
	}

	if (dragonVector)
	{
		dragonTimer += timer;

		if (dragonTimer > TIMER_DRAGON_STEP)
		{
			dragonTimer = 0;
			pointerDragonTexture = (pointerDragonTexture + 1) % COUNT_DRAGON_PHOTO;
		}
	}
	else
	{
		dragonTimer = 0;
	}

	if (timerDragonStay > FIRST_BREATH_TIMER)
	{
		pointerDragonTexture = 4;
	}

	if (timerDragonStay > SECOND_BREATH_TIMER)
	{
		pointerDragonTexture = 5;
	}

	if (timerDragonStay > THIRD_BREATH_TIMER)
	{
		pointerDragonTexture = 6;
	}

	/// if it is time for show first fire picture - set pointer
	if (timerDragonStay > FIRST_FIRE_TIMER)
	{
		pointerDragonFire = 1;
		pointerDragonTexture = 7;
	}

	/// if it is time for show second fire picture - set pointer
	if (timerDragonStay > SECOND_FIRE_TIMER)
	{
		pointerDragonFire = 2;
	}

	/// if it is time for show third fire picture - set pointer
	if (timerDragonStay > THIRD_FIRE_TIMER)
	{
		pointerDragonFire = 3;
	}

	/// if it is time for show fourth fire picture - set pointer
	if (timerDragonStay > FOURTH_FIRE_TIMER)
	{
		pointerDragonFire = 4;
	}

	/// if it is time for show fifth fire picture - set pointer
	if (timerDragonStay > FIFTH_FIRE_TIMER)
	{
		pointerDragonFire = 5;
	}

	/// if dragon stay too long - set pointer of fire, set boost vertically, set new final position 
	if (timerDragonStay > MAX_DRAGON_STAY)
	{
		pointerDragonFire = 0;
		pointerDragonTexture = 0;

		finalPositionDragon = positionDragonX + ((rand() % DRAGON_RANDOM_MODUL) - DRAGON_RANDOM_DISPLACEMENT);

		finalPositionDragon = max(finalPositionDragon, MIN_DRAGON_LEFT_POSITION + 1);
		finalPositionDragon = min(finalPositionDragon, MAX_DRAGON_RIGHT_POSITION - 1);

		dragonVector = (finalPositionDragon > positionDragonX ? 1 : -1);

		boostDragon = DRAGON_BOOST;
	}

	/// update position
	positionDragonY -= boostDragon;
	positionDragonX += timer / DRAGON_HORIZONTAL_SPEED * dragonVector;

	/// check, that position is inside of window
	positionDragonX = min(positionDragonX, MAX_DRAGON_RIGHT_POSITION);
	positionDragonX = max(positionDragonX, MIN_DRAGON_LEFT_POSITION);

	positionDragonY = max(positionDragonY, MAX_DRAGON_UP_POSITION);
	positionDragonY = min(positionDragonY, MIN_DRAGON_DOWN_POSITION);

	/// update boost
	boostDragon -= timer / DRAGON_BOOST_SPEED;

	/// if dragon if left from Alice - set dragon fire vector on right
	if (positionAliceX > positionDragonX)
	{
		DragonFireVector = 1;
	}
	else
	{
		DragonFireVector = 0;
	}

	/// if Alice if left from dragon - set dragon picture from left to right, else - set picture back
	if (positionAliceX > positionDragonX + TURN_DRAGON_DISPLACEMENT)
	{
		DragonSprite.setTextureRect(IntRect(POSITION_DRAGON_PHOTO_LEFT + DRAGON_PHOTO_LENGTH, POSITION_DRAGON_PHOTO_TOP, -DRAGON_PHOTO_LENGTH, DRAGON_PHOTO_HIGH));
	}
	else
	{
		DragonSprite.setTextureRect(IntRect(POSITION_DRAGON_PHOTO_LEFT, POSITION_DRAGON_PHOTO_TOP, DRAGON_PHOTO_LENGTH, DRAGON_PHOTO_HIGH));
	}

	return;
}

void Under_Level_1_2::checkFire(RenderWindow & window)
{
	/*
	* function of cheking intersect fire sprite & Alice sprite
	*/

	/// if there is no fire - goodbye
	if (pointerDragonFire == 0)
	{
		return;
	}

	/// if there is intersect - restart underlevel
	if (pointerDragonFire == 1)
	{
		if (positionAliceX > positionDragonX - ONE_FIRE_DISPLACEMENT - ALICE_PHOTO_LENGTH &&
			positionAliceX < positionDragonX + ONE_FIRE_DISPLACEMENT + DRAGON_PHOTO_LENGTH &&
			positionAliceY > MIN_ALICE_DOWN_POSITION - ALICE_DISPLACEMENT_ABOUT_DRAGON_FIRE_BY_VERTICAL)
		{
			restart(window);
		}
	}

	if (pointerDragonFire == 2)
	{
		if (positionAliceX > positionDragonX - TWO_FIRE_DISPLACEMENT - ALICE_PHOTO_LENGTH &&
			positionAliceX < positionDragonX + TWO_FIRE_DISPLACEMENT + DRAGON_PHOTO_LENGTH &&
			positionAliceY > MIN_ALICE_DOWN_POSITION - ALICE_DISPLACEMENT_ABOUT_DRAGON_FIRE_BY_VERTICAL)
		{
			restart(window);
		}
	}

	if (pointerDragonFire == 3)
	{
		if (positionAliceX > positionDragonX - THREE_FIRE_DISPLACEMENT - ALICE_PHOTO_LENGTH &&
			positionAliceX < positionDragonX + THREE_FIRE_DISPLACEMENT + DRAGON_PHOTO_LENGTH &&
			positionAliceY > MIN_ALICE_DOWN_POSITION - ALICE_DISPLACEMENT_ABOUT_DRAGON_FIRE_BY_VERTICAL)
		{
			restart(window);
		}
	}

	if (pointerDragonFire == 4)
	{
		if (((positionAliceX > positionDragonX - THREE_FIRE_DISPLACEMENT - ALICE_PHOTO_LENGTH &&
			positionAliceX < positionDragonX - ONE_FIRE_DISPLACEMENT) ||
			(positionAliceX > positionDragonX + DRAGON_PHOTO_LENGTH + ONE_FIRE_DISPLACEMENT - ALICE_PHOTO_LENGTH &&
				positionAliceX < positionDragonX + THREE_FIRE_DISPLACEMENT + DRAGON_PHOTO_LENGTH)) &&
				(positionAliceY > MIN_ALICE_DOWN_POSITION - ALICE_DISPLACEMENT_ABOUT_DRAGON_FIRE_BY_VERTICAL))
		{
			restart(window);
		}
	}

	if (pointerDragonFire == 5)
	{

		if (((positionAliceX > positionDragonX - THREE_FIRE_DISPLACEMENT - ALICE_PHOTO_LENGTH &&
			positionAliceX < positionDragonX - TWO_FIRE_DISPLACEMENT) ||
			(positionAliceX > positionDragonX + TWO_FIRE_DISPLACEMENT + DRAGON_PHOTO_LENGTH - ALICE_PHOTO_LENGTH &&
				positionAliceX < positionDragonX + THREE_FIRE_DISPLACEMENT + DRAGON_PHOTO_LENGTH)) &&
				(positionAliceY > MIN_ALICE_DOWN_POSITION - ALICE_DISPLACEMENT_ABOUT_DRAGON_FIRE_BY_VERTICAL))
		{
			restart(window);
		}
	}

	return;
}

void Under_Level_1_2::restart(RenderWindow & window)
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
	timerKickPhoto = 0;

	cloudUpperPointer = 0;
	cloudDownerPointer = 0;

	positionDragonX = MAX_DRAGON_RIGHT_POSITION;
	positionDragonY = MIN_DRAGON_DOWN_POSITION;
	finalPositionDragon = MAX_DRAGON_RIGHT_POSITION;
	boostDragon = 0;
	timerDragonStay = 0;

	pointerRunningTexture = 0;
	dragonVector = 0;
	dragonHP = DRAGON_HEALTH_POINTS;
	pointerDragonFire = 0;

	AliceKick = 0;
	pause = 0;
	DragonFireVector = 0;

	myClock.restart();

	return;
}

void Under_Level_1_2::checkIntersect(RenderWindow & window)
{
	/*
	* function if checking intersection of Dragon sprite and Alice sprite
	*/

	/// finding vertex of rectngle of intersection 
	int leftX = round(max(positionAliceX, positionDragonX));
	int rightX = round(min(positionAliceX + ALICE_PHOTO_LENGTH, positionDragonX + DRAGON_PHOTO_LENGTH));
	int upY = round(max(positionAliceY, positionDragonY));
	int downY = round(min(positionAliceY + ALICE_PHOTO_HIGH, positionDragonY + DRAGON_PHOTO_HIGH));

	/// if rectangle with not positive square - goodbye 
	if (downY < upY || leftX > rightX) return;

	/// if intersection came from left or right - stop dragon and stay Alice near it, else - restart
	if (downY - upY > rightX - leftX)
	{
		if (positionAliceX > positionDragonX)
		{
			positionAliceX = positionDragonX + DRAGON_PHOTO_LENGTH;
		}
		else
		{
			positionAliceX = positionDragonX - ALICE_PHOTO_LENGTH;
		}

		finalPositionDragon = positionDragonX;
		dragonVector = 0;
	}
	else
	{
		restart(window);
	}

	return;
}

void Under_Level_1_2::moveObjects(RenderWindow & window, double timer)
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
	moveDragon(timer);

	/// check that everthing is good
	checkIntersect(window);
	checkFire(window);

	return;
}

void Under_Level_1_2::drawPicture(RenderWindow & window)
{
	/*
	* function of drawing picture on screen
	*/

	/// clear window, set background colo Cyan
	window.clear(Color::Cyan);

	/// drawing ground
	for (int i = 0; i < COUNT_GROUND_SPRITES_ON_SCREEN; i++)
	{
		groundSprite.setPosition(POSITION_GROUND_SPRITE_X*i, POSITION_GROUND_SPRITE_Y);
		window.draw(groundSprite);
	}

	/// drawing background 
	for (int i = 0; i < COUNT_BACKGROUND_SPRITES_ON_SCREEN; i++)
	{
		backGroundSprite.setPosition(POSITION_BACKGROUND_SPRITE_X*i, POSITION_BACKGROUND_SPRITE_Y);
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

	/// drawing dragon
	DragonSprite.setTextureRect(IntRect(POSITION_DRAGON_PHOTO_LEFT + pointerDragonTexture * DRAGON_PHOTO_LENGTH, POSITION_DRAGON_PHOTO_TOP, DRAGON_PHOTO_LENGTH, DRAGON_PHOTO_HIGH));
	DragonSprite.setPosition(positionDragonX, positionDragonY);
	window.draw(DragonSprite);

	DragonSprite.setColor(Color::White);

	///drawing Alice
	AliceSprite.setPosition(positionAliceX, positionAliceY);
	window.draw(AliceSprite);

	/// drawing fire
	if (pointerDragonFire == 1)
	{
		if (DragonFireVector)
		{
			fireSprite.setTextureRect(IntRect(POSITION_DRAGON_FIRE_PHOTO_LEFT + DRAGON_FIRE_PHOTO_LENGTH - 1, POSITION_DRAGON_FIRE_PHOTO_TOP, -DRAGON_FIRE_PHOTO_LENGTH + 2, DRAGON_FIRE_PHOTO_HIGH));
			fireSprite.setPosition(positionDragonX + DRAGON_PHOTO_LENGTH, positionDragonY + DISPLACENET_DRAGON_FIRE_ABOUT_DRAGON_BY_Y);

			window.draw(fireSprite);
		}
		else
		{
			fireSprite.setTextureRect(IntRect(POSITION_DRAGON_FIRE_PHOTO_LEFT - 1, POSITION_DRAGON_FIRE_PHOTO_TOP, DRAGON_FIRE_PHOTO_LENGTH - 2, DRAGON_FIRE_PHOTO_HIGH));
			fireSprite.setPosition(positionDragonX - DRAGON_FIRE_PHOTO_LENGTH, positionDragonY + DISPLACENET_DRAGON_FIRE_ABOUT_DRAGON_BY_Y);

			window.draw(fireSprite);
		}
	}

	if (pointerDragonFire == 2)
	{
		if (DragonFireVector)
		{
			fireSprite.setTextureRect(IntRect(POSITION_DRAGON_FIRE_PHOTO_LEFT + 3 * DRAGON_FIRE_PHOTO_LENGTH - 1, POSITION_DRAGON_FIRE_PHOTO_TOP, -2 * DRAGON_FIRE_PHOTO_LENGTH + 3, DRAGON_FIRE_PHOTO_HIGH));
			fireSprite.setPosition(positionDragonX + DRAGON_PHOTO_LENGTH, positionDragonY + DISPLACENET_DRAGON_FIRE_ABOUT_DRAGON_BY_Y);
			window.draw(fireSprite);
		}
		else
		{
			fireSprite.setTextureRect(IntRect(POSITION_DRAGON_FIRE_PHOTO_LEFT + DRAGON_FIRE_PHOTO_LENGTH, POSITION_DRAGON_FIRE_PHOTO_TOP, 2 * DRAGON_FIRE_PHOTO_LENGTH - 3, DRAGON_FIRE_PHOTO_HIGH));
			fireSprite.setPosition(positionDragonX - DRAGON_FIRE_PHOTO_LENGTH * 2, positionDragonY + DISPLACENET_DRAGON_FIRE_ABOUT_DRAGON_BY_Y);
			window.draw(fireSprite);
		}
	}

	if (pointerDragonFire == 3)
	{
		if (DragonFireVector)
		{
			if (firstFirePhoto)
			{
				fireSprite.setTextureRect(IntRect(POSITION_DRAGON_FIRE_PHOTO_LEFT + 6 * DRAGON_FIRE_PHOTO_LENGTH - 3, POSITION_DRAGON_FIRE_PHOTO_TOP, -3 * DRAGON_FIRE_PHOTO_LENGTH + 4, DRAGON_FIRE_PHOTO_HIGH));
			}
			else
			{
				fireSprite.setTextureRect(IntRect(POSITION_DRAGON_FIRE_PHOTO_LEFT + 9 * DRAGON_FIRE_PHOTO_LENGTH - 3, POSITION_DRAGON_FIRE_PHOTO_TOP, -3 * DRAGON_FIRE_PHOTO_LENGTH + 4, DRAGON_FIRE_PHOTO_HIGH));
			}

			firstFirePhoto = ((int)(timerDragonStay - THIRD_FIRE_TIMER) / CHANGE_FIRE_PHOTO_SPEED) % 2;

			fireSprite.setPosition(positionDragonX + DRAGON_PHOTO_LENGTH, positionDragonY + DISPLACENET_DRAGON_FIRE_ABOUT_DRAGON_BY_Y);
			window.draw(fireSprite);
		}
		else
		{
			if (firstFirePhoto)
			{
				fireSprite.setTextureRect(IntRect(POSITION_DRAGON_FIRE_PHOTO_LEFT + 3 * DRAGON_FIRE_PHOTO_LENGTH - 3, POSITION_DRAGON_FIRE_PHOTO_TOP, 3 * DRAGON_FIRE_PHOTO_LENGTH - 4, DRAGON_FIRE_PHOTO_HIGH));
			}
			else
			{
				fireSprite.setTextureRect(IntRect(POSITION_DRAGON_FIRE_PHOTO_LEFT + 6 * DRAGON_FIRE_PHOTO_LENGTH - 3, POSITION_DRAGON_FIRE_PHOTO_TOP, 3 * DRAGON_FIRE_PHOTO_LENGTH - 4, DRAGON_FIRE_PHOTO_HIGH));
			}

			firstFirePhoto = ((int)(timerDragonStay - THIRD_FIRE_TIMER) / CHANGE_FIRE_PHOTO_SPEED) % 2;

			fireSprite.setPosition(positionDragonX - 3 * DRAGON_FIRE_PHOTO_LENGTH, positionDragonY + DISPLACENET_DRAGON_FIRE_ABOUT_DRAGON_BY_Y);
			window.draw(fireSprite);
		}
	}

	if (pointerDragonFire == 4)
	{
		if (DragonFireVector)
		{
			fireSprite.setTextureRect(IntRect(POSITION_DRAGON_FIRE_PHOTO_LEFT + 11 * DRAGON_FIRE_PHOTO_LENGTH - 5, POSITION_DRAGON_FIRE_PHOTO_TOP, -2 * DRAGON_FIRE_PHOTO_LENGTH + 3, DRAGON_FIRE_PHOTO_HIGH));
			fireSprite.setPosition(positionDragonX + DRAGON_PHOTO_LENGTH + ONE_FIRE_DISPLACEMENT, positionDragonY + DISPLACENET_DRAGON_FIRE_ABOUT_DRAGON_BY_Y);
			window.draw(fireSprite);
		}
		else
		{
			fireSprite.setTextureRect(IntRect(POSITION_DRAGON_FIRE_PHOTO_LEFT + 9 * DRAGON_FIRE_PHOTO_LENGTH - 5, POSITION_DRAGON_FIRE_PHOTO_TOP, 2 * DRAGON_FIRE_PHOTO_LENGTH - 3, DRAGON_FIRE_PHOTO_HIGH));
			fireSprite.setPosition(positionDragonX - 2 * DRAGON_FIRE_PHOTO_LENGTH - ONE_FIRE_DISPLACEMENT, positionDragonY + DISPLACENET_DRAGON_FIRE_ABOUT_DRAGON_BY_Y);
			window.draw(fireSprite);
		}
	}

	if (pointerDragonFire == 5)
	{
		if (DragonFireVector)
		{
			fireSprite.setTextureRect(IntRect(POSITION_DRAGON_FIRE_PHOTO_LEFT + 12 * DRAGON_FIRE_PHOTO_LENGTH - 6, POSITION_DRAGON_FIRE_PHOTO_TOP, -DRAGON_FIRE_PHOTO_LENGTH + 2, DRAGON_FIRE_PHOTO_HIGH));
			fireSprite.setPosition(positionDragonX + DRAGON_PHOTO_LENGTH + TWO_FIRE_DISPLACEMENT, positionDragonY + DISPLACENET_DRAGON_FIRE_ABOUT_DRAGON_BY_Y);
			window.draw(fireSprite);
		}
		else
		{
			fireSprite.setTextureRect(IntRect(POSITION_DRAGON_FIRE_PHOTO_LEFT + 11 * DRAGON_FIRE_PHOTO_LENGTH -6, POSITION_DRAGON_FIRE_PHOTO_TOP, DRAGON_FIRE_PHOTO_LENGTH - 2, DRAGON_FIRE_PHOTO_HIGH));
			fireSprite.setPosition(positionDragonX - DRAGON_FIRE_PHOTO_LENGTH - TWO_FIRE_DISPLACEMENT, positionDragonY + DISPLACENET_DRAGON_FIRE_ABOUT_DRAGON_BY_Y);
			window.draw(fireSprite);
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

bool Under_Level_1_2::switchEvent(Event event, RenderWindow & window, Music & music)
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
		}else
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

	/// if LMD pressed ans not pause - check kick, if this kick is final - return true
	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && !pause)
	{
		if (!pause && checkKick(window))
		{
			return 1;
		}

		AliceKick = 1;
	}

	return 0;
}

void Under_Level_1_2::checkTime(RenderWindow & window)
{
	/*
	* function of checking time
	*/

	/// if too much time has passed - restart timer, move objects and draw new picture on screen
	if (myClock.getElapsedTime().asMilliseconds() > MILLI_SECOND_FOR_ACTION)
	{
		timer = myClock.restart().asMilliseconds();
		moveObjects(window, timer);
		drawPicture(window);
	}

	return;
}

bool Under_Level_1_2::checkKick(RenderWindow & window)
{
	/*
	* function of checking Alice kick
	*/

	/// if Alice is near Dragon
	if ((round(positionAliceX) == round(positionDragonX) - ALICE_PHOTO_LENGTH ||
		round(positionAliceX) == round(positionDragonX) + DRAGON_PHOTO_LENGTH) &&
		(round(positionAliceY) >= round(positionDragonY) - FIRST_STRANGE_CONST &&
			round(positionAliceY) <= round(positionDragonY) + SECOND_STRANGE_CONST))
	{
		/// if it doesn`t double click - subtract Dragons` HP
		if (!AliceKick)
		{
			DragonSprite.setColor(Color::Red);
			dragonHP--;
		}

		/// if it is final cick - return true
		if (dragonHP == 0)
		{
			return 1;
		}

	}

	return 0;
}

void Under_Level_1_2::game(RenderWindow & window, Music & music)
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
				return;
			}
		}

		/// check time
		checkTime(window);
	}

	return;
}

Under_Level_1_2::Under_Level_1_2()
{
}


Under_Level_1_2::~Under_Level_1_2()
{
}
