#include "GameScore.h"

GameScore* GameScore::createScore()
{
	auto score = new GameScore;
	score->initScore();
	score->setScale(0.5);
	return score;
}

void GameScore::initScore()
{
	auto bg  = Sprite::create("blood_bg.png");
	addChild(bg);
	_score = 0;
	_speed=0.02;
	_addPre = 20;
	_levelNum = 0;

	progress = ProgressTimer::create(Sprite::create("blood.png"));
	progress->setType(ProgressTimer::Type::BAR);
	progress->setPercentage(100);
	progress->setMidpoint(ccp(0,0));
	progress->setBarChangeRate(ccp(1,0));
	addChild(progress);

	_scoreLabel = LabelBMFont::create("0", "fonts/font-issue1343.fnt");
	this->addChild(_scoreLabel);

	_level = Node::create();
	auto lev = Sprite::create("level.png");
	_level->addChild(lev,0,1);
	auto lab = LabelBMFont::create("0", "fonts/font-issue1343.fnt");
	lab->setPosition(lev->getContentSize().width/2+50,10);
	lab->setScale(1.5);
	_level->addChild(lab,1,2);
	this->addChild(_level);
	_level->setVisible(false);
}

void GameScore::callBack()
{
	if(callBackFunc)
		callBackFunc();
}

void GameScore::setScore(int score)
{
	_score = score;
	int num = _score/20;
	if( num>20 ) num = 20;
	progress->stopAllActions();
	int pro = progress->getPercentage()+_addPre - num*0.5;
	if( pro > 100 ) pro = 100;
	char string[12] = {0};
	sprintf(string, "%d", score);

	_scoreLabel->setString(string);
	progress->setPercentage(pro);

	auto to1 = Sequence::create(ProgressTo::create(_speed*pro, 0),CallFunc::create(CC_CALLBACK_0(GameScore::callBack,this)),nullptr);
	progress->runAction(to1);
	setLevel();
}

void GameScore::setLevel()
{
	int num = _score/20;
	if( num > _levelNum )
	{
		_levelNum = _score/20;
		auto lab = static_cast<LabelBMFont*>(_level->getChildByTag(2));
		char string[12] = {0};
		sprintf(string, "%d", _levelNum);
		lab->setString(string);
		_level->setPosition(ccp(0,0));
		_level->setVisible(true);
		_level->runAction(Sequence::create(MoveBy::create(0.7,ccp(0,200)),Hide::create(),nullptr));
	}
}

void GameScore::onReset()
{
	_score = 0;
	_speed=0.02;
	_addPre = 20;
	_levelNum = 0;

	progress->stopAllActions();
	progress->setPercentage(100);
	auto to1 = Sequence::create(ProgressTo::create(_speed*100, 0),CallFunc::create(CC_CALLBACK_0(GameScore::callBack,this)),nullptr);
	progress->runAction( to1);
	char string[12] = {0};
	sprintf(string, "%d", 0);
	_scoreLabel->setString(string);
}