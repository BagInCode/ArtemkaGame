#include "Level3.h"



Level3::Level3()
{
}


Level3::~Level3()
{
}

void Level3::game(RenderWindow & window, Music & music)
{
	Cut_Scene_3_1_Object.play(window, music);
	Under_Level_3_1_Object.game(window, music);
	Cut_Scene_3_2_Object.play(window, music);
	Under_Level_3_2_Object.game(window, music);

	return;
}