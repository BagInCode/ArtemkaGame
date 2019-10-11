#include "Under_Level_2_1.h"

void Under_Level_2_1::makeSpries()
{
	Vector2f w(10, 10);
	ball.setSize(w);
	ball.setFillColor(Color::Green);

	Vector2f v(100, 5);
	plank.setSize(v);

	Vector2f u(30, 30);
	target.setSize(u);
	target.setOutlineThickness(1);
	target.setOutlineColor(Color::Black);

	return;
}

void Under_Level_2_1::drawPicture(RenderWindow & window)
{
	window.clear();

	for (int i = 0; i < FIELD_HIGH_ARKANOID; i++)
	{
		for (int j = 0; j < FIELD_LENGTH_ARKANOID; j++)
		{
			if (!used[i][j] && FIELD[i][j] > 0)
			{
				target.setPosition(FIELD_DISPLACEMENT_ARKANOID_LEFT + j * 2 * TARGET_RADIUS, FIELD_DISPLACEMENT_ARKANOID_TOP + i * 2 * TARGET_RADIUS);
				
				if (FIELD[i][j] == 1)
				{
					target.setFillColor(Color::Red);
				}
				if (FIELD[i][j] == 2)
				{
					target.setFillColor(Color::Blue);
				}
				if (FIELD[i][j] == 3)
				{
					target.setFillColor(Color::Yellow);
				}
				
				window.draw(target);
			}
		}
	}

	plank.setPosition(plankPositionX, plankPositionY);
	window.draw(plank);

	ball.setPosition(positionBallX, positionBallY);
	window.draw(ball);

	if (pause)
	{
		window.draw(pauseText);
	}

	window.display();
}

void Under_Level_2_1::switchEvent(Event & event, RenderWindow & window, Music & music)
{
	/*
	* function of switching event type
	*/

	/// if window is close - close
	if (event.type == Event::Closed)
	{
		window.close();
	}

	/// if window lost focus - make pausa
	if (event.type == Event::LostFocus)
	{
		pause = 1;
		makePause(music);
	}

	/// if Esc presseg - chenge pausa value
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

	if(event.type == Event::KeyPressed && !start)
	{
		start = 1;
	}

	/// if key D pressed - add to AliceVector one if key D has not already pressed
	if (event.type == Event::KeyPressed && event.key.code == Keyboard::D && !pause && start)
	{
		plankVector += (!keyDPressed);
		keyDPressed = 1;
	}

	/// if key A released - add to AliceVector one if key A has not already released
	if (event.type == Event::KeyReleased && event.key.code == Keyboard::A && !pause && start)
	{
		plankVector += keyAPressed;
		keyAPressed = 0;
	}

	/// if key A pressed - subtract from AliceVector one if key A has not already released
	if (event.type == Event::KeyPressed && event.key.code == Keyboard::A && !pause && start)
	{
		plankVector -= (!keyAPressed);
		keyAPressed = 1;
	}

	/// if key D released - subtract from AliceVector one if key D has not already released
	if (event.type == Event::KeyReleased && event.key.code == Keyboard::D && !pause && start)
	{
		plankVector -= keyDPressed;
		keyDPressed = 0;
	}

	return;
}

void Under_Level_2_1::makePause(Music & music)
{
	pause = 1;
	music.pause();

	return;
}

bool Under_Level_2_1::checkTime(RenderWindow & window)
{
	/*
	* function of checking time
	*/

	/// if too much time has passed
	if (myClock.getElapsedTime().asMilliseconds() > MILLI_SECOND_FOR_ACTION / 5)
	{
		/// restart timer
		double timer = myClock.restart().asMilliseconds();

		/// move
		moveObjects(timer, window);

		/// draw new picture
		drawPicture(window);
	}

	return 0;
}
void Under_Level_2_1::makePauseTextTTC()
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

	return;
}

void Under_Level_2_1::restart(RenderWindow & window)
{
	/*
	* function of restart underlevel;
	*/

	myClock.restart();

	/// show red screen
	while (myClock.getElapsedTime().asSeconds() < TIME_LOOSE_WAITING)
	{
		window.clear(Color::Red);
		window.display();
	}

	start = 0;
	positionBallX = 645;
	positionBallY = 590;
	speed = 2;
	ballVectorX = 0;
	ballVectorY = -1;
	plankPositionX = 600;
	plankPositionY = 600;
	plankVector = 0;
	keyAPressed = 0;
	keyDPressed = 0;

	countLives--;

	if (countLives == 0)
	{
		countLives = 2;

		for (int i = 0; i < FIELD_HIGH_ARKANOID; i++)
		{
			for (int j = 0; j < FIELD_LENGTH_ARKANOID; j++)
			{
				used[i][j] = 0;
			}
		}

		countTargets = 95;
	}
	
	myClock.restart();

	return;
}

void Under_Level_2_1::moveObjects(double timer, RenderWindow & window)
{
	if (pause)
	{
		return;
	}

	movePlank(timer);
	moveBall(timer);

	checkIntersect(window);

	return;
}

void Under_Level_2_1::moveBall(double timer)
{
	positionBallX += ballVectorX * timer / ALICE_HORIZONTAL_SPEED * speed;
	positionBallY += ballVectorY * timer / ALICE_HORIZONTAL_SPEED * speed;

	return;
}

void Under_Level_2_1::movePlank(double timer)
{
	plankPositionX += timer * plankVector / ALICE_HORIZONTAL_SPEED * speed;
	
	plankPositionX = max(plankPositionX, double(0));
	plankPositionX = min(plankPositionX, double(WINDOW_LENGTH - 100));

	return;
}

void Under_Level_2_1::checkIntersect(RenderWindow & window)
{
	if (positionBallY > plankPositionY + 2 * BALL_RADIUS + 1)
	{
		restart(window);

		return;
	}

	if (positionBallX < 0 || positionBallX > WINDOW_LENGTH - 2 * BALL_RADIUS)
	{
		ballVectorX *= -1;

		positionBallX = max(positionBallX, 0.);
		positionBallX = min(positionBallX, WINDOW_LENGTH - 2. * BALL_RADIUS);
	}

	if (positionBallY < 0)
	{
		ballVectorY *= -1;

		positionBallY = 0;
	}

	if (positionBallY > plankPositionY - 2 * BALL_RADIUS - 2 && positionBallX > plankPositionX - 2 * BALL_RADIUS && positionBallX < plankPositionX + 100 && ballVectorY > 0)
	{
		double angle = (100 - (positionBallX - plankPositionX))/100;

		if (angle < 1. / 6)
		{
			angle = 1. / 6;
		}
		if (angle > 5. / 6)
		{
			angle = 5. / 6;
		}

		angle *= pi;

		ballVectorY = -sin(angle);
		ballVectorX = cos(angle);
	}

	for (int i = 0; i < FIELD_HIGH_ARKANOID; i++)
	{
		for (int j = 0; j < FIELD_LENGTH_ARKANOID; j++)
		{
			if (used[i][j] || FIELD[i][j] == 0)
			{
				continue;
			}

			double _left = max(positionBallX, FIELD_DISPLACEMENT_ARKANOID_LEFT + j * 2. * TARGET_RADIUS);
			double _right = min(positionBallX + 10, FIELD_DISPLACEMENT_ARKANOID_LEFT + (j + 1) * 2. * TARGET_RADIUS);
			double _up = max(positionBallY, FIELD_DISPLACEMENT_ARKANOID_TOP + i * 2. * TARGET_RADIUS);
			double _down = min(positionBallY + 10, FIELD_DISPLACEMENT_ARKANOID_TOP + (i + 1) * 2. * TARGET_RADIUS);

			if (_down < _up || _left > _right)
			{
				continue;
			}

			used[i][j] = 1;
			countTargets--;

			if (FIELD[i][j] == 2)
			{
				speed *= 1.1;
			}
			if (FIELD[i][j] == 3)
			{
				speed /= 1.1;
			}

			if (_down - _up > _right - _left)
			{
				if ((positionBallX < FIELD_DISPLACEMENT_ARKANOID_LEFT + j * 2. * TARGET_RADIUS && ballVectorX > 0) ||
					(positionBallX > FIELD_DISPLACEMENT_ARKANOID_LEFT + j * 2. * TARGET_RADIUS && ballVectorX < 0))
				{
					ballVectorX *= -1;
				}
			}
			else
			{
				if((positionBallY > FIELD_DISPLACEMENT_ARKANOID_TOP + i * 2. * TARGET_RADIUS && ballVectorY < 0)||
				   (positionBallY < FIELD_DISPLACEMENT_ARKANOID_TOP + i * 2. * TARGET_RADIUS && ballVectorY > 0))
				{
					ballVectorY *= -1;
				}
			}
		}
	}
}

void Under_Level_2_1::game(RenderWindow & window, Music & music)
{
	/*
	* main function of class
	*/

	/// load pictures
	makeSpries();

	/// make pause text TTC
	makePauseTextTTC();

	Event event;

	/// restart timer
	myClock.restart();

	/// while window is not closed
	while (window.isOpen())
	{
		/// if there is some events
		if (window.pollEvent(event))
		{
			/// switch event
			switchEvent(event, window, music);
		}

		/// check time
		checkTime(window);

		if (countTargets <= 0)
		{
			return;
		}
	}

	return;
}

Under_Level_2_1::Under_Level_2_1()
{
}


Under_Level_2_1::~Under_Level_2_1()
{
}
