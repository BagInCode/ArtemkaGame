#include "Under_Level_4_1.h"

void Under_Level_4_1::makeSound(Music & music)
{
	/*
	* function loading and start the sound
	*/

	music.openFromFile("Music\\PacMan.ogg");
	music.setLoop(1);

	music.play();

	return;
}

void Under_Level_4_1::makeSpries()
{
	/*
	* function of loading pictures if sprites
	*/

	texture.loadFromFile("textures\\PacMan.png");

	walls.setTexture(texture);
	walls.setTextureRect(IntRect(POSITION_WALL_X, POSITIOM_WALL_Y, FIELD_SPRITE_SIZE, FIELD_SPRITE_SIZE));

	return;
}

void Under_Level_4_1::drawPicture(RenderWindow & window)
{
	/*
	* function of drawing picture on screen
	*/

	/// clear window, set background color Black
	window.clear(Color::Black);

	/// draw FIELD
	for (int i = 0; i < FIELD_HEIGH; i++)
	{
		for (int j = 0; j < FIELD_LENGTH; j++)
		{
			/// if there is empty square - continue
			if (FIELD[i][j] == 0)
			{
				continue;
			}

			/// set position and draw sprite
			walls.setPosition(FIELD_DISPLACEMENT_LEFT + j * FIELD_SPRITE_SIZE, FIELD_DISPLACEMENT_TOP + i * FIELD_SPRITE_SIZE);
			window.draw(walls);
		}
	}

	/// draw eatme
	for (int i = 0; i < COUNT_EATME; i++)
	{
		if (!usedEatMe[i])
		{
			eatMe.setPosition(positionsEstMe[i].first * FIELD_SPRITE_SIZE + FIELD_DISPLACEMENT_LEFT, positionsEstMe[i].second * FIELD_SPRITE_SIZE + FIELD_DISPLACEMENT_TOP);
			window.draw(eatMe);
		}
	}

	/// draw pacman
	pacman.draw(window);

	/// draw enemy
	for (int i = 0; i < COUNT_ENEMY; i++)
	{
		enemy[i].draw(window);
	}

	/// if pausa - draw pausa text
	if (pause)
	{
		window.draw(pauseText);
	}

	/// draw text
	window.draw(text);

	window.display();

	return;
}

void Under_Level_4_1::switchEvent(Event & event, RenderWindow & window, Music & music)
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

	/// if w a s d pressed - set new speed vector
	if (event.type == Event::KeyPressed && event.key.code == Keyboard::W)
	{
		pacman.setSpeedVector(0, -1);
	}

	if (event.type == Event::KeyPressed && event.key.code == Keyboard::A)
	{
		pacman.setSpeedVector(-1, 0);
	}

	if (event.type == Event::KeyPressed && event.key.code == Keyboard::S)
	{
		pacman.setSpeedVector(0, 1);
	}

	if (event.type == Event::KeyPressed && event.key.code == Keyboard::D)
	{
		pacman.setSpeedVector(1, 0);
	}

	return;
}

void Under_Level_4_1::makePause(Music & music)
{
	/*
	* function of stoping moving
	*/

	music.pause();
	pause = 1;

	return;
}

bool Under_Level_4_1::checkTime(RenderWindow & window)
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
		if (move(timer, window))
		{
			return 1;
		}

		/// draw new picture
		drawPicture(window);
	}

	return 0;
}

bool Under_Level_4_1::move(double timer, RenderWindow & window)
{
	/*
	* function of moving objects on screen
	*/

	/// if game on pausa - goodbye
	if (pause)
	{
		return 0;
	}

	/// move enemies
	enemy[0].move(timer);
	enemy[1].move(timer);
	enemy[2].move(timer);
	enemy[3].move(timer);

	/// pacman move
	pacman.move(timer);

	/// check eatme
	checkEatMe();

	/// check intersect
	if (checkIntesect(window))
	{
		return 1;
	}

	return 0;
}

void Under_Level_4_1::createEnemies()
{
	/*
	* function of initialization enemies
	*/

	enemy[0].initialization(0, 6, 7);
	enemy[1].initialization(1, 11, 12);
	enemy[2].initialization(2, 11, 7);
	enemy[3].initialization(3, 6, 12);

	return;
}

void Under_Level_4_1::initializationEatMe()
{
	/*
	* function of initialization eatme
	*/

	/// set picture
	eatMe.setTexture(texture);
	eatMe.setTextureRect(IntRect(90, 120, FIELD_SPRITE_SIZE, FIELD_SPRITE_SIZE));

	/// set position
	positionsEstMe[0] = { 1, 2 }; usedEatMe[0] = 0;
	positionsEstMe[1] = { 17, 2 }; usedEatMe[1] = 0;
	positionsEstMe[2] = { 1, 15 }; usedEatMe[2] = 0;
	positionsEstMe[3] = { 17, 15 }; usedEatMe[3] = 0;

	return;
}

void Under_Level_4_1::makePauseTextTTC()
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

void Under_Level_4_1::restart(RenderWindow & window)
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

	initializationEatMe();
	pacman.initialization(9, 3);
	createEnemies();
	cntKill = 0;
	setString();

	myClock.restart();

	return;
}

void Under_Level_4_1::checkEatMe()
{
	/*
	* function of checking eatMe intersection with pacman
	*/

	/// fixed current position
	int currentPacManX = pacman.getPosition().first / FIELD_SPRITE_SIZE;
	int currentPacManY = pacman.getPosition().second / FIELD_SPRITE_SIZE;

	/// check intersec
	for (int i = 0; i < COUNT_EATME; i++)
	{
		/// if intersect is true
		if (currentPacManX == positionsEstMe[i].first && currentPacManY == positionsEstMe[i].second && !usedEatMe[i])
		{
			/// use this eatme
			usedEatMe[i] = 1;

			/// make enemies sceared
			for (int j = 0; j < COUNT_ENEMY; j++)
			{
				enemy[j].makeSceared();
			}
		}
	}

	return;
}

bool Under_Level_4_1::checkIntesect(RenderWindow & window)
{
	/*
	* function of checking intersection pacman with ghosts
	*/

	/// fixed current position of pacman
	int currentPacManX = pacman.getPosition().first / FIELD_SPRITE_SIZE;
	int currentPacManY = pacman.getPosition().second / FIELD_SPRITE_SIZE;

	for (int i = 0; i < COUNT_ENEMY; i++)
	{
		/// fixed cerrent postion of enemy
		int currentEnemyX = enemy[i].getPosition().first / FIELD_SPRITE_SIZE;
		int currentEnemyY = enemy[i].getPosition().second / FIELD_SPRITE_SIZE;

		/// if pacman in one square with enemy
		if (currentEnemyX == currentPacManX && currentEnemyY == currentPacManY)
		{
			/// if enemy is sceared - kill him
			if (enemy[i].getSceared())
			{
				cntKill++;

				setString();

				if (cntKill == COUNT_KILL_FOR_WIN)
				{
					return 1;
				}

				enemy[i].initialization(i, 9, 7);
			}
			else
			{
				/// we died - restart
				restart(window);
			}
		}
	}

	return 0;
}

void Under_Level_4_1::makeTextTTC()
{
	/*
	* function of making text TTC
	*/

	font.loadFromFile("Roboto-Regular.ttf");

	text.setFont(font);
	text.setCharacterSize(STANDART_TEXT_SIZE * 2);
	text.setPosition(FIELD_DISPLACEMENT_LEFT, FIELD_DISPLACEMENT_TOP + FIELD_HEIGH * FIELD_SPRITE_SIZE);
	text.setString("Kills: 0/10");
	text.setFillColor(Color::White);
	text.setStyle(Text::Bold);

	return;
}

void Under_Level_4_1::setString()
{
	/*
	* function of setting text string
	*/

	string textString = "Kills: ";
	textString += char(cntKill + '0');
	textString += "/10";

	text.setString(textString);

	return;
}

void Under_Level_4_1::game(RenderWindow & window, Music & music)
{
	/*
	* main function of class
	*/

	/// make sound
	makeSound(music);

	/// make random more randomly
	srand(time(0));

	/// load pictures
	makeSpries();

	/// make pause text TTC
	makePauseTextTTC();

	/// initialization of enemies
	createEnemies();

	/// init eatme
	initializationEatMe();

	/// initialization of pacman
	pacman.initialization(9, 3);

	Event event;

	/// restart timer
	myClock.restart();

	/// make text TTC
	makeTextTTC();

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
		if (checkTime(window))
		{
			return;
		}
	}

	return;
}

Under_Level_4_1::Under_Level_4_1()
{
}

Under_Level_4_1::~Under_Level_4_1()
{
}
