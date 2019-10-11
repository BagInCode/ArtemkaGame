#include "EnemyClass.h"

void EnemyClass::setTexture()
{
	/*
	* function of loading texture in sprite
	*/

	texture.loadFromFile("textures\\PacMan.png");
	sprite.setTexture(texture);

	return;
}

void EnemyClass::setSpeedVector(int newVectorX, int newVectorY)
{
	/*
	* function of setting speed vector
	*/

	vectorX = newVectorX;
	vectorY = newVectorY;

	return;
}

void EnemyClass::setPicture()
{
	/*
	* function of setting enemy picture
	*/

	if (vectorX == 1)
	{
		sprite.setTextureRect(IntRect(POSITION_LOOK_RIGHT, positionSpriteY, FIELD_SPRITE_SIZE, FIELD_SPRITE_SIZE));
	}

	if (vectorX == -1)
	{
		sprite.setTextureRect(IntRect(POSITION_LOOK_LEFT, positionSpriteY, FIELD_SPRITE_SIZE, FIELD_SPRITE_SIZE));
	}

	if (vectorY == 1)
	{
		sprite.setTextureRect(IntRect(POSITION_LOOK_DOWN, positionSpriteY, FIELD_SPRITE_SIZE, FIELD_SPRITE_SIZE));
	}

	if (vectorY == -1)
	{
		sprite.setTextureRect(IntRect(POSITION_LOOK_UP, positionSpriteY, FIELD_SPRITE_SIZE, FIELD_SPRITE_SIZE));
	}

	return;
}

void EnemyClass::setPosition(int newX, int newY)
{
	/*
	* function of setting position
	*/

	positionX = newX * FIELD_SPRITE_SIZE;
	positionY = newY * FIELD_SPRITE_SIZE;

	return;
}

void EnemyClass::setTurn()
{
	/*
	* function of setting turn
	*/

	/// fixed current position
	int currentX = (positionX / FIELD_SPRITE_SIZE);
	int currentY = (positionY / FIELD_SPRITE_SIZE);

	if (currentX == lastChangedX && currentY == lastChangedY)
	{
		return;
	}

	vector < pair < int, int > > mayBe;

	/// if you can go somewhere - try it
	if (FIELD[currentY][currentX - 1] == 0 &&  vectorX != 1)
	{
		mayBe.push_back({ -1, 0 });
	}

	if (FIELD[currentY][currentX + 1] == 0 &&  vectorX != -1)
	{
		mayBe.push_back({ 1, 0 });
	}

	if (FIELD[currentY - 1][currentX] == 0 &&  vectorY != 1)
	{
		mayBe.push_back({ 0, -1 });
	}

	if (FIELD[currentY + 1][currentX] == 0 &&  vectorY != -1)
	{
		mayBe.push_back({ 0, 1 });
	}

	/// chose one variant
	if (mayBe.size())
	{
		int chose = rand() % mayBe.size();

		vectorX = mayBe[chose].first;
		vectorY = mayBe[chose].second;

		lastChangedX = currentX;
		lastChangedY = currentY;

		if (!sceared)
		{
			setPicture();
		}
	}

	return;
}

void EnemyClass::setColor(int color)
{
	/*
	* function of setting color
	*/

	positionSpriteY = color * FIELD_SPRITE_SIZE;

	return;
}

void EnemyClass::setKill()
{
	/*
	* function of setting kill value
	*/

	kill = 1;

	return;
}

pair < int, int > EnemyClass::getPosition()
{
	/*
	* function of getting enemy position
	*/

	return { positionX, positionY };
}

pair < int, int > EnemyClass::getSpeedVector()
{
	/*
	* function of getting speed vector
	*/

	return { vectorX, vectorY };
}

bool EnemyClass::getKill()
{
	/*
	* function of getting kill status
	*/

	return kill;
}

bool EnemyClass::getSceared()
{
	/*
	* function of getting sceared
	*/

	return sceared;
}

void EnemyClass::checkMove()
{
	/*
	* function of ckecking moving
	*/

	/// fixed current position
	int currentX = (positionX / FIELD_SPRITE_SIZE) + (positionX % FIELD_SPRITE_SIZE > FIELD_SPRITE_SIZE / 2);
	int currentY = (positionY / FIELD_SPRITE_SIZE) + (positionY % FIELD_SPRITE_SIZE > FIELD_SPRITE_SIZE / 2);

	/// if pacman try to go on wall square - stop it
	if (FIELD[currentY - 1][currentX] == 1 && positionY < currentY*FIELD_SPRITE_SIZE)
	{
		positionY = currentY * FIELD_SPRITE_SIZE;
	}
	if (FIELD[currentY + 1][currentX] == 1 && positionY > currentY*FIELD_SPRITE_SIZE)
	{
		positionY = currentY * FIELD_SPRITE_SIZE;
	}
	if (FIELD[currentY][currentX - 1] == 1 && positionX < currentX*FIELD_SPRITE_SIZE)
	{
		positionX = currentX * FIELD_SPRITE_SIZE;
	}
	if (FIELD[currentY][currentX + 1] == 1 && positionX > currentX*FIELD_SPRITE_SIZE)
	{
		positionX = currentX * FIELD_SPRITE_SIZE;
	}

	return;
}

void EnemyClass::move(double timer)
{
	/*
	* function of moving;
	*/

	/// if enemy is diead - goodbye
	if (kill)
	{
		return;
	}

	/// calculate dela of position
	int was = int(timerMoving / PACMAN_SPEED);

	timerMoving += timer / speed;

	int is = int(timerMoving / PACMAN_SPEED);

	int delt = is - was;

	/// if sceared
	if (sceared)
	{
		/// increase timer os sceared
		timerScered += timer;

		/// set picture
		if (timerScered > FIRST_SCEARED_TIMER)
		{
			sprite.setTextureRect(IntRect(POSITION_SCEARED_WHITE_X, POSITION_SCEARED_WHITE_Y, FIELD_SPRITE_SIZE, FIELD_SPRITE_SIZE));
		}

		if (timerScered > SECOND_SCEARED_TIMER)
		{
			sprite.setTextureRect(IntRect(POSITION_SCEARED_BLUE_X, POSITION_SCEARED_BLUE_Y, FIELD_SPRITE_SIZE, FIELD_SPRITE_SIZE));
		}

		if (timerScered > THIRD_SCEARED_TIMER)
		{
			sprite.setTextureRect(IntRect(POSITION_SCEARED_WHITE_X, POSITION_SCEARED_WHITE_Y, FIELD_SPRITE_SIZE, FIELD_SPRITE_SIZE));
		}

		if (timerScered > FOURTH_SCEARED_TIMER)
		{
			sprite.setTextureRect(IntRect(POSITION_SCEARED_BLUE_X, POSITION_SCEARED_BLUE_Y, FIELD_SPRITE_SIZE, FIELD_SPRITE_SIZE));
		}

		/// if timer is over - make unsceared
		if (timerScered > MAX_TIMER_SCEARED)
		{
			makeUnsceared();
		}
	}

	/// don`t make timer so big
	if (timerMoving > ONE_SECOND)
	{
		timerMoving -= ONE_SECOND;
	}

	/// move
	positionX += vectorX * delt;
	positionY += vectorY * delt;

	/// check move
	checkMove();

	/// if enemyif center of square - try turn
	if (positionX % FIELD_SPRITE_SIZE == 0 &&
		positionY % FIELD_SPRITE_SIZE == 0)
	{
		setTurn();
	}

	return;
}

void EnemyClass::initialization(int color, int positionX, int positionY)
{
	/*
	* function of initialization enemy
	*/

	lastChangedX = 0;
	lastChangedY = 0;

	setTexture();
	setColor(color);
	setPosition(positionX, positionY);
	setTurn();
	makeUnsceared();

	return;
}

void EnemyClass::draw(RenderWindow & window)
{
	/*
	* function of drawing sprite
	*/

	/// if enemy is died - goodbye
	if (kill)
	{
		return;
	}

	/// draw enemy
	sprite.setPosition(FIELD_DISPLACEMENT_LEFT + positionX, FIELD_DISPLACEMENT_TOP + positionY);
	window.draw(sprite);

	return;
}

void EnemyClass::makeSceared()
{
	/*
	* function of making sceared
	*/

	sceared = 1;
	speed = 1.5;

	sprite.setTextureRect(IntRect(POSITION_SCEARED_BLUE_X, POSITION_SCEARED_BLUE_Y, FIELD_SPRITE_SIZE, FIELD_SPRITE_SIZE));

	return;
}

void EnemyClass::makeUnsceared()
{
	/*
	* function of making unsceared
	*/

	sceared = 0;
	speed = 1;

	timerScered = 0;

	setPicture();

	return;
}

EnemyClass::EnemyClass()
{
}

EnemyClass::~EnemyClass()
{
}
