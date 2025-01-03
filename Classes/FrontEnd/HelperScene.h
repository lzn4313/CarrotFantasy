#ifndef __Helper_SCENE_H__
#define __Helper_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;
//����ѡ�
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
    //���캯��
    static cocos2d::Layer* createLayer();//�̳д�������
    virtual bool init();
    CREATE_FUNC(HelpLayer);
};
//����ѡ�
class MonsterLayer :public cocos2d::Layer {
private:
    Size visibleSize;
    void initBackGround();
public:
    //���캯��
    static cocos2d::Layer* createLayer();//�̳д�������
    virtual bool init();
    CREATE_FUNC(MonsterLayer);
};
//������չʾѡ�
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
    //���캯��
    static cocos2d::Layer* createLayer();//�̳д�������
    virtual bool init();
    CREATE_FUNC(TowerLayer);
};

class HelperState;
//��������Scene
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

    //��ʼ������
    void initBackGround();
    //��ʼ���˵�
    void initMenu();
    //��ʼ������
    void initLayers();
    //�������˵�
    void goto_home(Ref* psender);
    //ȥ����ѡ�
    void goto_help(Ref* psender);
    //ȥ����ѡ�
    void goto_monster(Ref* psender);
    //ȥ������ѡ�
    void goto_tower(Ref* psender);
public:
    //���캯��
    static cocos2d::Scene* createScene();//�̳д�������
    virtual bool init();
    CREATE_FUNC(HelperScene);

};
//����״̬
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
