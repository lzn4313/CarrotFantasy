#pragma once
#include "cocos2d.h"
#include "GameScene.h"
#include "Tower.h"
#include "GameController.h"
#include "Shop.h"
#include "LevelLayer.h"
#include "gameMap.h"
#include "TotalData.h"
#include "LevelData.h"

class Facade {
private:
	Shop* shop;

	GameController* gamecontroller;

	cocos2d::Layer* gameMenu;
	TotalData* totalData;

	static  Facade* facade;

	GameScene* gameScene;

	Facade();

	GameMap* gameMap;

	LevelData* levelData;


public:

	static Facade* getInstance();

	void clear();

	Shop* getShop();

	cocos2d::Scene* startGame(int);

	GameController* getGameController();

	GameMenu* getGameMenu(int level);

    GameMap* getGameMap() {
		return gameMap;
	}

	TotalData* getTotalData();

	LevelData* getLevelData();
};
