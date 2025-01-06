#ifndef __Options_SCENE_H__
#define __Options_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;


//���ý��������ѡ��ҳ
class SetLayer :public cocos2d::Layer
{
private:
    Size visibleSize;
    void initBackGround();
    void initMenu();

    //�ر���Ч
    virtual void close_sound(Ref* psender);
    //�ر�bgm
    virtual void close_bgmusic(Ref* psender);
    //������Ϸ�浵����
    virtual void reset_game(Ref* psender);
public:
    //���캯��
    static cocos2d::Layer* createLayer();//�̳д�������
    virtual bool init();
    CREATE_FUNC(SetLayer);

};
//���ý����ͳ��ѡ��ҳ
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
    //���캯��
    static cocos2d::Layer* createLayer();//�̳д�������
    virtual bool init();
    CREATE_FUNC(StatisticsLayer);
};
//���ý������Աѡ��ҳ
class PersonLayer :public cocos2d::Layer
{
private:
    Size visibleSize;

    void initBackGround();
public:
    //���캯��
    static cocos2d::Layer* createLayer();//�̳д�������
    virtual bool init();
    CREATE_FUNC(PersonLayer);
};
class OptionsState;
//���ý���
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

    //ȥ���˵�
    void goto_menu(Ref* psender);
    //ȥ����ѡ��ҳ
    void goto_set(Ref* psender);
    //ȥͳ��ѡ��ҳ
    void goto_statistics(Ref* psender);
    //ȥ��Աѡ��ҳ
    void goto_person(Ref* psender);
public:
    friend class OptionsState;
    //���캯��
    static cocos2d::Scene* createScene();//�̳д�������
    virtual bool init();
    CREATE_FUNC(OptionsScene);
};

//����״̬
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