#include "PacManClass.h"

void PacManClass::setSpeedVector(int newVectorX, int newVectorY)
{
	/*
	* function of setting speed vector
	*/

	nextVectorX = newVectorX;
	nextVectorY = newVectorY;

	return;
}

void PacManClass::setPosition(int newX, int newY)
{
	/*
	* function of setting position
	*/

	positionX = newX * FIELD_SPRITE_SIZE;
	positionY = newY * FIELD_SPRITE_SIZE;

	return;
}

void PacManClass::setPicture()
{
	/*
	* function of setting picture
	*/

	if (!openMouth)
	{
		sprite.setTextureRect(IntRect(POSITION_CLOSE_MOUTH_X, POSITIOM_CLOSE_MOUTH_Y, FIELD_SPRITE_SIZE, FIELD_SPRITE_SIZE));
	}
	else
	{
		if (vectorX == 1)
		{
			sprite.setTextureRect(IntRect(POSITION_OPEN_MOUTH_RIGHT_X, POSITION_OPEN_MOUTH_RIGHT_Y, FIELD_SPRITE_SIZE, FIELD_SPRITE_SIZE));
		}
		if (vectorX == -1)
		{
			sprite.setTextureRect(IntRect(POSITION_OPEN_MOUTH_RIGHT_X + FIELD_SPRITE_SIZE, POSITION_OPEN_MOUTH_RIGHT_Y, -FIELD_SPRITE_SIZE, FIELD_SPRITE_SIZE));
		}
		if (vectorY == -1)
		{
			sprite.setTextureRect(IntRect(POSITION_OPEN_MOUTH_UP_X, POSITION_OPEN_MOUTH_UP_Y, FIELD_SPRITE_SIZE, FIELD_SPRITE_SIZE));
		}
		if (vectorY == 1)
		{
			sprite.setTextureRect(IntRect(POSITION_OPEN_MOUTH_UP_X, POSITION_OPEN_MOUTH_UP_Y + FIELD_SPRITE_SIZE, FIELD_SPRITE_SIZE, -FIELD_SPRITE_SIZE));
		}
	}

	return;
}

void PacManClass::setTexture()
{
	/*
	* function of loading texture in sprite
	*/

	texture.loadFromFile("textures\\PacMan.png");
	sprite.setTexture(texture);

	return;
}

pair < int, int > PacManClass::getPosition()
{
	/*
	* function of getting position
	*/

	return { positionX, positionY };
}

pair < int, int > PacManClass::getSpeedVector()
{
	/*
	* function of getting speed vector
	*/

	return { vectorX, vectorY };
}

void PacManClass::checkMove()
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

void PacManClass::move(double timer)
{
	/*
	* function of moving
	*/

	/// calculate delt
	int was = int(timerMoving / PACMAN_SPEED);

	timerMoving += timer;
	timerPicture += timer;

	int is = int(timerMoving / PACMAN_SPEED);

	int delt = is - was;

	/// move
	positionX += vectorX * delt;
	positionY += vectorY * delt;

	/// check move
	checkMove();

	/// if stay in center of square - try turn
	if (positionX % FIELD_SPRITE_SIZE == 0 && positionY % FIELD_SPRITE_SIZE == 0)
	{
		checkTurn();
	}

	/// if current picture show too long - change  
	if (timerPicture > PACMAN_PHOTO)
	{
		openMouth = !openMouth;

		timerPicture = 0;

		setPicture();
	}

	return;
}

void PacManClass::checkTurn(bool zeroVal)
{
	/*
	* function of cheking turn
	*/

	/// if no turn - goodbye
	if (!nextVectorX && !nextVectorY && !zeroVal)
	{
		return;
	}

	/// fixed current position
	int currentX = round(double(positionX) / FIELD_SPRITE_SIZE);
	int currentY = round(double(positionY) / FIELD_SPRITE_SIZE);

	/// if turn if possible - turn
	if (FIELD[currentY + nextVectorY][currentX + nextVectorX] == 0)
	{
		vectorX = nextVectorX;
		vectorY = nextVectorY;

		nextVectorX = 0;
		nextVectorY = 0;
	}

	/// set picture
	setPicture();

	return;
}

void PacManClass::initialization(int positionX, int positionY)
{
	/*
	* function of initialization
	*/

	setPosition(positionX, positionY);
	setTexture();
	setSpeedVector(0, 0);
	checkTurn(1);

	return;
}

void PacManClass::draw(RenderWindow & window)
{
	/*
	* function of drawing picture in screen
	*/

	sprite.setPosition(positionX + FIELD_DISPLACEMENT_LEFT, positionY + FIELD_DISPLACEMENT_TOP);
	window.draw(sprite);

	return;
}

PacManClass::PacManClass()
{
}

PacManClass::~PacManClass()
{
}
