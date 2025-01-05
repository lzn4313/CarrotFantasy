#ifndef __Total_Data_H__
#define __Total_Data_H__

#include "cocos2d.h"

class TotalData
{
private:
	int monster_total;//击杀怪物总数
	int boss_total;//击杀boss总数
	int barrier_total;//摧毁障碍总数
public:
	TotalData();
	void resetData();
	int getTotalMonster();
	void setTotalMonster(int TotalNum);
	int getTotalBoss();
	void setTotalBoss(int TotalNum);
	int getTotalBarrier();
	void setTotalBarrier(int TotalNum);
};
#endif // __Total_Data_H__
