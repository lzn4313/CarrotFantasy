#pragma once
#include "cocos2d.h"
#include "GameScene.h"
#include "Tower.h"
#include "GameController.h"
#include "Shop.h"
#include "LevelLayer.h"
#include "gameMap.h"

class Facade {
private:
	Shop* shop;

	GameController* gamecontroller;

	cocos2d::Layer* gameMenu;

	static  Facade* facade;

	Facade();

	GameMap* gameMap;


public:

	static Facade* getInstance();

	void clear();

	Shop* getShop();

	GameController* getGameController();

	cocos2d::Layer* getGameMenu(int level);

    GameMap* getGameMap() {
		return gameMap;
	}
};
