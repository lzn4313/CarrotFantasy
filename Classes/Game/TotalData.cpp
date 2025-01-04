#include "TotalData.h"

USING_NS_CC;

TotalData::TotalData()
{
	resetData();
}
void TotalData::resetData()
{
	monster_total = 0;
	boss_total = 0;
	barrier_total = 0;
}
int TotalData::getTotalMonster()
{
	return monster_total;
}
int TotalData::getTotalBoss()
{
	return boss_total;
}
int TotalData::getTotalBarrier()
{
	return barrier_total;
}
void TotalData::setTotalMonster(int TotalNum)
{
	monster_total = TotalNum;
}
void TotalData::setTotalBoss(int TotalNum)
{
	boss_total = TotalNum;
}
void TotalData::setTotalBarrier(int TotalNum)
{
	barrier_total = TotalNum;
}

