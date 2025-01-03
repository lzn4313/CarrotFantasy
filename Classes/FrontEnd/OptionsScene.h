#ifndef __Options_SCENE_H__
#define __Options_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;


//设置界面的设置选项页
class SetLayer :public cocos2d::Layer
{
private:
    Size visibleSize;
    void initBackGround();
    void initMenu();

    //关闭音效
    virtual void close_sound(Ref* psender);
    //关闭bgm
    virtual void close_bgmusic(Ref* psender);
    //重置游戏存档数据
    virtual void reset_game(Ref* psender);
public:
    //构造函数
    static cocos2d::Layer* createLayer();//继承创建场景
    virtual bool init();
    CREATE_FUNC(SetLayer);

};
//设置界面的统计选项页
class StatisticsLayer :public cocos2d::Layer
{
private:
    Size visibleSize;

    void initBackGround();
    void initBg_1();
    void initBg_2();
    void initBg_3();
    void initBg_4();
    void initBg_5();
    void initBg_6();
    void initBg_7();
public:
    //构造函数
    static cocos2d::Layer* createLayer();//继承创建场景
    virtual bool init();
    CREATE_FUNC(StatisticsLayer);
};
//设置界面的人员选项页
class PersonLayer :public cocos2d::Layer
{
private:
    Size visibleSize;

    void initBackGround();
public:
    //构造函数
    static cocos2d::Layer* createLayer();//继承创建场景
    virtual bool init();
    CREATE_FUNC(PersonLayer);
};
class OptionsState;
//设置界面
class OptionsScene : public cocos2d::Scene
{
    friend class SetState;
    friend class StatisticsState;
    friend class PersonState;
private:
    Size visibleSize;

    MenuItemImage* set_btn;
    MenuItemImage* statistics_btn;
    MenuItemImage* person_btn;

    SetLayer* setLayer;
    StatisticsLayer* statisticsLayer;
    PersonLayer* personLayer;

    OptionsState* currentState;

    void initMenu();
    void initLayers();

    //去主菜单
    void goto_menu(Ref* psender);
    //去设置选项页
    void goto_set(Ref* psender);
    //去统计选项页
    void goto_statistics(Ref* psender);
    //去人员选项页
    void goto_person(Ref* psender);
public:
    friend class OptionsState;
    //构造函数
    static cocos2d::Scene* createScene();//继承创建场景
    virtual bool init();
    CREATE_FUNC(OptionsScene);
};

//界面状态
class OptionsState {
public:
    virtual ~OptionsState() {}
    virtual void enter(OptionsScene* scene) = 0;
    virtual void exit(OptionsScene* scene) = 0;
};

class SetState : public OptionsState {
public:
    void enter(OptionsScene* scene) {
        scene->setLayer->setVisible(true);
        scene->set_btn->setEnabled(false);
        scene->set_btn->setScale(1);
        scene->set_btn->setPositionX(scene->visibleSize.width * 0.3);
    }
    void exit(OptionsScene* scene) {
        scene->setLayer->setVisible(false);
        scene->set_btn->setEnabled(true);
        scene->set_btn->setScale(1.4);
        scene->set_btn->setPositionX(scene->visibleSize.width * 0.3);
    }
};
class StatisticsState : public OptionsState {
    void enter(OptionsScene* scene) {
        scene->statisticsLayer->removeAllChildrenWithCleanup(true);
        scene->statisticsLayer->init();
        scene->statisticsLayer->setVisible(true);
        scene->statistics_btn->setEnabled(false);
        scene->statistics_btn->setScale(1);
    }
    void exit(OptionsScene* scene) {
        scene->statisticsLayer->setVisible(false);
        scene->statistics_btn->setEnabled(true);
        scene->statistics_btn->setScale(1.4);
    }
};

class PersonState : public OptionsState {
    void enter(OptionsScene* scene) {
        scene->personLayer->setVisible(true);
        scene->person_btn->setEnabled(false);
        scene->person_btn->setScale(1);
    }
    void exit(OptionsScene* scene) {
        scene->personLayer->setVisible(false);
        scene->person_btn->setEnabled(true);
        scene->person_btn->setScale(1.4);
    }
};
#endif // __Options_SCENE_H__