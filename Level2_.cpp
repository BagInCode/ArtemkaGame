#include "Level2_.h"



Level2_::Level2_()
{
}


Level2_::~Level2_()
{
}

void Level2_::game(RenderWindow & window, Music & music)
{
	Cut_Scene_2_1_Object.play(window, music);
	Under_Level_2_1_Object.game(window, music);
	Cut_Scene_2_2_Object.play(window, music);

	return;
}
