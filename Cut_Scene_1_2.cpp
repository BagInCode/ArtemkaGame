#include "Cut_Scene_1_2.h"

void Cut_Scene_1_2::play(RenderWindow & window, Music & music)
{
	/*
	* main function of class
	*/

	/// play fisrt part
	Cut_Scene_1_2_1_Object.play(window, music);

	/// play second part
	Cut_Scene_1_2_2_Object.play(window, music);

	return;
}

Cut_Scene_1_2::Cut_Scene_1_2()
{
}

Cut_Scene_1_2::~Cut_Scene_1_2()
{
}
