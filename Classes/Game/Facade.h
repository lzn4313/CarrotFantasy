#pragma once
#include "cocos2d.h"
#include "GameScene.h"
#include "Tower.h"
#include "GameController.h"
#include "Shop.h"
<<<<<<< Updated upstream
#include "LevelLayer.h"
#include "gameMap.h"
=======
#include "TotalData.h"
>>>>>>> Stashed changes

class Facade {
private:
	Shop* shop;

	GameController* gamecontroller;

<<<<<<< Updated upstream
	cocos2d::Layer* gameMenu;
=======
	TotalData* totalData;

	GameMenu* gameMenu;
>>>>>>> Stashed changes

	static  Facade* facade;

	Facade();

	GameMap* gameMap;


public:

	static Facade* getInstance();

	void clear();

	Shop* getShop();

	GameController* getGameController();

<<<<<<< Updated upstream
	cocos2d::Layer* getGameMenu(int level);

    GameMap* getGameMap() {
		return gameMap;
	}
=======
	TotalData* getTotalData();
>>>>>>> Stashed changes
};
