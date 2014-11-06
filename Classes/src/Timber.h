#ifndef __TIMBER_H__
#define __TIMBER_H__
#include <cocos2d.h>
#include "TreeModel.h"
USING_NS_CC;
class Timber : public Node
{
public:
	static Timber* createTimber();

	void initTimber();

	void playAction(TreeBranchDirection enums);

	void setTimberDie();

	TreeBranchDirection getTimberDir();

	void onReset();
private:
	Sprite* body;

	TreeBranchDirection dir;
};

#endif