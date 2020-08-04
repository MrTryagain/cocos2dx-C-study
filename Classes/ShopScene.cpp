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
    this->addChild(bg);
    this->addChild(shopBoard,2);
    this->addChild(shopBoard2,2);
    this->addChild(shopBoard3,2);
    shopBoard->setPosition(Vec2(visibleSize.width/2-100,visibleSize.height/2));
    shopBoard2->setPosition(Vec2(visibleSize.width/2+100,visibleSize.height/2));
    shopBoard3->setPosition(Vec2(visibleSize.width/2+300,visibleSize.height/2));
    shopBoard->addChild(BuyButton);
    shopBoard2->addChild(BuyButton2);
    shopBoard3->addChild(BuyButton3);
    BuyButton->setPosition(Vec2(shopBoard->getContentSize().width/2,shopBoard->getContentSize().height/6));
    BuyButton2->setPosition(Vec2(shopBoard->getContentSize().width/2,shopBoard->getContentSize().height/6));
    BuyButton3->setPosition(Vec2(shopBoard->getContentSize().width/2,shopBoard->getContentSize().height/6));
    shopBoard->setVisible(false);
    shopBoard2->setVisible(false);
    shopBoard3->setVisible(false);
    auto listener = EventListenerTouchOneByOne::create();//设置单点监听器
    listener->setSwallowTouches(true);//触摸重叠层时不冲突
    listener->onTouchBegan = CC_CALLBACK_2(ShopScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(ShopScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(ShopScene::onTouchEnded, this);
    EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
    eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    shopButton->setPosition(Director::getInstance()->convertToGL(Vec2(480,500)));
    shopButton->setScale(0.5);
    cancelButton->setPosition(Director::getInstance()->convertToGL(Vec2(750,100)));
    cancelButton->setVisible(false);
    auto mu = Menu::create(shopButton,cancelButton,NULL);
    mu->setPosition(Vec2::ZERO);
    this->addChild(mu);

    return true;
}

bool ShopScene::onTouchBegan(Touch* touch, Event* event){
    log("开始");
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

void ShopScene::shopButtonCallback(Ref* pSender){
    log("按钮");
    cancelButton->setVisible(true);
    shopBoard->setVisible(true);
    shopBoard2->setVisible(true);
    shopBoard3->setVisible(true);
}

void ShopScene::cancelButtonCallback(Ref* pSender){
    cancelButton->setVisible(false);
    shopBoard->setVisible(false);
    shopBoard2->setVisible(false);
    shopBoard3->setVisible(false);
    
}
