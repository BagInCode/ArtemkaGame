#include "Level5.h"



Level5::Level5()
{
}


Level5::~Level5()
{
}


void Level5::game(RenderWindow & window, Music & music)
{
	Cut_Scene_5_1_Object.play(window, music);
	Cut_Scene_5_2_Object.play(window, music);
}
