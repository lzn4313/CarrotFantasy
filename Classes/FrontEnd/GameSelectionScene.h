#ifndef __GameSelection_SCENE_H__
#define __GameSelection_SCENE_H__

USING_NS_CC;
//冒险模式选关界面类
class GameSelectionScene : public cocos2d::Scene
{
private:
    Size visibleSize;

    void initBackGround();
    void initMenu();
    void initBigLevelLayer();

    void gotoHelper(Ref* psender);
public:
    //构造函数
    static cocos2d::Scene* createScene();//继承创建场景
    virtual bool init();
    CREATE_FUNC(GameSelectionScene);
};
//选大关界面
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
    //创建滑动层（供滑动翻页）
    void create_slide_layer();
    //去冒险模式
    void goto_evaluate();
    //以按钮方式向左翻页
    void page_left(Ref* psender);
    //以按钮方式向右翻页
    void page_right(Ref* psender);
    //去天际选小关
    void goto_level_1();
    //去丛林选小关
    void goto_level_2();
    //去沙漠选小关
    void goto_level_3();
public:
    //构造函数
    static cocos2d::Layer* createLayer();//继承创建场景
    virtual bool init();
    CREATE_FUNC(BigLevelLayer);

};
////选天际小关界面
//class Level_1_Layer :public cocos2d::Layer
//{
//private:
//    Size visibleSize;
//
//    static const int totalPage = 4;
//    std::string numImage[totalPage];
//    float pagesPoint[totalPage];
//    int currentPage;
//
//    void initSlideLayer();
//    void initListener();
//
//    void nextPage();
//    void lastPage();
//    void rollBack();
//public:
//    //构造函数
//    static cocos2d::Layer* createLayer();//继承创建场景
//    virtual bool init();
//    CREATE_FUNC(Level_1_Layer);
//    //创建滑动层（供滑动翻页）
//    void create_slide_layer();
//    //返回选大关界面
//    void return_to_biglevel(Ref* psender);
//    //选择第1小关
//    void level_1_1(Ref* psender, Widget::TouchEventType type);
//    //选择第2小关
//    void level_1_2(Ref* psender, Widget::TouchEventType type);
//    //选择第3小关
//    void level_1_3(Ref* psender, Widget::TouchEventType type);
//    //选择第4小关
//    void level_1_4(Ref* psender, Widget::TouchEventType type);
//    //选择第5小关
//    void level_1_5(Ref* psender, Widget::TouchEventType type);
//};
#endif // __GameSelection_SCENE_H__
