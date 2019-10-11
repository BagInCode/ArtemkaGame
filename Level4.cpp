#pragma once
#include "Level4.h"

void Level4::game(RenderWindow & window, Music & music)
{
	Cut_Scene_4_1_Object.play(window, music);
	Under_Level_4_1_Object.game(window, music);
	Cut_Scene_4_2_Object.play(window, music);
	
	return;
}

Level4::Level4()
{
}

Level4::~Level4()
{
}
