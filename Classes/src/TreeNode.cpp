#include "TreeNode.h"

TreeNode* TreeNode::createNode()
{
	auto node = new TreeNode;
	node->initTree();
	return node;
}

void TreeNode::initTree()
{
	Sprite* body = Sprite::create("body.jpg");
	this->addChild(body,0,1);
	Sprite* branch = Sprite::create("branch.png");
	this->addChild(branch,1,2);
	this->setContentSize(Size(body->getContentSize().width,body->getContentSize().height));
}

void TreeNode::setBranch(TreeBranchDirection enums)
{
	enumBranch = enums;
	auto body = this->getChildByTag(1);
	auto branch = this->getChildByTag(2);
	branch->setVisible(enums != DEFINE);
	if (enums == DEFINE)
	{
		return;
	}
	if (enums == RIGHT)
	{
		branch->setScaleX(1);
		branch->setPositionX(body->getContentSize().width);
	} 
	else
	{
		branch->setScaleX(-1);
		branch->setPositionX(-body->getContentSize().width);
	}
}

TreeBranchDirection TreeNode::getHasBranch()
{
	return enumBranch;
}