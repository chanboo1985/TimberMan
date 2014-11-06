#ifndef __GAME_OVER_H__
#define __GAME_OVER_H__
#include <cocos2d.h>
USING_NS_CC;
using namespace std;
class GameOver : public Layer
{
public:
	static GameOver* getInstance();

	void setScore(int score);

	std::function<void()> callBackFun;

private:
	void onCallBack();

	void initLayer();

	Sprite* newScore;

	LabelBMFont* _newScore;

	LabelBMFont* _highestScore;

	static GameOver* _layer;
};

#endif