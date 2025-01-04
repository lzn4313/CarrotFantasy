#include "cocos2d.h"
#include "Game/GameScene.h"
#include "Game/enemy.h"
using namespace std;

/*�������ǩ��Ӧ*/
#define Tower_Bottle 1
#define Tower_Shit 2
#define Tower_Fan 3
#define Tower_Star 4

/*����Ч�����ǩ��Ӧ*/
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
	int name_tag;//��¼���Ʊ�ǩ
	int value;//��¼��ǰ��ֵ
	float attack;//��¼���ι�����
	float attack_speed;//��¼�����ٶ�
	float attack_range;//��¼������Χ
	int attack_special;//��¼���⹥��Ч������͸�����١����ѵȣ�
	int level;//��¼�ȼ�

	Tower_information(int t = 0, int v = 0, float atk = 0, float atk_speed = 0, float atk_r = 1, int atk_special = 0, int L = 1)
		:name_tag(t), value(v), attack(atk), attack_speed(atk_speed), attack_range(atk_r), attack_special(atk_special), level(L)
	{}//���캯��

};

class Bullet :public cocos2d::Sprite {
protected:
	Enemy* Target = nullptr;
	Tower_body* Father = nullptr;
public:
	virtual bool init();
	virtual void update(float dt);//ʵʱ�жϷ�Χ���Ƿ��е��ˣ����򹥻�
	//CREATE_FUNC(Bullet);
};

class Tower_body :public cocos2d::Sprite {
protected:
	Tower_information tower_information;
	float time = 0;//���ƹ������
public:
	//���캯��
	Tower_body(Tower_information tower_information) {
		this->tower_information = tower_information;
	}
	virtual bool init();
	virtual void update(float dt);//ʵʱ�жϷ�Χ���Ƿ��е��ˣ����򹥻�
	Tower_information getInfo() { return tower_information; }
	void setInfo(Tower_information info) { this->tower_information = info; }
	bool is_in_range(Enemy* Target);//�ж�Ŀ���Ƿ��ڹ�����Χ��
	//CREATE_FUNC(Tower_body);
};

/*��̨��*/
class Tower : public cocos2d::Sprite {
protected:
	Tower_body* TowerBody = nullptr;
	cocos2d::Sprite* TowerBase = nullptr;
public:
	virtual void build() = 0;
	void up_level_tower();//������̨
	int sell_tower();//������̨
	float get_attack_range();//��ù�����Χ
	int get_level();//��õȼ�
	int get_level_up_money();//�������������
	int get_sell_money();//��ó��ۼ۸�
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
	// , cocos2d::Vec2 start, cocos2d::Vec2 end, cocos2d::Layer* this_layer);//�ӵ����ж���
	//void attack_once(Tower_information tower, cocos2d::Vec2 start, cocos2d::Vec2 end, cocos2d::Layer* this_layer);//���ι�������
};

int getMoney(int tag);//�������Ʊ�ǩ��ó�ʼ��ֵ

Tower* build_tower(int tag);//�������Ʊ�ǩ����һ����̨