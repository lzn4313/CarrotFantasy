#ifndef __Menu_SCENE_H__
#define __Menu_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

//�˵��������
class MenuScene : public cocos2d::Scene
{
private:
    Size visibleSize;
    void initBackGround();
    void initCloud();
    void initMonster();
    void initCarrot();
    void initTitle();
    void initMenu();

    //�ر���Ϸ
    void close_game(Ref* pSender);
    //ȥ���ý���
    void goto_options(Ref* pSender);
    //ȥ��������
    void goto_helper(Ref* pSender);
    //ȥð��ģʽ
    void goto_adventure(Ref* psender);
    //ȥbossģʽ
    void goto_boss(Ref* psender);
    //ȥ������
    void goto_nest(Ref* psender);

public:
    //���캯��
    static cocos2d::Scene* createScene();//�̳д�������
    virtual bool init();
    CREATE_FUNC(MenuScene);
};

#endif // __Menu_SCENE_H__
