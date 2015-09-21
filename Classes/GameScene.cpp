#include "GameScene.h"
#include "Definitions.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    planet = Sprite::create("res/planet.png");
    planet->setPosition(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y);
    planet->setScale(0.07);
    this->addChild(planet, 2);

    auto rotationPoint = Node::create();
    rotationPoint->setPosition(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y);
    this->addChild(rotationPoint, 2);
    
    spaceShip = Sprite::create("res/spaceship.png");
   
    spaceShip->setPosition(0, INIT_SPACESHIP_ORBIT);
    spaceShip->setScale(0.03);
    spaceShip->setAnchorPoint(Vec2(0.5, 0.5));
    spaceShip->setRotation(90);
    
    rotationPoint->addChild(spaceShip);
    
    auto rotateBy = RotateBy::create(5.0f, 360.0f);
    rotationPoint->runAction(RepeatForever::create(rotateBy));
    
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    laser = DrawNode::create();
    laser->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    laser->drawSegment(Vec2(0, 0), Vec2(spaceShip->getPosition().x - 7, spaceShip->getPosition().y - 10), 5.0, cocos2d::Color4F(100, 0, 0, 1));
    this->addChild(laser);
    laser->runAction(RepeatForever::create(RotateBy::create(5.0f, 360.0f)));
    
    spaceShip->runAction(RepeatForever::create(MoveTo::create(0.7, Vec2(spaceShip->getPosition().x - 10, spaceShip->getPosition().y - 10))));
    
    // make this an action
    //    log("%f %f", spaceShip->getPosition().x, spaceShip->getPosition().y);
    
    this->scheduleUpdate();
    return true;
}
void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event){
    if (keyCode == EventKeyboard::KeyCode::KEY_SPACE) {
        spaceShip->runAction(MoveTo::create(0.5, Vec2(spaceShip->getPosition().x + 10, spaceShip->getPosition().y + 10)));
    }
    drawComets();
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event){
    if (keyCode == EventKeyboard::KeyCode::KEY_SPACE) {
        spaceShip->runAction(MoveTo::create(0.5, Vec2(spaceShip->getPosition().x + 10, spaceShip->getPosition().y + 10)));
        
    }
}

void GameScene::drawComets(){
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    // rd - random direction(left or right side)
    int rx, ry, rd;
    rd = RandomHelper::random_int(0, 1);
    if(rd){
        //left side
        rx = RandomHelper::random_int((int)origin.x, 30);
        ry = RandomHelper::random_int((int)origin.y, 30);
    }else{
        //right side
        rx = RandomHelper::random_int((int)(visibleSize.width - rx) - 20, (int)(visibleSize.width - rx));
        ry = RandomHelper::random_int((int)(visibleSize.height - ry) - 20, (int)(visibleSize.height - ry));
    }
    //int rx = RandomHelper::random_int(0, INIT_SPACESHIP_ORBIT+100);
    //int ry = RandomHelper::random_int(0, INIT_SPACESHIP_ORBIT+100);
    log("%d %d",rx, ry);
    Comet = DrawNode::create();
    Comet->drawDot(Vec2(rx, ry), 10, Color4F(100,0,0,1));
    this->addChild(Comet);
    
    Comet->runAction(RepeatForever::create(MoveTo::create(3.0f, Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y))));
    
}

void GameScene::update(float dt){
    laser->clear();
    laser->drawSegment(Vec2(0, 0), Vec2(spaceShip->getPosition().x - 5, spaceShip->getPosition().y - 10), 5.0, cocos2d::Color4F(0, 100, 30, 0.8));
}