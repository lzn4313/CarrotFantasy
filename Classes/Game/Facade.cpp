#include "Facade.h"

using namespace cocos2d;
using namespace std;
Facade* Facade::facade = nullptr;

Facade* Facade::getInstance()
{
	if (facade == nullptr) {
		facade=  new Facade();
		return facade;
	}
	else {
		return facade;
	}
}
void Facade::clear()
{
	this->gameMenu = nullptr;
	gameMap->clear();
}

Facade::Facade()
{
	this->gameMenu = nullptr;
	shop = new Shop();
	gamecontroller = new GameController();
}

Shop* Facade::getShop()
{
	return shop;
}

cocos2d::Scene* Facade::startGame(int level)  
{
	auto scene=GameScene::createScene()
}

GameController* Facade::getGameController()
{
	return gamecontroller;
}

Cer Facade::getGameMenu(int level)
{
	if(gameMenu ==nullptr)
		gameMenu = GameMenu::create();
	return gameMenu;
}
