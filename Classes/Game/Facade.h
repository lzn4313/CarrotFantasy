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
#include "OptionController.h"

class Facade {
private:
	Shop* shop;

	GameController* gamecontroller;

	GameMenu* gameMenu;

	TotalData* totalData;

	static  Facade* facade;

	Facade();

	GameMap* gameMap;

	LevelData* levelData;

	GameScene* gameScene;
public:

	static Facade* getInstance();

	void clear();
	void startGame();
	void pause();
	void speedUp();
	void win();
	void lose();
	void buyTower(int tag, int money);
	void sellTower(Tower* tower);

	Shop* getShop();

	GameController* getGameController();

	cocos2d::Layer* getGameMenu(int level);

    GameMap* getGameMap() {
		return gameMap;
	}

	TotalData* getTotalData();

	LevelData* getLevelData();
};
