#include<TouchDemoScene.h>

USING_NS_CC;

Scene* TouchDemo::createScene()
{
    auto scene = Scene::create();
    auto layer = TouchDemo::create();
    scene->addChild(layer);
    return scene;
    
}

bool TouchDemo::init(){
    if(!Layer::init()){
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    

    //贴图的纹理图片宽高必须是2的n次幂，128x128
    auto bg = Sprite::create("BackgroundTile.png", Rect(0, 0, visibleSize.width, visibleSize.height));
    //贴图的纹理参数，水平重复平铺，垂直重复平铺
    Texture2D::TexParams tp = {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT};
    bg->getTexture()->setTexParameters(tp);
    bg->setPosition(origin + Vec2(visibleSize.width/2, visibleSize.height/2));
    //this->addChild(bg);
    
    auto listener = EventListenerTouchOneByOne::create();//设置单点监听器
    listener->setSwallowTouches(false);//触摸重叠层时不冲突
    //回调函数
    listener->onTouchBegan = CC_CALLBACK_2(TouchDemo::onTouchBeganCallback, this);
    listener->onTouchMoved = CC_CALLBACK_2(TouchDemo::onTouchMovedCallback, this);
    listener->onTouchEnded = CC_CALLBACK_2(TouchDemo::onTouchEndedCallback, this);
    EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();

    //添加盒子A
    auto ball = Sprite::create("Ball.png");
    ball->setPosition(origin+Vec2(visibleSize.width/2, visibleSize.height/2) + Vec2(-120, 120));
    ball->setTag(1);
    this->addChild(ball);
    //注册监听器，绑定layer层。第二次listener要调用clone函数，否则会报冲突
    eventDispatcher->addEventListenerWithSceneGraphPriority(listener,getChildByTag(1));
    //添加粒子特效
    ParticleSystem* particleSystem = ParticleMeteor::create();
    particleSystem->setPosition(ball->getPosition());
    addChild(particleSystem);
    log("Fire");
    return true;
}
bool TouchDemo::onTouchBeganCallback(Touch* touch,Event* event){
    
    auto target = static_cast<Sprite*>(event->getCurrentTarget());//获取目标对象
    Point locationInNode = target->convertToNodeSpace(touch->getLocation());//手指按的坐标
    Size s = target->getContentSize();//目标尺寸
    Rect rect = Rect(0,0,s.width,s.height);//目标精灵矩阵
    //如果目标矩阵包含手指按的地方，则runAction
    if(rect.containsPoint(locationInNode)){
        log("spritex = %f, y = %f ", locationInNode.x, locationInNode.y);
        log("spritetag = %d", target->getTag());
        target->runAction(ScaleTo::create(0.06f,1.06f));
    }
    
    return true;
}

void TouchDemo::onTouchMovedCallback(Touch* touch, Event* event){
    auto target = static_cast<Sprite*>(event->getCurrentTarget());
    target->setPosition(target->getPosition()+ touch->getDelta());
}
void TouchDemo::onTouchEndedCallback(Touch* touch, Event* event){
    
    auto target = static_cast<Sprite*>(event->getCurrentTarget());
    Point locationInNode = target->convertToNodeSpace(touch->getLocation());
    Size s = target->getContentSize();
    Rect rect = Rect(0, 0, s.width, s.height);
    //点击范围判断检测
    if(rect.containsPoint(locationInNode))
    {
        log("spritex = %f, y = %f ", locationInNode.x, locationInNode.y);
        log("spritetag = %d", target->getTag());
        target->runAction(ScaleTo::create(0.06f,1.0f));
    }

}
//销毁监听器
void TouchDemo::onExit(){
    Layer::onExit();
    log("onexit");
    Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
}
