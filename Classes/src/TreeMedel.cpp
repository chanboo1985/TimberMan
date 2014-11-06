#include "TreeModel.h"

TreeModel* TreeModel::_layer = nullptr;
TreeModel* TreeModel::getInstance()
{
	if (!_layer)
	{
		_layer = new TreeModel;
		_layer->initTree();
		_layer->setScale(0.5);
	}
	return _layer;
}

void TreeModel::initTree()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* base = Sprite::create("base.png");
	this->addChild(base);
	base->setPosition(3,base->getContentSize().height/2);

	treeBody = Node::create();
	this->addChild(treeBody);
	treeBody->setPositionY(base->getContentSize().height);
	createTreeModel();
	scheduleUpdate();
}

void TreeModel::createTreeModel()
{
	treeBody->removeAllChildren();
	treeQueue.clear();
	treeCache.clear();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	float posY = 0;
	bool isBase = true;
	while (visibleSize.height*2 > posY)
	{
		auto tree = TreeNode::createNode();
		tree->setBranch(getBranch());
		if (isBase)
		{
			posY += tree->getContentSize().height/2;
			isBase = false;
		} 
		else
		{
			posY += tree->getContentSize().height;
		}
		tree->setPositionY(posY);
		treeBody->addChild(tree);
		treeQueue.pushBack(tree);
	}
}

void TreeModel::update(float time)
{
	for (int idx = 1; idx < treeQueue.size(); idx++)
	{
		auto protree = treeQueue.at(idx - 1);
		auto tree = treeQueue.at(idx);
		tree->setPositionY(protree->getPositionY() + protree->getContentSize().height);
	}
}

TreeNode* TreeModel::deleteTreeHeadNode()
{
	auto tree = treeQueue.at(0);
	treeQueue.erase(0);
	treeCache.pushBack(tree);
	TreeNode* nextTree;
	if (treeCache.size() > 10)
	{
		nextTree = treeCache.at(0);
		treeBody->removeChild(nextTree);
		treeCache.erase(0);
		nextTree->setPositionX(0);
		nextTree->setRotation3D(Vertex3F(0,0,0));
	} 
	else
	{
		nextTree = TreeNode::createNode();
	}
	treeBody->addChild(nextTree);
	nextTree->setBranch(getBranch());
	treeQueue.pushBack(nextTree);
	treeBody->reorderChild(tree,treeBody->getChildrenCount() + 10);
	auto head = treeQueue.at(0);
	head->runAction(Sequence::create(MoveTo::create(0.06f,ccp(0,tree->getPositionY())),NULL));
	return tree;
}

TreeBranchDirection TreeModel::getBranch()
{
	auto isBranch = CCRANDOM_0_1()*10 < 7;
	if( treeQueue.size() == 0 )
		return DEFINE;
	if( !isBranch ) return DEFINE;
	auto protree = treeQueue.at(treeQueue.size()-1);
	switch (protree->getHasBranch())
	{
	case LEFT:
		return (CCRANDOM_0_1()*10 < 5) ? DEFINE : LEFT;
		break;
	case RIGHT:
		return (CCRANDOM_0_1()*10 < 5) ? DEFINE : RIGHT;
		break;
	case DEFINE:
		return getAgainBranch();
		break;
	default:
		return DEFINE;
		break;
	}
}

TreeBranchDirection TreeModel::getAgainBranch()
{
	if( treeQueue.size() < 2 )
		return DEFINE;
	auto protree = treeQueue.at(treeQueue.size()-2);
	switch (protree->getHasBranch())
	{
	case LEFT:
		return (CCRANDOM_0_1()*10 < 6) ? RIGHT : LEFT;
		break;
	case RIGHT:
		return (CCRANDOM_0_1()*10 < 6) ? LEFT : RIGHT;
		break;
	case DEFINE:
		return (CCRANDOM_0_1()*10 < 4) ? LEFT : RIGHT;
		break;
	default:
		return DEFINE;
		break;
	}
}

TreeBranchDirection TreeModel::getFirstBranch()
{
	return treeQueue.front()->getHasBranch();
}

void TreeModel::onReset()
{
	createTreeModel();
}

