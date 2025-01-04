#include "Shop.h"
#include <vector>
USING_NS_CC;
using namespace cocos2d::ui;

Shop::Shop()
{
	resetMoney();
}

void Shop::resetMoney()
{
	totalMoney = 0;
	gameMoney = 0;
}
void Shop::setGameMoney(int money)
{
	gameMoney = money;
}
int Shop::getGameMoney()
{
	return gameMoney;
}

int Shop::getTotalMoney()
{
	return totalMoney;
}
//��Ǯ��Ǯ������
void Shop::changeGameMoney(int money)
{
	if (money >= 0) {
		gameMoney = gameMoney + money;
		totalMoney = totalMoney + money;
	}
	else
	{
		gameMoney = gameMoney + money;
	}
}
//������̨������Towerָ��
Tower* Shop::getNewTower(int tag,int money)
{
	Tower* a = new Tower;
	changeGameMoney(money*-1);
	return a;
}
//����Tower
void Shop::updateTower(Tower* tower, int money)
{
	//tower->up_level_tower();
	changeGameMoney(money * -1);
}
//����Tower,towerɾ�������ۼ�
void Shop::sellTower(Tower* tower, int money)
{
	//tower.delete();
	changeGameMoney(money);
}

