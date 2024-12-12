#pragma once

void ExecuteScene();

enum SceneType
{
	title,
	game,
	clear,
	over
};

enum SceneStep
{
	init,
	update,
	teminate
};