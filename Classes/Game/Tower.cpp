#include"Game/Tower.h"
#include"Config/sound&music.h"
#include"Game/enemy.h"
#include <string>
#include <cmath>
USING_NS_CC;
using namespace cocos2d::ui;

extern Tower* tower_map[7][12];//记录地图上的炮台信息
extern char game_map[7][12];//辅助地图数组
extern int if_speed_up;//是否加速
extern int if_pause;//是否暂停
extern int carrot_hp;//记录萝卜血量
extern int carrot_level;//记录萝卜等级
extern pos carrot_position;//记录萝卜位置
extern vector<Enemy*> monster;//储存怪物

const string str[TOWER_NUM + 1] = { "/Tower/Bottle/", "/Tower/Shit/", "/Tower/Fan/", "/Tower/Star/", "/Tower/Build/" };

/*
Sprite* Bullet::createSprite()
{
	return Bullet::create();
}

bool Bullet::init()
{
	if (!Sprite::init())
		return false;
	this->scheduleUpdate();
	return true;
}

void Bullet::update(float dt)
{
	if (if_pause == 0) {
		if (Target != nullptr && Farther != nullptr) {
			float x, y, r;
			x = Target->getPositionX() - this->getPositionX();
			y = Target->getPositionY() - this->getPositionY();
			r = -atan2f(y, x) / 3.14159 * 180;
			/*中心距离小于等于目标大小，视为击中
			((this->getPosition().x - Target->getPosition().x) * (this->getPosition().x - Target->getPosition().x)
				+ (this->getPosition().y - Target->getPosition().y) * (this->getPosition().y - Target->getPosition().y))
				<= ((Target->getContentSize().width / 2) * (Target->getContentSize().width / 2)
					+ (Target->getContentSize().height / 2) * (Target->getContentSize().height / 2))*
			if (fabs(this->getPosition().x - Target->getPosition().x) <= (Target->getContentSize().width / 2))
			{
				Target->declineHp(Farther->tower_information);
				this->removeFromParent();
			}
			else {
				double ds = 300 * dt * (if_speed_up + 1);
				double dx = ds * cos(360-r);
				double dy = dx * sin(360-r);
				this->setRotation(r);
				this->setPosition(this->getPosition().x + dx, this->getPosition().y + dy);
			}
		}
	}
}

Sprite* Tower_body::createSprite()
{
	return Tower_body::create();
}*/


class TowerFactory {
public:
	virtual Tower* createTower() = 0;
};

class BottleFactory : public TowerFactory {
public:
	Tower* createTower() override {
		Tower* tower = nullptr;
		tower = new TowerBottle();
		tower->build();
		return tower;
	}
};

class ShitFactory : public TowerFactory {
public:
	Tower* createTower() override {
		Tower* tower = nullptr;
		tower = new TowerShit();
		tower->build();
		return tower;
	}
};

class FanFactory : public TowerFactory {
public:
	Tower* createTower() override {
		Tower* tower = nullptr;
		tower = new TowerFan();
		tower->build();
		return tower;
	}
};

class StarFactory : public TowerFactory {
public:
	Tower* createTower() override {
		Tower* tower = nullptr;
		tower = new TowerStar();
		tower->build();
		return tower;
	}
};

class TowerBottle : public Tower {
public:
	void build() override {
		int tag = Tower_Bottle;

		TowerBase = Sprite::create();
		Tower_information tower_information = Tower_information{ tag, Tower_Value[tag - 1], Tower_Attack[tag - 1], Tower_Attack_Speed[tag - 1], 1.2, tag - 1, 1 };
		TowerBody = new Tower_body(tower_information);

		TowerBase->setTexture(str[tag - 1] + "base_1.PNG");
		TowerBody->setTexture(str[tag - 1] + "origin1.PNG");
		TowerBody->setRotation(-90);
	}
};

class TowerShit : public Tower {
public:
	void build() override {
		int tag = Tower_Shit;

		TowerBase = Sprite::create();
		Tower_information tower_information = Tower_information{ tag, Tower_Value[tag - 1], Tower_Attack[tag - 1], Tower_Attack_Speed[tag - 1], 1.2, tag - 1, 1 };
		TowerBody = new Tower_body(tower_information);

		TowerBase->setTexture(str[tag - 1] + "base_1.PNG");
		TowerBody->setTexture(str[tag - 1] + "origin1.PNG");
	}
};

class TowerFan : public Tower {
public:
	void build() override {
		int tag = Tower_Fan;

		TowerBase = Sprite::create();
		Tower_information tower_information = Tower_information{ tag, Tower_Value[tag - 1], Tower_Attack[tag - 1], Tower_Attack_Speed[tag - 1], 1.2, tag - 1, 1 };
		TowerBody = new Tower_body(tower_information);

		TowerBase->setTexture(str[tag - 1] + "base_1.PNG");
		TowerBody->setTexture(str[tag - 1] + "origin1.PNG");
	}
};

class TowerStar : public Tower {
public:
	void build() override {
		int tag = Tower_Star;

		TowerBase = Sprite::create();
		Tower_information tower_information = Tower_information{ tag, Tower_Value[tag - 1], Tower_Attack[tag - 1], Tower_Attack_Speed[tag - 1], 1.2, tag - 1, 1 };
		TowerBody = new Tower_body(tower_information);

		TowerBase->setTexture(str[tag - 1] + "base_1.PNG");
		TowerBody->setTexture(str[tag - 1] + "origin1.PNG");
		TowerBody->setRotation(0);
	}
};



class BulletFactory {
public:
	virtual Bullet* createBullet(Enemy* target, Tower_body* father) = 0;
};

class BottleBulletFactory : public BulletFactory {
public:
	Bullet* createBullet(Enemy* target, Tower_body* father) override {
		Bullet* bullet = nullptr;
		bullet = new BottleBullet(target, father);
		return bullet;
	}
};

class ShitBulletFactory : public BulletFactory {
public:
	Bullet* createBullet(Enemy* target, Tower_body* father) override {
		Bullet* bullet = nullptr;
		bullet = new ShitBullet(target, father);
		return bullet;
	}
};

class FanBulletFactory : public BulletFactory {
public:
	Bullet* createBullet(Enemy* target, Tower_body* father) override {
		Bullet* bullet = nullptr;
		bullet = new FanBullet(target, father);
		return bullet;
	}
};

class StarBulletFactory : public BulletFactory {
public:
	Bullet* createBullet(Enemy* target, Tower_body* father) override {
		Bullet* bullet = nullptr;
		bullet = new StarBullet(target, father);
		return bullet;
	}
};

class BottleBullet : public Bullet {
public:
	BottleBullet(Enemy* target, Tower_body* father) {
		this->Target = target;
		this->Father = father;
		Vec2 my_position = this->Father->getPosition();

		int tag = Tower_Bottle;
		switch (this->Father->getInfo().level) {
			case 1:
				this->setTexture(str[tag - 1] + "bullet1.PNG");
				break;
			case 2:
				this->setTexture(str[tag - 1] + "bullet2.PNG");
				break;
			case 3:
				this->setTexture(str[tag - 1] + "bullet3.PNG");
				break;
			default:
				break;
		}

		float dx, dy, r;
		dx = target->getPosition().x - my_position.x;
		dy = target->getPosition().y - my_position.y;
		r = -atan2f(dy, dx) / M_PI * 180;

		this->setPosition(my_position);
		this->setRotation(r);

		auto remove_bullet = CallFunc::create([=]() {
			this->removeFromParent();
			});

		auto attacked = CallFunc::create([=]() {
			if (target != nullptr)
				target->declineHp(this->Father->getInfo(), 0);
			});

		auto bullet_move_to = cocos2d::MoveTo::create((if_speed_up == 0 ? 0.2 : (0.2 / 2)), target->getPosition());
		this->runAction(Sequence::create(bullet_move_to, DelayTime::create(0), remove_bullet, DelayTime::create(0), attacked, nullptr));
		this->Father->addChild(this);
	}
};

class ShitBullet : public Bullet {
public:
	ShitBullet(Enemy* target, Tower_body* father) {
		this->Target = target;
		this->Father = father;
		Vec2 my_position = this->Father->getPosition();

		int tag = Tower_Shit;
		switch (this->Father->getInfo().level) {
			case 1:
				this->setTexture(str[tag - 1] + "bullet1.PNG");
				break;
			case 2:
				this->setTexture(str[tag - 1] + "bullet2.PNG");
				break;
			case 3:
				this->setTexture(str[tag - 1] + "bullet3.PNG");
				break;
			default:
				break;
		}

		float dx, dy, r;
		dx = target->getPosition().x - my_position.x;
		dy = target->getPosition().y - my_position.y;
		r = -atan2f(dy, dx) / M_PI * 180;

		this->setPosition(my_position);
		this->setRotation(r);

		auto remove_bullet = CallFunc::create([=]() {
			this->removeFromParent();
			});

		auto attacked = CallFunc::create([=]() {
			if (target != nullptr)
				target->declineHp(this->Father->getInfo(), 0);
			});

		auto bullet_move_to = cocos2d::MoveTo::create((if_speed_up == 0 ? 0.25 : (0.25 / 2)), target->getPosition());
		this->runAction(Sequence::create(bullet_move_to, DelayTime::create(0), remove_bullet, DelayTime::create(0), attacked, nullptr));
		this->Father->addChild(this);
	}
};

class FanBullet : public Bullet {
public:
	FanBullet(Enemy* target, Tower_body* father) {
		this->Target = target;
		this->Father = father;
		Vec2 my_position = this->Father->getPosition();

		int tag = Tower_Fan;
		switch (this->Father->getInfo().level) {
			case 1:
				this->setTexture(str[tag - 1] + "bullet1.PNG");
				break;
			case 2:
				this->setTexture(str[tag - 1] + "bullet2.PNG");
				break;
			case 3:
				this->setTexture(str[tag - 1] + "bullet3.PNG");
				break;
			default:
				break;
		}

		float dx, dy, r;
		dx = target->getPosition().x - my_position.x;
		dy = target->getPosition().y - my_position.y;
		r = -atan2f(dy, dx) / M_PI * 180;

		this->setPosition(my_position);
		this->setRotation(r);
	}
};

class StarBullet : public Bullet {
public:
	StarBullet(Enemy* target, Tower_body* father) {
		this->Target = target;
		this->Father = father;
		Vec2 my_position = this->Father->getPosition();

		int tag = Tower_Star;
		switch (this->Father->getInfo().level) {
			case 1:
				this->setTexture(str[tag - 1] + "bullet1.PNG");
				break;
			case 2:
				this->setTexture(str[tag - 1] + "bullet2.PNG");
				break;
			case 3:
				this->setTexture(str[tag - 1] + "bullet3.PNG");
				break;
			default:
				break;
		}

		float dx, dy, r;
		dx = target->getPosition().x - my_position.x;
		dy = target->getPosition().y - my_position.y;
		r = -atan2f(dy, dx) / M_PI * 180;

		this->setPosition(my_position);
		auto remove_bullet = CallFunc::create([=]() {
			this->removeFromParent();
			});

		auto attacked = CallFunc::create([=]() {
			if (target != nullptr) {
				Vec2 devided;
				if (target->declineHp(this->Father->getInfo(), 0)) {
					for (Enemy* enemy : monster) {
						devided = enemy->getPosition();
						if (((target->getPositionX() - devided.x) * (target->getPositionX() - devided.x) +
							(target->getPositionY() - devided.y) * (target->getPositionY() - devided.y))
							<= (160 * 160) * (this->Father->getInfo().attack_range + 1) / 2)
						{
							enemy->declineHp(this->Father->getInfo(), 1);
						}
					}
				}
			}
			});

		auto bullet_move_to = cocos2d::MoveTo::create(if_speed_up == 0 ? 0.33 : 0.33 / 2, target->getPosition());
		auto rotate = Spawn::create(bullet_move_to, Repeat::create(RotateBy::create(if_speed_up == 0 ? 0.33 : 0.33 / 2, 360), 1), nullptr);
		this->runAction(Sequence::create(rotate, DelayTime::create(0), remove_bullet, DelayTime::create(0), attacked, nullptr));
		this->Father->addChild(this);
	}
};



bool Bullet::init()
{
	if (!Sprite::init())
		return false;
	this->scheduleUpdate();
	return true;
}

bool Tower_body::init()
{
	if (!Sprite::init())
		return false;
	this->scheduleUpdate();
	return true;
}

/*重写update函数*/
void Tower_body::update(float dt)
{
	if (if_pause == 0) {
		time += dt;
		Vec2 my_position = this->getPosition();
		//Vec2 enemy_position;
		Enemy* target = nullptr;
		extern Enemy* destination;

		if (destination != nullptr && this->is_in_range(destination))
		{
			target = destination;
		}
		else {
			for (Enemy* enemy : monster) {
				if (this->is_in_range(enemy))
				{
					target = enemy;
					break;
				}
			}
		}

		if (target != nullptr) {
			if (time >= (if_speed_up == 0 ? (4 / tower_information.attack_speed) : (2 / tower_information.attack_speed))) {
				time = 0;
				Node* this_layer = this->getParent();
				Layer* ThisLayer = static_cast<Layer*>(this_layer);
				/*攻击前摇动画*/
				float dx, dy, r;
				dx = target->getPosition().x - my_position.x;
				dy = target->getPosition().y - my_position.y;
				r = -atan2f(dy, dx) / M_PI * 180;

				if (tower_information.name_tag == Tower_Bottle) {
					SoundManager::getInstance()->bottle_atk_sound_effect();
					this->setRotation(r);
					Vector<SpriteFrame*> frame;
					switch (tower_information.level) {
						case 1:
							frame.pushBack(SpriteFrame::create(str[tower_information.name_tag - 1] + "atk11.PNG", Rect(0, 0, 62, 24)));
							frame.pushBack(SpriteFrame::create(str[tower_information.name_tag - 1] + "atk12.PNG", Rect(0, 0, 62, 27)));
							frame.pushBack(SpriteFrame::create(str[tower_information.name_tag - 1] + "origin1.PNG", Rect(0, 0, 56, 25)));
							break;
						case 2:
							frame.pushBack(SpriteFrame::create(str[tower_information.name_tag - 1] + "atk21.PNG", Rect(0, 0, 69, 32)));
							frame.pushBack(SpriteFrame::create(str[tower_information.name_tag - 1] + "atk22.PNG", Rect(0, 0, 67, 40)));
							frame.pushBack(SpriteFrame::create(str[tower_information.name_tag - 1] + "origin2.PNG", Rect(0, 0, 63, 35)));
							break;
						case 3:
							frame.pushBack(SpriteFrame::create(str[tower_information.name_tag - 1] + "atk31.PNG", Rect(0, 0, 76, 43)));
							frame.pushBack(SpriteFrame::create(str[tower_information.name_tag - 1] + "atk32.PNG", Rect(0, 0, 72, 48)));
							frame.pushBack(SpriteFrame::create(str[tower_information.name_tag - 1] + "origin3.PNG", Rect(0, 0, 70, 46)));
							break;
						default:
							break;
					}
					this->runAction(Sequence::create(Animate::create(Animation::createWithSpriteFrames(frame, 0.1)), nullptr));

					Bullet* bullet = nullptr;
					BulletFactory* factory = new BottleBulletFactory();
					bullet = factory->createBullet(target, this);
					//this->addChild(bullet);

					/*
					auto bullet = Sprite::create();
					switch (tower_information.level)
					{
						case 1:
							bullet->setTexture(str[tower_information.name_tag - 1] + "bullet1.PNG");
							break;
						case 2:
							bullet->setTexture(str[tower_information.name_tag - 1] + "bullet2.PNG");
							break;
						case 3:
							bullet->setTexture(str[tower_information.name_tag - 1] + "bullet3.PNG");
							break;
						default:
							break;
					}
					bullet->setPosition(this->getPosition());

					auto remove_bullet = CallFunc::create([=]() {
						bullet->removeFromParent();
						});

					auto attacked = CallFunc::create([=]() {
						if (target != nullptr)
							target->declineHp(tower_information, 0);
						});

					bullet->setRotation(r);
					auto bullet_move_to = cocos2d::MoveTo::create(if_speed_up == 0 ? 0.2 : 0.2 / 2, target->getPosition());
					bullet->runAction(Sequence::create(bullet_move_to, DelayTime::create(0), remove_bullet, DelayTime::create(0), attacked, nullptr));
					ThisLayer->addChild(bullet);*/
				}
				else if (tower_information.name_tag == Tower_Shit) {
					SoundManager::getInstance()->shit_atk_sound_effect();
					//利用帧动画完成攻击动画
					auto atk_Effect = Sprite::create();
					Vector<SpriteFrame*> frame;
					switch (tower_information.level) {
						case 1:
							frame.pushBack(SpriteFrame::create(str[tower_information.name_tag - 1] + "atk11.PNG", Rect(0, 0, 43, 46)));
							frame.pushBack(SpriteFrame::create(str[tower_information.name_tag - 1] + "atk12.PNG", Rect(0, 0, 55, 46)));
							frame.pushBack(SpriteFrame::create(str[tower_information.name_tag - 1] + "origin1.PNG", Rect(0, 0, 47, 41)));
							break;
						case 2:
							frame.pushBack(SpriteFrame::create(str[tower_information.name_tag - 1] + "atk21.PNG", Rect(0, 0, 48, 60)));
							frame.pushBack(SpriteFrame::create(str[tower_information.name_tag - 1] + "atk22.PNG", Rect(0, 0, 59, 57)));
							frame.pushBack(SpriteFrame::create(str[tower_information.name_tag - 1] + "origin2.PNG", Rect(0, 0, 52, 53)));
							break;
						case 3:
							frame.pushBack(SpriteFrame::create(str[tower_information.name_tag - 1] + "atk31.PNG", Rect(0, 0, 56, 68)));
							frame.pushBack(SpriteFrame::create(str[tower_information.name_tag - 1] + "atk32.PNG", Rect(0, 0, 70, 66)));
							frame.pushBack(SpriteFrame::create(str[tower_information.name_tag - 1] + "origin3.PNG", Rect(0, 0, 61, 65)));
							break;
						default:
							break;
					}
					this->runAction(Sequence::create(Animate::create(Animation::createWithSpriteFrames(frame, 0.1)), nullptr));

					Bullet* bullet = nullptr;
					BulletFactory* factory = new ShitBulletFactory();
					bullet = factory->createBullet(target, this);
					//this->addChild(bullet);

					/*
					auto bullet = Sprite::create();
					switch (tower_information.level)
					{
						case 1:
							bullet->setTexture(str[tower_information.name_tag - 1] + "bullet1.PNG");
							break;
						case 2:
							bullet->setTexture(str[tower_information.name_tag - 1] + "bullet2.PNG");
							break;
						case 3:
							bullet->setTexture(str[tower_information.name_tag - 1] + "bullet3.PNG");
							break;
						default:
							break;
					}
					bullet->setPosition(this->getPosition());

					auto remove_bullet = CallFunc::create([=]() {
						bullet->removeFromParent();
						});

					auto attacked = CallFunc::create([=]() {
						if (target != nullptr)
							target->declineHp(tower_information, 0);
						});

					bullet->setRotation(r);
					auto bullet_move_to = cocos2d::MoveTo::create((if_speed_up == 0 ? 0.25 : (0.25 / 2)), target->getPosition());
					bullet->runAction(Sequence::create(bullet_move_to, DelayTime::create(0), remove_bullet, DelayTime::create(0), attacked, nullptr));
					ThisLayer->addChild(bullet);*/
				}
				else if (tower_information.name_tag == Tower_Star) {
					SoundManager::getInstance()->star_atk_sound_effect();
					//利用帧动画完成攻击动画
					auto atk_Effect = Sprite::create();
					Vector<SpriteFrame*> frame;
					switch (tower_information.level) {
						case 1:
							frame.pushBack(SpriteFrame::create(str[tower_information.name_tag - 1] + "atk11.PNG", Rect(0, 0, 59, 59)));
							frame.pushBack(SpriteFrame::create(str[tower_information.name_tag - 1] + "atk12.PNG", Rect(0, 0, 61, 58)));
							frame.pushBack(SpriteFrame::create(str[tower_information.name_tag - 1] + "origin1.PNG", Rect(0, 0, 53, 54)));
							break;
						case 2:
							frame.pushBack(SpriteFrame::create(str[tower_information.name_tag - 1] + "atk21.PNG", Rect(0, 0, 60, 60)));
							frame.pushBack(SpriteFrame::create(str[tower_information.name_tag - 1] + "atk22.PNG", Rect(0, 0, 70, 69)));
							frame.pushBack(SpriteFrame::create(str[tower_information.name_tag - 1] + "origin2.PNG", Rect(0, 0, 57, 56)));
							break;
						case 3:
							frame.pushBack(SpriteFrame::create(str[tower_information.name_tag - 1] + "atk31.PNG", Rect(0, 0, 72, 73)));
							frame.pushBack(SpriteFrame::create(str[tower_information.name_tag - 1] + "atk32.PNG", Rect(0, 0, 73, 74)));
							frame.pushBack(SpriteFrame::create(str[tower_information.name_tag - 1] + "origin3.PNG", Rect(0, 0, 68, 70)));
							break;
						default:
							break;
					}

					this->runAction(Sequence::create(Animate::create(Animation::createWithSpriteFrames(frame, 0.11)), nullptr));

					Bullet* bullet = nullptr;
					BulletFactory* factory = new StarBulletFactory();
					bullet = factory->createBullet(target, this);
					//this->addChild(bullet);

					/*
					auto bullet = Sprite::create();
					switch (tower_information.level)
					{
						case 1:
							bullet->setTexture(str[tower_information.name_tag - 1] + "bullet1.PNG");
							break;
						case 2:
							bullet->setTexture(str[tower_information.name_tag - 1] + "bullet2.PNG");
							break;
						case 3:
							bullet->setTexture(str[tower_information.name_tag - 1] + "bullet3.PNG");
							break;
						default:
							break;
					}
					bullet->setPosition(this->getPosition());

					auto remove_bullet = CallFunc::create([=]() {
						bullet->removeFromParent();
						});

					auto attacked = CallFunc::create([=]() {
						if (target != nullptr) {
							Vec2 devided;
							if (target->declineHp(tower_information, 0)) {
								for (Enemy* enemy : monster) {
									devided = enemy->getPosition();
									if (((target->getPositionX() - devided.x) * (target->getPositionX() - devided.x) +
										(target->getPositionY() - devided.y) * (target->getPositionY() - devided.y))
										<= (160 * 160) * (tower_information.attack_range + 1) / 2)
									{
										enemy->declineHp(tower_information, 1);
									}
								}
							}
						}
						});

					auto bullet_move_to = cocos2d::MoveTo::create(if_speed_up == 0 ? 0.33 : 0.33 / 2, target->getPosition());
					auto rotate = Spawn::create(bullet_move_to, Repeat::create(RotateBy::create(if_speed_up == 0 ? 0.33 : 0.33 / 2, 360), 1), nullptr);
					bullet->runAction(Sequence::create(rotate, DelayTime::create(0), remove_bullet, DelayTime::create(0), attacked, nullptr));
					ThisLayer->addChild(bullet);*/
				}
			}
		}
	}
}

/*判断目标是否在攻击范围内*/
bool Tower_body::is_in_range(Enemy* Target) {
	if (Target != nullptr) {
		Vec2 my_position = this->getPosition();
		Vec2 target_position = Target->getPosition();
		Tower_information info = this->getInfo();
		if (pow((my_position.x - target_position.x), 2) + pow((my_position.y - target_position.y), 2)
			<= pow((info.attack_range * 80 * sqrt(2)), 2) + pow((Target->getContentSize().width / 2), 2) + pow((Target->getContentSize().height / 2), 2))
		{
			return true;
		}
	}
	return false;
}

/*升级炮台*/
void Tower::up_level_tower()
{
	if (TowerBody->getInfo().name_tag <= TOWER_NUM && TowerBody->getInfo().name_tag >= 1) {
		if (this->get_level() < Max_Level) {
			/*更新基本信息*/
			Tower_information newInfo = TowerBody->getInfo();
			newInfo.value += get_level_up_money();
			newInfo.level++;
			newInfo.attack *= 2;
			newInfo.attack_range += 0.5;
			if (newInfo.name_tag == Tower_Bottle)
				newInfo.attack_speed += 2;
			else
				newInfo.attack_speed *= 1.5;
			TowerBody->setInfo(newInfo);

			int level = TowerBody->getInfo().level;
			/*更新图片*/
			if (level == 2) {
				TowerBase->setTexture(str[TowerBody->getInfo().name_tag - 1] + "base_2.PNG");
				TowerBody->setTexture(str[TowerBody->getInfo().name_tag - 1] + "origin_2.PNG");
			}
			else if (level == 3) {
				TowerBase->setTexture(str[TowerBody->getInfo().name_tag - 1] + "base_3.PNG");
				TowerBody->setTexture(str[TowerBody->getInfo().name_tag - 1] + "origin_3.PNG");
			}

			if (TowerBody->getInfo().name_tag == Tower_Bottle)
				TowerBody->setRotation(-90);
			else if (TowerBody->getInfo().name_tag == Tower_Star)
				TowerBody->setRotation(0);
		}
	}

	/*/利用帧动画完成升级特效
	auto Effect_1 = Sprite::create();
	Vector<SpriteFrame*> frame;
	frame.pushBack(SpriteFrame::create("/Tower/Build/up1.png", Rect(0, 0, 77, 62)));
	frame.pushBack(SpriteFrame::create("/Tower/Build/up2.png", Rect(0, 0, 86, 69)));
	frame.pushBack(SpriteFrame::create("/Tower/Build/up3.png", Rect(0, 0, 95, 69)));
	frame.pushBack(SpriteFrame::create("/Tower/Build/up4.png", Rect(0, 0, 120, 80)));
	Effect_1->setScale(2);
	auto remove_effect_1 = CallFunc::create([=]() {
		this_layer->removeChild(Effect_1);
		});
	Effect_1->runAction(Sequence::create(Animate::create(Animation::createWithSpriteFrames(frame, 0.05)), remove_effect_1, nullptr));
	Effect_1->setPosition(vec.x, vec.y);
	this_layer->addChild(Effect_1, -1);

	auto Effect_2 = Sprite::create();
	Effect_2->setPosition(vec.x, vec.y);
	Effect_2->setTexture("/Tower/Build/up5.png");
	auto effect_move = cocos2d::MoveTo::create(0.2, Vec2{ vec.x,vec.y + 300 });
	Effect_2->setScale(2);
	auto remove_effect_2 = CallFunc::create([=]() {
		this_layer->removeChild(Effect_2);
		});
	Effect_2->runAction(Sequence::create(effect_move, remove_effect_2, nullptr));
	this_layer->addChild(Effect_2);*/

}

/*出售炮台*/
int Tower::sell_tower()
{
	int money = this->get_sell_money();
	this->removeFromParent();

	/*
	//利用帧动画完成删除特效
	vec2 vec = trans_ij_to_xy(position);
	auto Effect = Sprite::create();
	Vector<SpriteFrame*> frame;
	frame.pushBack(SpriteFrame::create("/Tower/Build/Items02-hd_1.PNG", Rect(0, 0, 161, 133)));
	frame.pushBack(SpriteFrame::create("/Tower/Build/Items02-hd_2.PNG", Rect(0, 0, 169, 175)));
	frame.pushBack(SpriteFrame::create("/Tower/Build/Items02-hd_3.PNG", Rect(0, 0, 199, 224)));
	frame.pushBack(SpriteFrame::create("/Tower/Build/Items02-hd_4.PNG", Rect(0, 0, 242, 243)));
	Effect->setPosition(vec.x, vec.y);
	this_layer->addChild(Effect);
	auto remove_effect = CallFunc::create([=]() {
		this_layer->removeChild(Effect);
		});
	Effect->runAction(Sequence::create(Animate::create(Animation::createWithSpriteFrames(frame, 0.05)), remove_effect, nullptr));
	*/

	delete this;
	return money;
}

/*获得出售价格*/
int Tower::get_sell_money() 
{
	if (this != nullptr && TowerBody != nullptr)
		return TowerBody->getInfo().value * 0.8;
	else
		return 0;
}

/*获得攻击范围*/
float Tower::get_attack_range()
{
	if (this != nullptr && TowerBody != nullptr)
		return TowerBody->getInfo().attack_range;
	else
		return 1;
}

/*获得等级*/
int Tower::get_level()
{
	if (this != nullptr && TowerBody != nullptr)
		return TowerBody->getInfo().level;
	else
		return 0;
}

/*获得升级所需金币*/
int Tower::get_level_up_money()
{
	if (this != nullptr && TowerBody != nullptr) {
		if (TowerBody->getInfo().name_tag == Tower_Bottle)
			return (100 + TowerBody->getInfo().level * 80);
		else
			return (TowerBody->getInfo().level == 1 ? 220 : 260);
	}
	else
		return (carrot_level == 1 ? 500 : 1000);
}

/*获得初始建造金币*/
int getMoney(int tag) {
	return Tower_Value[tag - 1];
}

/*建造炮台*/
Tower* build_tower(int tag)
{
	Tower* tower = nullptr;
	TowerFactory* factory = nullptr;
	if (tag <= TOWER_NUM && tag >=1) {
		// 使用工厂类创建相应的炮塔
		switch (tag)
		{
			case Tower_Bottle:
				factory = new BottleFactory();
				break;
			case Tower_Shit:
				factory = new ShitFactory();
				break;
			case Tower_Fan:
				factory = new FanFactory();
				break;
			case Tower_Star:
				factory = new StarFactory();
				break;
			default:
				break;
		}
		if (factory != nullptr) {
			tower = factory->createTower();
		}
	}
	return tower;
}