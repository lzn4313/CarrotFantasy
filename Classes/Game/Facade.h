#pragma once
#include "cocos2d.h"
#include "GameScene.h"
#include "Tower.h"
#include "GameController.h"
#include "Shop.h"

class Facade {
private:

	//GameLevel* gameLevel;
	Shop* shop;

	GameController* gamecontroller;

	GameMenu* gameMenu;

	static  Facade* facade;

	Facade();

public:

	static Facade* getInstance();

	void clear();

	Shop* getShop();

	GameController* getGameController();
};
