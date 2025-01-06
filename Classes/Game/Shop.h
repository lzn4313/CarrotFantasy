#ifndef __Shop_H__
#define __Shop_H__

#include "cocos2d.h"
#include "Game/Tower.h"

class Shop
{
private:
	int gameMoney;
	int totalMoney;
public:
	Shop();
	//初始化金钱
	void resetMoney();
	//设置游戏内金钱
	void setGameMoney(int money);
	//返回当前关卡金钱
	int getGameMoney();
	//返会全部获得的金钱
	int getTotalMoney();
	//改变关卡金钱
	void changeGameMoney(int money);
	//返回一个买过的塔
	Tower* getNewTower(int tag, int money);
	//升级炮台
	void updateTower(Tower*tower, int money);
	//出售炮台
	void sellTower(Tower* tower);

};
#endif // __Shop_H__