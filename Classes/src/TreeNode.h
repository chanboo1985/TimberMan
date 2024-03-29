#ifndef __TREE_NODE_H__
#define __TREE_NODE_H__
#include <cocos2d.h>
USING_NS_CC;

enum TreeBranchDirection{
	DEFINE,
	LEFT,
	RIGHT
};

class TreeNode : public Node
{
public:
	static TreeNode* createNode();

	void setBranch(TreeBranchDirection enums);

	TreeBranchDirection getHasBranch();
private:
	void initTree();

	TreeBranchDirection enumBranch;
};

#endif