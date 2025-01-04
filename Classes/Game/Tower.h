#include "cocos2d.h"
#include "Game/GameScene.h"
#include "Game/enemy.h"
using namespace std;

/*名称与标签对应*/
#define Tower_Bottle 1
#define Tower_Shit 2
#define Tower_Fan 3
#define Tower_Star 4

/*攻击效果与标签对应*/
#define None 0
#define Slow 1
#define Penetrate 2
#define Divide 3

#define Max_Level 3
#define TOWER_NUM 4

const int Tower_Value[4] = { 100,120,160,160 };
const float Tower_Attack[4] = { 50,20,60,80 };
const float Tower_Attack_Speed[4] = { 8,4,4,3 };

struct Tower_information {
	int name_tag;//记录名称标签
	int value;//记录当前价值
	float attack;//记录单次攻击力
	float attack_speed;//记录攻击速度
	float attack_range;//记录攻击范围
	int attack_special;//记录特殊攻击效果（穿透、减速、分裂等）
	int level;//记录等级

	Tower_information(int t = 0, int v = 0, float atk = 0, float atk_speed = 0, float atk_r = 1, int atk_special = 0, int L = 1)
		:name_tag(t), value(v), attack(atk), attack_speed(atk_speed), attack_range(atk_r), attack_special(atk_special), level(L)
	{}//构造函数

};

class Bullet :public cocos2d::Sprite {
protected:
	Enemy* Target = nullptr;
	Tower_body* Father = nullptr;
public:
	virtual bool init();
	virtual void update(float dt);//实时判断范围内是否有敌人，有则攻击
	//CREATE_FUNC(Bullet);
};

class Tower_body :public cocos2d::Sprite {
protected:
	Tower_information tower_information;
	float time = 0;//控制攻击间隔
public:
	//构造函数
	Tower_body(Tower_information tower_information) {
		this->tower_information = tower_information;
	}
	virtual bool init();
	virtual void update(float dt);//实时判断范围内是否有敌人，有则攻击
	Tower_information getInfo() { return tower_information; }
	void setInfo(Tower_information info) { this->tower_information = info; }
	bool is_in_range(Enemy* Target);//判断目标是否在攻击范围内
	//CREATE_FUNC(Tower_body);
};

/*炮台类*/
class Tower : public cocos2d::Sprite {
protected:
	Tower_body* TowerBody = nullptr;
	cocos2d::Sprite* TowerBase = nullptr;
public:
	virtual void build() = 0;
	void up_level_tower();//升级炮台
	int sell_tower();//出售炮台
	float get_attack_range();//获得攻击范围
	int get_level();//获得等级
	int get_level_up_money();//获得升级所需金币
	int get_sell_money();//获得出售价格
	/*
	void createBuildEffect(const string& effectPath, const vec2& vec) {
		auto Effect = Sprite::create();
		Vector<SpriteFrame*> frame;
		frame.pushBack(SpriteFrame::create(effectPath + "Items02-hd_1.PNG", Rect(0, 0, 161, 133)));
		frame.pushBack(SpriteFrame::create(effectPath + "Items02-hd_2.PNG", Rect(0, 0, 169, 175)));
		frame.pushBack(SpriteFrame::create(effectPath + "Items02-hd_3.PNG", Rect(0, 0, 199, 224)));
		frame.pushBack(SpriteFrame::create(effectPath + "Items02-hd_4.PNG", Rect(0, 0, 242, 243)));

		auto remove_effect = CallFunc::create([=]() {
			this_layer->removeChild(Effect);
			});

		Effect->runAction(Sequence::create(Animate::create(Animation::createWithSpriteFrames(frame, 0.05)), remove_effect, nullptr));
		Effect->setPosition(vec.x, vec.y);
		this_layer->addChild(Effect);
	}*/
	//void bullet_fly(Tower_information 
	// 
	// , cocos2d::Vec2 start, cocos2d::Vec2 end, cocos2d::Layer* this_layer);//子弹飞行动画
	//void attack_once(Tower_information tower, cocos2d::Vec2 start, cocos2d::Vec2 end, cocos2d::Layer* this_layer);//单次攻击动画
};

int getMoney(int tag);//根据名称标签获得初始价值

Tower* build_tower(int tag);//根据名称标签建造一个炮台