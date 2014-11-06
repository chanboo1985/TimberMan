#ifndef __TREE_LAYER_H__
#define __TREE_LAYER_H__
#include <cocos2d.h>
#include "TreeNode.h"
USING_NS_CC;
class TreeModel : public Layer
{
public:
	static TreeModel* getInstance();

	TreeNode* getTreeHeadNode();

	TreeNode* deleteTreeHeadNode();

	void initTree();

	TreeBranchDirection getFirstBranch();

	void onReset();
private:
	void createTreeModel();

	void update(float time);

	TreeBranchDirection getBranch();

	TreeBranchDirection getAgainBranch();

	Node* treeBody;

	Vector<TreeNode*> treeQueue;

	Vector<TreeNode*> treeCache;

	static TreeModel* _layer;
};

#endif