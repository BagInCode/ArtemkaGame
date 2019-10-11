#include "Level0.h"



Level0::Level0()
{
}


Level0::~Level0()
{
}


void Level0::game(RenderWindow & window, Music & music)
{
	Cut_Scene_0_1_Object.play(window, music);
	Cut_Scene_0_2_Object.play(window, music);
}
