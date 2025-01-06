#ifndef __GameSelection_SCENE_H__
#define __GameSelection_SCENE_H__

USING_NS_CC;
//ð��ģʽѡ�ؽ�����
class GameSelectionScene : public cocos2d::Scene
{
private:
    Size visibleSize;

    void initBackGround();
    void initMenu();
    void initBigLevelLayer();

    void gotoHelper(Ref* psender);
public:
    //���캯��
    static cocos2d::Scene* createScene();//�̳д�������
    virtual bool init();
    CREATE_FUNC(GameSelectionScene);
};
//ѡ��ؽ���
class BigLevelLayer : public cocos2d::Layer {
private:
    Size visibleSize;

    static const int totalPage = 4;
    std::string numImage[totalPage];
    float pagesPoint[totalPage];
    int currentPage;

    Sprite* evaluate;
    Sprite* skyline;
    Sprite* desert;
    Sprite* jungle;
    Layer* slideLayer;
    Sprite* pageNum[totalPage];

    void initMenu();
    void initPage();
    void initSlideLayer();
    void initListener();

    void goto_menu(Ref* psender);

    void nextPage();
    void lastPage();
    void rollBack();

    //ȥð��ģʽ
    void goto_evaluate();
    //ȥ���ѡС��
    void goto_level_1();
    //ȥ����ѡС��
    void goto_level_2();
    //ȥɳĮѡС��
    void goto_level_3();
public:
    //���캯��
    static cocos2d::Layer* createLayer();//�̳д�������
    virtual bool init();
    CREATE_FUNC(BigLevelLayer);
};
//ѡ���С�ؽ���
class Level_1_Layer :public cocos2d::Layer
{
private:
    Size visibleSize;

    static const int totalPage = 5;
    std::string numImage[totalPage];
    float pagesPoint[totalPage];
    int currentPage;

    Sprite* levels[totalPage];
    Layer* slideLayer;
    Layer* move_layer;
    Layer* static_layer;


    void initBackGround();
    void initMenu();
    void initSlideLayer();
    void initListener();

    void nextPage();
    void lastPage();
    void rollBack();

    //����ѡ��ؽ���
    void return_to_biglevel(Ref* psender);
    //ѡ���1С��
    void gotoGameScene(Ref* psender, int level);
public:
    //���캯��
    static cocos2d::Layer* createLayer();//�̳д�������
    virtual bool init();
    CREATE_FUNC(Level_1_Layer);
};
#endif // __GameSelection_SCENE_H__
