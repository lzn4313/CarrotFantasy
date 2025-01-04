#pragma once
#include "cocos2d.h"
#include "GameScene.h"
#include "Tower.h"

class Facade {
private:

	//GameLevel* gameLevel;

	GameMenu* gameMenu;

	static  Facade* facade;

	Facade();

public:

	static Facade* getInstance();

	void clear();
};
