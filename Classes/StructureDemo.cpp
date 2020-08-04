#include "StructureDemo.h"

USING_NS_CC;

Scene* Structure::createScene(){
    auto scene = Scene::create();
    auto layer = Structure::create();
    scene->addChild(layer);
    return scene;
}

bool Structure::init(){
    if(!Layer::init()){
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //创建菜单按钮
    auto item = MenuItemImage::create(
                                      "go-down.png",
                                      "go-up.png",
                                      CC_CALLBACK_1(Structure::menuCloseCallback,this));
    item->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    
    auto menu = Menu::create(item,NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu,1);
    //创建__Array* 类型的list成员变量
    this->list = __Array::createWithCapacity(MAX_COUNT);//设置数组容量
    this->list->retain();//保留list的内存，因为list是autorelease的，init结束会释放。
    for(int i=0;i<MAX_COUNT;++i){
        Sprite* sprite = Sprite::create("Ball.png");//循环创建精灵对象
        this->list->addObject(sprite);//将精灵添加进list
    }
    return true;
}
void Structure::menuCloseCallback(Ref* pSender){
    Ref* obj = nullptr;
    log("list->count() = %zd",this->list->count());
    Size visibleSize = Director::getInstance()->getVisibleSize();
    CCARRAY_FOREACH(this->list, obj){//宏命令遍历list
        Sprite* sprite = (Sprite*)obj;
        int x = CCRANDOM_0_1()*visibleSize.width;
        int y = CCRANDOM_0_1()*visibleSize.height;
        
        sprite->setPosition(Vec2(x,y));
        this->removeChild(sprite);
        this->addChild(sprite);
    }
}
Structure::~Structure(){
    //1.移除list所以对象
    this->list->removeAllObjects();
    //2.安全释放list对象
    CC_SAFE_RELEASE_NULL(this->list);
}
