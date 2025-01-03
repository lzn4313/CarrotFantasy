#ifndef __LOADING_SCENE_H__
#define __LOADING_SCENE_H__

#include "cocos2d.h"

class LoadingScene : public cocos2d::Scene
{
private:
    int numberOfLoadedRes;

    void loadSource();
    void loadMenu();
    void loadOptions();
    void loadHelper();
    void loadGameSelection();
    void check(float dt);
    void cacheImage(const std::string& filepath);
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(LoadingScene);
};

#endif // __LOADING_SCENE_H__