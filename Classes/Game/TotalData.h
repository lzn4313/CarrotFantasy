#ifndef __Total_Data_H__
#define __Total_Data_H__

#include "cocos2d.h"

class TotalData
{
private:
	int monster_total;//��ɱ��������
	int boss_total;//��ɱboss����
	int barrier_total;//�ݻ��ϰ�����
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
