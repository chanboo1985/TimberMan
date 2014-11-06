#ifndef __GAME_DATA_H__
#define __GAME_DATA_H__
#include <cocos2d.h>
USING_NS_CC;
class GameScore : public Layer
{
public:
	static GameScore* createScore();

	void initScore();

	std::function<void()> callBackFunc;

	void setScore(int score);

	void onReset();

private:
	Sprite* _blood;
	int _score;
	float _speed;
	int _addPre;
	int _levelNum;
	Node* _level;
	LabelBMFont* _scoreLabel;
	ProgressTimer* progress;
	
	void callBack();

	void setLevel();
};

#endif