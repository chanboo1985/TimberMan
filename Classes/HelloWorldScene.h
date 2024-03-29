#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "src/Timber.h"
#include "src/GameScore.h"

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback();

	bool onTouchBegans(Touch *touch, Event *event);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	Timber* timber;
	GameScore* score;
	Menu* menu;
	int _score;
	Sprite* bg1;
	Sprite* bg2;
	Sprite* logo;
	EventListenerTouchOneByOne* list;
	bool getIsOver();
	void onRest();
	void gameOver();
	void playGame();
};

#endif // __HELLOWORLD_SCENE_H__
