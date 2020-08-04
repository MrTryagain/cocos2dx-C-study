#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "SettingScene.h"
#include "PhysicScene.h"
#include "TouchDemoScene.h"//触摸demo
#include "MapInit.h"
#include "NinjaMove.h"
#include "CrashDetection.h"
#include "StructureDemo.h"
#include "ShopScene.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
//初始化
bool HelloWorld::init()
{
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    //设置背景
    auto bg = Sprite::create("fallbg.jpg");
    bg->setPosition(480,320);
    this->addChild(bg);
    //开始按钮精灵
    Sprite *startSpriteNormal = Sprite::create("start-up.png");
    Sprite *startSpriteSelected = Sprite::create("start-down.png");
    MenuItemSprite *startMenuItem = MenuItemSprite::create(startSpriteNormal,
                                                           startSpriteSelected,
                                                           CC_CALLBACK_1(HelloWorld::menuItemStartCallback, this));
    startMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(480, 170)));
    startMenuItem->setScale(0.5);
    
    //开始2按钮精灵
    Sprite *start2_1 = Sprite::create("Ball.png");
    Sprite *start2_2 = Sprite::create("Ball.png");
    MenuItemSprite *start2MenuItem = MenuItemSprite::create(start2_1,
                                                           start2_2,
                                                        CC_CALLBACK_1(HelloWorld::menuItemStart2Callback, this));
    start2MenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(280, 170)));
    start2MenuItem->setScale(0.5);
    //设置按钮
    MenuItemImage *settingMenuItem = MenuItemImage::create(
                                                           "setting-up.png",
                                                           "setting-down.png",
                                                           CC_CALLBACK_1(HelloWorld::menuItemSettingCallback, this));
    settingMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(480, 300)));
    settingMenuItem->setScale(0.5);
    
    // 帮助按钮
    MenuItemImage *helpMenuItem = MenuItemImage::create(
                                                        "help-up.png",
                                                        "help-down.png",
                                                        CC_CALLBACK_1(HelloWorld::menuItemHelpCallback, this));
    
    helpMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(480,430)));
    helpMenuItem->setScale(0.65);
    
    auto mu = Menu::create(startMenuItem,start2MenuItem,settingMenuItem,helpMenuItem,NULL);
    mu->setPosition(Vec2::ZERO);
    this->addChild(mu);
    return true;
}
//关闭菜单回调函数
void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}
//开始按钮回调函数
void HelloWorld::menuItemStartCallback(Ref* pSender)
{
    log("开始游戏");
    Director::getInstance()->pushScene(ShopScene::createScene());//场景跳转
}
//开始2按钮回调函数
void HelloWorld::menuItemStart2Callback(Ref* pSender)
{
    Director::getInstance()->replaceScene(PhysicScene::createScene());//场景跳转
}
//设置按钮回调函数
void HelloWorld::menuItemSettingCallback(Ref* pSender)
{
    Director::getInstance()->pushScene(Setting::createScene());//场景跳转
}
//帮助按钮回调函数
void HelloWorld::menuItemHelpCallback(Ref* pSender)
{
    Director::getInstance()->pushScene(ShopScene::createScene());
}

