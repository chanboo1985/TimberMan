#include "Timber.h"

Timber* Timber::createTimber()
{
	auto timber = new Timber;
	timber->initTimber();
	timber->setScale(0.5);
	return timber;
}

void Timber::initTimber()
{
	body = Sprite::create("role.png");
	this->addChild(body);

	auto aCahe = AnimationCache::getInstance();

	Vector<SpriteFrame*> aFrames(2);
	aFrames.pushBack(SpriteFrame::create("att_left.png",Rect(0,0,303,210)));
	aFrames.pushBack(SpriteFrame::create("role.png",Rect(0,0,196,257)));
	aCahe->addAnimation(Animation::createWithSpriteFrames(aFrames,0.1f),"left");

	aFrames.clear();
	aFrames.pushBack(SpriteFrame::create("att_right.png",Rect(0,0,303,210)));
	aFrames.pushBack(SpriteFrame::create("role.png",Rect(0,0,196,257)));
	aCahe->addAnimation(Animation::createWithSpriteFrames(aFrames,0.1f),"right");

	aFrames.clear();
	aFrames.pushBack(SpriteFrame::create("die.png",Rect(0,0,104,110)));
	aCahe->addAnimation(Animation::createWithSpriteFrames(aFrames,0.1f),"die");

	this->setContentSize(Size(body->getContentSize().width,body->getContentSize().height));
}

void Timber::playAction(TreeBranchDirection enums)
{
	auto aCahe = AnimationCache::getInstance();
	body->stopAllActions();
	switch (enums)
	{
	case LEFT:
		body->runAction(Animate::create(aCahe->getAnimation("left")));
		break;
	case RIGHT:
		body->runAction(Animate::create(aCahe->getAnimation("right")));
		break;
	}
	dir = enums;
}

void Timber::setTimberDie()
{
	auto aCahe = AnimationCache::getInstance();
	body->stopAllActions();
	body->runAction(Animate::create(aCahe->getAnimation("die")));
}

TreeBranchDirection Timber::getTimberDir()
{
	return dir;
}

void Timber::onReset()
{
	body->stopAllActions();
	body->setSpriteFrame(SpriteFrame::create("role.png",Rect(0,0,196,257)));
}