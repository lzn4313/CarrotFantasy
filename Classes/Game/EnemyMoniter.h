#pragma once
#include "cocos2d.h"
#include"Game/GameScene.h"
#include<vector>

using namespace std; 
USING_NS_CC;


class EnemyMoniter :public cocos2d::Layer
{
private:
	int current_waves;
	int max_waves;
	pos start_position;
	vector<vector<int>> monster_data;
	vector<Enemy*> monster;
	vector<Enemy*> barrier;
public:
	virtual bool init();
	static EnemyMoniter* create(int) {
		EnemyMoniter* pRet = new(std::nothrow) EnemyMoniter(); if (pRet && pRet->init()) {
			pRet->autorelease(); return pRet;
		}
		else {
			delete pRet; pRet = nullptr; return nullptr;
		}
	};
	virtual void update(float dt);

	void setLevel(int level_selection);
	void monster_appear(int Type);
	void barrier_appear(int Type, pos position);
	void barrier_appear(int Type, pos position_l, pos position_r);
	void barrier_appear(int Type, pos position_l, pos position_r, pos position_u);
	void start();
	const vector<Enemy*>& getMonster() { return monster; }
	const vector<Enemy*>& getBarrier() { return barrier; }
};
