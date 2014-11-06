#include "HelloWorldScene.h"
#include "src/TreeModel.h"
#include "src/GameOver.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	_score = 0;

	bg1 = Sprite::create("bg1.jpg");
	this->addChild(bg1);
	bg1->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	bg2 = Sprite::create("bg2.jpg");
	this->addChild(bg2);
	bg2->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	bg2->setVisible(false);


	auto model = TreeModel::getInstance();
	model->setPosition(visibleSize.width/2,100);
	this->addChild(model);

	timber = Timber::createTimber();
	this->addChild(timber);
	timber->setPosition(visibleSize.width/2-timber->getContentSize().width/2-20,150);
	list = EventListenerTouchOneByOne::create();
	list->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegans,this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(list,this);
	list->setEnabled(false);

	score = GameScore::createScore();
	this->addChild(score);
	score->setPosition(visibleSize.width/2,visibleSize.height/2);
	score->callBackFunc = CC_CALLBACK_0(HelloWorld::menuCloseCallback,this);

	auto leftIcon = Sprite::create("left.png");
	auto rightIcon = Sprite::create("right.png");
	leftIcon->setScale(0.5);
	rightIcon->setScale(0.5);
	leftIcon->setPosition(leftIcon->getContentSize().width/2,50);
	rightIcon->setPosition(visibleSize.width-rightIcon->getContentSize().width/2,50);
	this->addChild(leftIcon);
	this->addChild(rightIcon);

	auto gameOver = GameOver::getInstance();
	this->addChild(gameOver);
	gameOver->callBackFun = CC_CALLBACK_0(HelloWorld::onRest,this);
	gameOver->setAnchorPoint(Point(0,0.5));
	gameOver->setVisible(false);
	gameOver->setPosition(visibleSize.width/2,visibleSize.height+gameOver->getContentSize().height/2);


	auto play = MenuItemImage::create(
		"play.png",
		"play.png",
		CC_CALLBACK_0(HelloWorld::playGame, this));
	play->setScale(0.5);
	menu = Menu::create(play, NULL);
	this->addChild(menu);
	menu->setPosition(visibleSize.width/2,play->getContentSize().height*2);


	logo = Sprite::create("logo.png");
	logo->setPosition(visibleSize.width/2,visibleSize.height/2+logo->getContentSize().height);
	this->addChild(logo);

	ParticleSystem* pl = ParticleSnow::create();
	pl->setTexture(Director::getInstance()->getTextureCache()->addImage("particle.png"));
	pl->setPosition(visibleSize.width/2,visibleSize.height);
	this->addChild(pl,10);
    
    return true;
}

bool HelloWorld::onTouchBegans(Touch *touch, Event *event)
{
	auto pos = touch->getLocation();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto model = TreeModel::getInstance();

	auto isRight = pos.x > visibleSize.width/2;
	timber->playAction(isRight ? RIGHT : LEFT);
	if(isRight)
	{
		timber->setPosition(visibleSize.width/2+timber->getContentSize().width/2+20,150);
	}
	else
	{
		timber->setPosition(visibleSize.width/2-timber->getContentSize().width/2-20,150);
	}

	if(getIsOver())
	{
		timber->setTimberDie();
		gameOver();
		return false;
	}

	auto dic = visibleSize.width*2;
	auto time = 0.5;
	auto tree = model->deleteTreeHeadNode();
	if( isRight )
	{
		tree->runAction(Spawn::create(RotateBy::create(time,-180),MoveBy::create(time,Point(-dic,0)),nullptr));
	}
	else
	{
		tree->runAction(Spawn::create(RotateBy::create(time,180),MoveBy::create(time,Point(dic,0)),nullptr));
	}

	_score++;
	score->setScore(_score);
	if(getIsOver())
	{
		timber->setTimberDie();
		gameOver();
	}

	return true;
}

bool HelloWorld::getIsOver()
{
	auto model = TreeModel::getInstance();

	if(model->getFirstBranch() == timber->getTimberDir()) return true;
	return false;
}


void HelloWorld::menuCloseCallback()
{
	if(!GameOver::getInstance()->isVisible())
	{
		gameOver();
	}
}

void HelloWorld::onRest()
{
	_score = 0;
	TreeModel::getInstance()->onReset();
	score->onReset();
	timber->onReset();
	list->setEnabled(true);
	auto isBgShow = (CCRANDOM_0_1()*10 < 5);
	bg1->setVisible(isBgShow);
	bg2->setVisible(!isBgShow);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	timber->setPosition(visibleSize.width/2-timber->getContentSize().width/2-20,150);
}

void HelloWorld::gameOver()
{
	list->setEnabled(false);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto gameOver = GameOver::getInstance();
	gameOver->setScore(_score);
	gameOver->setPositionY(visibleSize.height+gameOver->getContentSize().height/2);
	gameOver->setVisible(true);
	gameOver->runAction(MoveBy::create(0.5,Point(0,-gameOver->getContentSize().height)));
}

void HelloWorld::playGame()
{
	menu->removeFromParent();
	logo->removeFromParent();
	list->setEnabled(true);
	score->onReset();
}
