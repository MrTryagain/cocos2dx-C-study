
#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    //回调函数声明
    void menuCloseCallback(cocos2d::Ref* pSender);
    void menuItemStartCallback(Ref* pSender);
    void menuItemStart2Callback(Ref* pSender);
    void menuItemSettingCallback(Ref* pSender);
    void menuItemHelpCallback(Ref* pSender);
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__

