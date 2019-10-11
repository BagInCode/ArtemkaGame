#include "Level1.h"

void Level1::game(RenderWindow & window, Music & music)
{
	/*
	* main function of class
	*/

	/// play fisrt cut scene
	Cut_Scene_1_1_Object.play(window, music);

	/// play first underlevel
	Under_Level_1_1_Object.game(window, music);

	/// play second cut scene
	Cut_Scene_1_2_Object.play(window, music);

	/// ples second underlevel
	Under_Level_1_2_Object.game(window, music);

	/// play third cut scene
	Cut_Scene_1_3_Object.play(window, music);

	return;
}

Level1::Level1()
{
}

Level1::~Level1()
{
}
