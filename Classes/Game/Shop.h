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
	//��ʼ����Ǯ
	void resetMoney();
	//������Ϸ�ڽ�Ǯ
	void setGameMoney(int money);
	//���ص�ǰ�ؿ���Ǯ
	int getGameMoney();
	//����ȫ����õĽ�Ǯ
	int getTotalMoney();
	//�ı�ؿ���Ǯ
	void changeGameMoney(int money);
	//����һ���������
	Tower* getNewTower(int tag, int money);
	//������̨
	void updateTower(Tower*tower, int money);
	//������̨
	void sellTower(Tower* tower);

};
#endif // __Shop_H__