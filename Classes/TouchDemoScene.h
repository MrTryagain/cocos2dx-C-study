#include<cocos2d.h>

class TouchDemo : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    virtual void onExit();
    //回调函数声明
    bool onTouchBeganCallback(cocos2d::Touch* touch,cocos2d::Event* event);
    void onTouchMovedCallback(cocos2d::Touch* touch,cocos2d::Event* event);
    void onTouchEndedCallback(cocos2d::Touch* touch,cocos2d::Event* event);
    CREATE_FUNC(TouchDemo);
};

