#include "cocos2d.h"
#include"Game/GameScene.h"
#include"Game/enemy.h"
#include"Game/EnemyMoniter.h"
#include<vector>
#include<algorithm>
#include <iostream>
#include <cstdio>
#include<string>
#include<format>
#include "Facade.h"


using namespace std;
USING_NS_CC;

bool EnemyMoniter::init() {
	if (!Layer::init()) {
		return false;
	}
	return true;
}

void EnemyMoniter::setLevel(int level_selection) {
	Facade::getInstance()->getLevelData()->clear();
	vector<int>waves;
	string path = format("Level/enemy_{}.txt",level_selection);
	path = FileUtils::getInstance()->fullPathForFilename(path);
	auto file = fopen(path.c_str(), "r");
	int a, b, c,d,e,f,g,h,i,j;
	fscanf(file, "%d %d", &a, &b);
	start_position={ a,b };
	fscanf(file, "%d %d",&current_waves,&max_waves);
	for (a = 0; a < max_waves; a++) {
		fscanf(file, "%d", &b);
		for (int j = 0; j < b; j++) {
			fscanf(file, "%d", &c);
			waves.push_back(c);
		}
		monster_data.push_back(waves);
		waves.clear();
	}
	fscanf(file, "%d", &a);
	for (b = 0; b < a; b++) {
		fscanf(file, "%d", &c);
		switch (c) {
			case BARRIER_1:
			case BARRIER_2:
				fscanf(file, "%d %d", &d, &e);
				barrier_appear(c, { d,e });
				break;
			case BARRIER_3:
			case BARRIER_4:
				fscanf(file, "%d %d %d %d", &d, &e, &f, &g);
				barrier_appear(c, { d,e }, { f,g });
				break;
			case BARRIER_5:
			case BARRIER_6:
				fscanf(file, "%d %d %d %d %d %d", &d, &e, &f, &g, &h, &i);
				barrier_appear(c, { d,e }, { f,g }, { h,i });
				break;
			default:
				break;
		}
	}
	fclose(file);
}

void EnemyMoniter::monster_appear(int Type) {

	auto enemy = Enemy::createSprite();
	static_cast<Enemy*>(enemy)->setType(Type);
	vec2 start = trans_ij_to_xy(start_position);
	enemy->setPosition(Vec2(start.x, start.y));
	this->addChild(enemy);
	monster.push_back(static_cast<Enemy*>(enemy));

	if (Type < 3) {
		auto effect = Sprite::create("/EnemyCreate/Items02-hd_0.PNG");
		effect->setPosition(Vec2(start.x, start.y));
		this->addChild(effect);
		effect->runAction(Sequence::create(ScaleTo::create(0.2, 3), CallFunc::create([effect]() {effect->removeFromParent(); }), nullptr));
	}
}

void EnemyMoniter::barrier_appear(int Type, pos position) {
	vec2 vec;
	auto barrier_1 = Enemy::createSprite();
	static_cast<Enemy*>(barrier_1)->setType(Type);
	static_cast<Enemy*>(barrier_1)->set_position(position);
	vec = trans_ij_to_xy(position);
	barrier_1->setPosition(Vec2(vec.x, vec.y));
	this->addChild(barrier_1);
	barrier.push_back(static_cast<Enemy*>(barrier_1));
	Facade::getInstance()->setGameMap(position.i,position.j,1);
}

void EnemyMoniter::barrier_appear(int Type, pos position_l,pos position_r) {
	vec2 vec_l, vec_r, vec;
	auto barrier_1 = Enemy::createSprite();
	static_cast<Enemy*>(barrier_1)->setType(Type);
	static_cast<Enemy*>(barrier_1)->set_position(position_l);
	vec_l = trans_ij_to_xy(position_l);
	vec_r = trans_ij_to_xy(position_r);
	vec = { (vec_l.x + vec_r.x) / 2,(vec_l.y + vec_r.y) / 2 };
	barrier_1->setPosition(Vec2(vec.x, vec.y));
	this->addChild(barrier_1);
	barrier.push_back(static_cast<Enemy*>(barrier_1));
	Facade::getInstance()->setGameMap(position_l.i, position_l.j, 1);
	Facade::getInstance()->setGameMap(position_r.i, position_r.j, 1);
}

void EnemyMoniter::barrier_appear(int Type, pos position_l, pos position_r,pos position_u) {
	vec2 vec_l, vec_r,vec_u, vec;
	auto barrier_1 = Enemy::createSprite();
	static_cast<Enemy*>(barrier_1)->setType(Type);
	static_cast<Enemy*>(barrier_1)->set_position(position_l);
	vec_l = trans_ij_to_xy(position_l);
	vec_r = trans_ij_to_xy(position_r);
	vec_u = trans_ij_to_xy(position_u);
	vec = { (vec_l.x + vec_r.x) / 2,(vec_l.y + vec_u.y) / 2 };
	barrier_1->setPosition(Vec2(vec.x, vec.y));
	this->addChild(barrier_1);
    barrier.push_back(dynamic_cast<Enemy*>(barrier_1));
	Facade::getInstance()->setGameMap(position_l.i, position_l.j, 1);
	Facade::getInstance()->setGameMap(position_r.i, position_r.j, 1);
	Facade::getInstance()->setGameMap(position_u.i, position_u.j, 1);
	Facade::getInstance()->setGameMap(position_u.i, position_r.j, 1);
}

void EnemyMoniter::start() {

	auto create_monster = CallFunc::create([=]() {this->scheduleUpdate(); });

	this->runAction(Sequence::create(DelayTime::create(3), create_monster, nullptr));
}

void EnemyMoniter::update(float dt) {
	static float time = 1;
	static float clear_time = 0;
	static int n = 0;
	static int flag = 0;
	if (Facade::getInstance()->getGameController()->getPause() == 0) {
		if (flag == 0) {
			if (monster.size() == 0 && clear_time >= 2) {
				flag = 1;
				clear_time = 0;
				Facade::getInstance()->getLevelData()->setGameWaves(Facade::getInstance()->getLevelData()->getGameWaves()+1);
			}
		}

		if (flag == 1 && current_waves <= max_waves) {
			if (n == 0) {
				monster_appear(monster_data[current_waves - 1][n]);
				n++;
				time = 0;
			}
			else if (time >= 1) {
				monster_appear(monster_data[current_waves - 1][n]);
				n++;
				time = 0;
			}
			if (n == monster_data[current_waves - 1].size()) {
				flag = 0;
				n = 0;
				current_waves += 1;
				if (current_waves == max_waves + 1) {
					Facade::getInstance()->getGameController()->setAllClear(1);
				}
			}
		}
		if ( monster.size() == 0 && n == 0 && flag == 0) {
			clear_time += dt * (Facade::getInstance()->getGameController()->getSpeedUp() + 1);
		}
		time += dt * (Facade::getInstance()->getGameController()->getSpeedUp() + 1);
	}
}

