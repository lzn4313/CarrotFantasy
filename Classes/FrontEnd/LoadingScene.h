#ifndef __LOADING_SCENE_H__
#define __LOADING_SCENE_H__

#include "cocos2d.h"

class LoadingScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(LoadingScene);

    void loadSource(); 
    void logic(float dt);
    int numberOfLoadedRes;
    void cacheImage(const std::string& filepath);
};

#endif // __LOADING_SCENE_H__