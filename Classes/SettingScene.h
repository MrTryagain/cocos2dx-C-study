//
//  SettingScene.hpp
//  Hello
//
//  Created by Mybogames on 2020/7/27.
//
#include<cocos2d.h>

class Setting : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();
    //回调函数声明
    void menuSoundToggleCallback(Ref* pSender);
    void menuMusicToggleCallback(Ref* pSender);
    void menuOkCallback(Ref* pSender);
    CREATE_FUNC(Setting);
};

