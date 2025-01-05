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
#include "EnemyMoniter.h"

class Facade {
private:
	Shop* shop;

	GameController* gamecontroller;

	GameMenu* gameMenu;

	TotalData* totalData;

	static  Facade* facade;

	GameScene* gameScene;

	Facade();

	GameMap* gameMap;

	LevelData* levelData;

	GameScene* gameScene;
	LevelLayer* levelLayer;

	EnemyMoniter* enemyMoniter;
public:

	static Facade* getInstance();

	void clear();
	void startGame();
	void pause(GameController gamecontroller);
	void speedUp(GameController gamecontroller);
	void win();
	void lose();
	void buyTower(int tag, int money);
	void sellTower(Tower* tower);

	Shop* getShop();

	cocos2d::Scene* startGame(int);

	GameController* getGameController();

	GameMenu* getGameMenu(int level);

	TotalData* getTotalData();

	LevelData* getLevelData();

	void setCarrotPosition(int i, int j) { gameMap->setCarrotPosition({ i,j }); }
	pos getCarrotPosition() { gameMap->getCarrotPosition(); }

	void setTowerMap(int i, int j, Tower* tower) { gameMap->setTowerMap(i, j, tower); }
	Tower* getTowerMap(int i, int j) { return gameMap->getTowerMap(i, j); }

	void setGameMap(int i, int j, char p) { gameMap->setGameMap(i, j, p); }
	char getGameMap(int i, int j) { return gameMap->getGameMap(i, j); }

	void setLevelPath(int i, int j, char k) { gameMap->setLevelPath({ {i,j},k }); }
	const vector<LevelPath>& getLevelPath(int i, int j) { return gameMap->getLevelPath(); }
	void levelPathClear() { gameMap->levelPathClaer(); }

	const vector<Enemy*>& getMonster() { return enemyMoniter->getMonster(); }

	const vector<Enemy*>& getBarrier() { return enemyMoniter->getBarrier(); }
};
