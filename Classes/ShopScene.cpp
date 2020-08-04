#include "ShopScene.h"

USING_NS_CC;

Scene* ShopScene::createScene()
{
    auto scene = Scene::create();
    auto layer = ShopScene::create();
    scene->addChild(layer);
    return scene;
    
}

bool ShopScene::init(){
    if(!Layer::init()){
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    bg->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    
    this->addChild(bgLayer);
    this->addChild(shopLayer);
    bgLayer->addChild(bg);//背景是添加在bgLayer中
    shopLayer->addChild(shopBoard,2);//商品面板添加在shopLayer中
    shopLayer->addChild(shopBoard2,2);
    shopLayer->addChild(shopBoard3,2);
    shopBoard->setPosition(Vec2(shopLayer->getContentSize().width/2-100,shopLayer->getContentSize().height/2));
    shopBoard2->setPosition(Vec2(shopLayer->getContentSize().width/2+100,shopLayer->getContentSize().height/2));
    shopBoard3->setPosition(Vec2(shopLayer->getContentSize().width/2+300,shopLayer->getContentSize().height/2));
    shopBoard->addChild(BuyButton);
    shopBoard2->addChild(BuyButton2);
    shopBoard3->addChild(BuyButton3);
    BuyButton->setPosition(Vec2(shopBoard->getContentSize().width/2,shopBoard->getContentSize().height/6));
    BuyButton2->setPosition(Vec2(shopBoard->getContentSize().width/2,shopBoard->getContentSize().height/6));
    BuyButton3->setPosition(Vec2(shopBoard->getContentSize().width/2,shopBoard->getContentSize().height/6));
    shopBoard->setVisible(false);
    shopBoard2->setVisible(false);
    shopBoard3->setVisible(false);

    auto openMenuButtonOn  = MenuItemImage::create(
                                                   "open_menu.png",
                                                   "open_menu.png");
    auto openMenuButtonOff  = MenuItemImage::create(
                                                    "close_menu.png",
                                                    "close_menu.png");
    auto openMenuButton = MenuItemToggle::createWithCallback(CC_CALLBACK_1(ShopScene::openMenuButtonCallback, this),
                                                             openMenuButtonOn,
                                                             openMenuButtonOff,
                                                             NULL );
    
    auto listener = EventListenerTouchOneByOne::create();//设置单点监听器
    listener->setSwallowTouches(true);//触摸吞噬????????????????????????????????????
    listener->onTouchBegan = CC_CALLBACK_2(ShopScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(ShopScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(ShopScene::onTouchEnded, this);
    EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
    eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    shopButton->setPosition(Vec2(850,80));
    shopButton->setVisible(false);
    signInButton->setPosition(Vec2(850,80));
    signInButton->setVisible(false);
    cancelButton->setPosition(Director::getInstance()->convertToGL(Vec2(750,100)));
    openMenuButton->setPosition(Director::getInstance()->convertToGL(Vec2(850,580)));
    cancelButton->setVisible(false);
    returnButton->setPosition(visibleSize.width/2,visibleSize.height/7);
    auto mu = Menu::create(shopButton,cancelButton,returnButton,signInButton,openMenuButton,NULL);
    mu->setPosition(Vec2::ZERO);
    bgLayer->addChild(mu);

    return true;
}

bool ShopScene::onTouchBegan(Touch* touch, Event* event){
    log("点击");
    touchPoint = touch->getLocation();
    return true;
}

void ShopScene::onTouchMoved(Touch* touch, Event* event){
    log("%f",shopBoard->getPosition().x);
    shopBoard->setPosition(shopBoard->getPosition().x+touch->getDelta().x,shopBoard->getPosition().y);
    shopBoard2->setPosition(shopBoard2->getPosition().x+touch->getDelta().x,shopBoard2->getPosition().y);
    shopBoard3->setPosition(shopBoard3->getPosition().x+touch->getDelta().x,shopBoard3->getPosition().y);
}

void ShopScene::onTouchEnded(Touch* touch, Event* event){
    if(shopBoard->getPosition().x<120){//括号中判断边界
        Vec2 board1 = {120,shopBoard2->getPosition().y};
        Vec2 board2 = {320,shopBoard2->getPosition().y};
        Vec2 board3 = {520,shopBoard2->getPosition().y};
        shopBoard->runAction(MoveTo::create(0.3, board1));
        shopBoard2->runAction(MoveTo::create(0.3, board2));
        shopBoard3->runAction(MoveTo::create(0.3, board3));
    }else if(shopBoard3->getPosition().x>860){
        Vec2 board3 = {860,shopBoard2->getPosition().y};
        Vec2 board2 = {660,shopBoard2->getPosition().y};
        Vec2 board1 = {460,shopBoard2->getPosition().y};
        shopBoard->runAction(MoveTo::create(0.3, board1));
        shopBoard2->runAction(MoveTo::create(0.3, board2));
        shopBoard3->runAction(MoveTo::create(0.3, board3));
    }
}
//打开商店回调
void ShopScene::shopButtonCallback(Ref* pSender){
    log("打开商店");
    cancelButton->setVisible(true);
    shopLayer->setVisible(true);
    shopBoard->setVisible(true);
    shopBoard2->setVisible(true);
    shopBoard3->setVisible(true);
}
//关闭商店按钮回调
void ShopScene::cancelButtonCallback(Ref* pSender){
    log("关闭商店");
    cancelButton->setVisible(false);
    shopBoard->setVisible(false);
    shopBoard2->setVisible(false);
    shopBoard3->setVisible(false);
    
}
//返回按钮回调
void ShopScene::returnButtonCallback(Ref* pSender){
    log("返回");
    Director::getInstance()->popScene();
}
//签到按钮回调
void ShopScene::signInButtonCallback(Ref* pSender){
    log("签到");
}
//菜单开关按钮回调
void ShopScene::openMenuButtonCallback(Ref* pSender){
    log("move前商店的y坐标：%f",shopButton->getPosition().y);
    auto item = (MenuItemToggle*)pSender;
    if(1==item->getSelectedIndex()){//点击加号，展开菜单
        //log("打开菜单");
        shopButton->setVisible(true);
        shopButton->runAction(MoveTo::create(0.3, Vec2(850,300)));
        log("move时商店的y坐标：%f",shopButton->getPosition().y);
        signInButton->setVisible(true);
        signInButton->runAction(MoveTo::create(0.3, Vec2(850,200)));
    }
    if(0==item->getSelectedIndex()){//点击减号，收起菜单
        log("收起菜单");
        shopButton->runAction(MoveTo::create(0.3, Vec2(850,80)));
        signInButton->runAction(MoveTo::create(0.3, Vec2(850,80)));
        if(shopButton->getPosition().y<=90){
            shopButton->setVisible(false);
        }
        if(signInButton->getPosition().y<=90){
            signInButton->setVisible(false);
        }
    }
}

