#include<cocos2d.h>

class ShopScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    //回调函数声明
    bool onTouchBegan(cocos2d::Touch* touch,cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch,cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch,cocos2d::Event* event);
    void shopButtonCallback(Ref* pSender);
    void cancelButtonCallback(Ref* pSender);
    void returnButtonCallback(Ref* pSender);
    void signInButtonCallback(Ref* pSender);
    void dailyButtonCallback(Ref* pSender);
    void openMenuButtonCallback(Ref* pSender);
    cocos2d::Layer* bgLayer = Layer::create();
    cocos2d::Layer* shopLayer = Layer::create();
    cocos2d::Sprite* bg = cocos2d::Sprite::create("fallbg.jpg");//背景精灵
    cocos2d::Sprite* shopBoard = cocos2d::Sprite::create("board.png");//商店面板精灵
        cocos2d::Sprite* shopBoard2 = cocos2d::Sprite::create("board.png");
        cocos2d::Sprite* shopBoard3 = cocos2d::Sprite::create("board.png");
    cocos2d::Sprite* BuyButton = cocos2d::Sprite::create("BuyButton.png");//确认购买精灵
        cocos2d::Sprite* BuyButton2 = cocos2d::Sprite::create("BuyButton.png");
        cocos2d::Sprite* BuyButton3 = cocos2d::Sprite::create("BuyButton.png");
    cocos2d::MenuItemImage* shopButton = cocos2d::MenuItemImage::create(//菜单按钮-打开商店
                                                      "shop.png",
                                                      "shop.png",
                                                      CC_CALLBACK_1(ShopScene::shopButtonCallback, this));
    cocos2d::MenuItemImage* cancelButton = cocos2d::MenuItemImage::create(//菜单按钮-关闭商店
                                                        "Cancel.png",
                                                        "Cancel.png",
                                                        CC_CALLBACK_1(ShopScene::cancelButtonCallback, this));
    cocos2d::MenuItemImage* returnButton = cocos2d::MenuItemImage::create(//返回按钮
                                                                "return.png",
                                                                "return.png",
                                                                CC_CALLBACK_1(ShopScene::returnButtonCallback, this));
    cocos2d::MenuItemImage* signInButton = cocos2d::MenuItemImage::create(//签到按钮
                                                        "sign_in_up.png",
                                                        "sign_in_down.png",
                                                        CC_CALLBACK_1(ShopScene::signInButtonCallback, this));


    //cocos2d::Layer* shopLayer = cocos2d::Layer::create();
    cocos2d::Point touchPoint = cocos2d::Vec2(0,0);
    float moveDistance = 0;
    CREATE_FUNC(ShopScene);

};


