#ifndef __Helper_SCENE_H__
#define __Helper_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;
//帮助选项卡
class HelpLayer : public cocos2d::Layer {
private:
    Size visibleSize;
    
    Layer* slideLayer;
    Sprite* pageNum;

    static const int totalPage = 4;
    std::string numImage[totalPage];
    float pagesPoint[totalPage];
    int currentPage;

    void initSlideLayer();
    void initListener();

    void nextPage();
    void lastPage();
    void rollBack();
public:
    //构造函数
    static cocos2d::Layer* createLayer();//继承创建场景
    virtual bool init();
    CREATE_FUNC(HelpLayer);
};
//怪物选项卡
class MonsterLayer :public cocos2d::Layer {
private:
    Size visibleSize;
    void initBackGround();
public:
    //构造函数
    static cocos2d::Layer* createLayer();//继承创建场景
    virtual bool init();
    CREATE_FUNC(MonsterLayer);
};
//防御塔展示选项卡
class TowerLayer :public cocos2d::Layer {
private:
    Size visibleSize;

    Layer* slideLayer;
    Sprite* pageNum;

    static const int totalPage = 10;
    std::string numImage[totalPage];
    float pagesPoint[totalPage];
    int currentPage;

    void initSlideLayer();
    void initListener();

    void nextPage();
    void lastPage();
    void rollBack();
public:
    //构造函数
    static cocos2d::Layer* createLayer();//继承创建场景
    virtual bool init();
    CREATE_FUNC(TowerLayer);
};

class HelperState;
//帮助界面Scene
class HelperScene : public cocos2d::Scene
{
friend class HelpState;
friend class MonsterState;
friend class TowerState;
private:
    Size visibleSize;

    MenuItemImage* help_btn;
    MenuItemImage* monster_btn;
    MenuItemImage* tower_btn;

    HelpLayer* helpLayer;
    MonsterLayer* monsterLayer;
    TowerLayer* towerLayer;

    HelperState* currentState;

    //初始化背景
    void initBackGround();
    //初始化菜单
    void initMenu();
    //初始化三层
    void initLayers();
    //返回主菜单
    void goto_home(Ref* psender);
    //去帮助选项卡
    void goto_help(Ref* psender);
    //去怪物选项卡
    void goto_monster(Ref* psender);
    //去防御塔选项卡
    void goto_tower(Ref* psender);
public:
    //构造函数
    static cocos2d::Scene* createScene();//继承创建场景
    virtual bool init();
    CREATE_FUNC(HelperScene);

};
//界面状态
class HelperState {
public:
    virtual ~HelperState() {}
    virtual void enter(HelperScene* scene) = 0;
    virtual void exit(HelperScene* scene) = 0;
};
class HelpState : public HelperState {
public:
    void enter(HelperScene* scene) {
        scene->helpLayer->init();
        scene->helpLayer->setVisible(true);
        scene->help_btn->setEnabled(false);
        scene->help_btn->setScale(1);
    }
    void exit(HelperScene* scene) {
        scene->helpLayer->removeAllChildrenWithCleanup(true);
        scene->helpLayer->setVisible(false);
        scene->help_btn->setEnabled(true);
        scene->help_btn->setScale(1.4);
    }
};
class MonsterState : public HelperState {
    void enter(HelperScene* scene) {
        scene->monsterLayer->setVisible(true);
        scene->monster_btn->setEnabled(false);
        scene->monster_btn->setScale(1);
    }
    void exit(HelperScene* scene) {
        scene->monsterLayer->setVisible(false);
        scene->monster_btn->setEnabled(true);
        scene->monster_btn->setScale(1.4);
    }
};
class TowerState : public HelperState {
    void enter(HelperScene* scene) {
        scene->towerLayer->init();
        scene->towerLayer->setVisible(true);
        scene->tower_btn->setEnabled(false);
        scene->tower_btn->setScale(1);
    }
    void exit(HelperScene* scene) {
        scene->towerLayer->removeAllChildrenWithCleanup(true);
        scene->towerLayer->setVisible(false);
        scene->tower_btn->setEnabled(true);
        scene->tower_btn->setScale(1.4);
    }
};
#endif // __Helper_SCENE_H__
