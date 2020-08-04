//
//  SettingScene.cpp
//  Hello
//
//  Created by Mybogames on 2020/7/27.
//

#include "SettingScene.h"
#include <SimpleAudioEngine.h>

USING_NS_CC;

Scene* Setting::createScene()
{
    auto scene = Scene::create();
    auto layer = Setting::create();
    scene->addChild(layer);
    return scene;
}

bool Setting::init(){
    if(!Layer::init()){
        return false;
    }
    //设置背景
    auto bg = Sprite::create("settingbg.jpg");
    bg->setPosition(480,320);
    addChild(bg);

    //音效开关
    auto soundOnMenuItem = MenuItemImage::create(
                                                 "on.png",
                                                 "on.png");
    auto soundOffMenuItem = MenuItemImage::create(
                                                  "off.png",
                                                  "off.png");
    auto soundToggleMenuItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(Setting::menuSoundToggleCallback, this),
                                                                  soundOnMenuItem,
                                                                  soundOffMenuItem,
                                                                  NULL);
    soundToggleMenuItem->setPosition(650,410);
    soundToggleMenuItem->setScale(0.5);

    //音乐开关
    auto musicOnMenuItem  = MenuItemImage::create(
                                                  "on.png",
                                                  "on.png");
    auto musicOffMenuItem  = MenuItemImage::create(
                                                   "off.png",
                                                   "off.png");
    auto musicToggleMenuItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(Setting::menuMusicToggleCallback, this),
                                                                  musicOnMenuItem,
                                                                  musicOffMenuItem,
                                                                  NULL );
    musicToggleMenuItem->setPosition(650,290);
    musicToggleMenuItem->setScale(0.5);
    
    //Ok按钮
    auto okMenuItem  = MenuItemImage::create(
                                             "ok-down.png",
                                             "ok-up.png",
                                             CC_CALLBACK_1(Setting::menuOkCallback, this));
    
    okMenuItem->setPosition(480,120);
    okMenuItem->setScale(0.5);
    //按钮菜单
    auto mu = Menu::create(soundToggleMenuItem,musicToggleMenuItem,okMenuItem,NULL);
    mu->setPosition(Vec2::ZERO);
    addChild(mu);
    return true;
}

void Setting::onEnter(){
    Layer::onEnter();
}

void Setting::onEnterTransitionDidFinish(){
//    播放音乐代码
//    SimpleAudioEngine::getInstance()->playBackgroundMusic("",true);
//    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}
//回调函数,实现音乐控制
void Setting::menuSoundToggleCallback(Ref* pSender){

}

void Setting::menuMusicToggleCallback(Ref* pSender){
    
}
//回调函数,返回主菜单
void Setting::menuOkCallback(Ref* pSender){
    Director::getInstance()->popScene();
}
