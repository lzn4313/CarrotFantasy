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
	gameMenu = nullptr;
}

Facade::Facade()
{
	gameMenu = nullptr;
	shop = new Shop();
	gamecontroller = new GameController();
}

Shop* Facade::getShop()
{
	return shop;
}

GameController* Facade::getGameController()
{
	return gamecontroller;
}
