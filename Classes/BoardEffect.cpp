#include"BoardEffect.h"

void BoardEffect::onEnter()
{
	Node::onEnter();
}


void BoardEffect::addEffect(int effectID, float delay, float duration, float positionX, float positionY, float positionZ)
{
	addEffect(effectID, this,delay,duration,positionX,positionY,positionZ);
}


void BoardEffect::addEffect(int effectID, Node * target, float delay,float duration, float positionX, float positionY, float positionZ)
{
	
	switch (effectID)
	{
	case 0:
	{//粒子效果
		auto emitter = ParticleFlower::create();  //花效果，可换成其他ParticleFire，ParticleExplosion等等
		emitter->setTexture(Director::getInstance()->getTextureCache()->addImage("effects/particles/stars.png"));//设置贴图
		emitter->setStartColor(Color4F(0.1, 0.5, 0.5, 0.5));
		emitter->setEndColor(Color4F(0.7, 0.1, 0.1, 0.2));
		
		emitter->setPosition3D(Vec3(positionX, positionY, positionZ));
		target->addChild(emitter);
		if (duration == DEFAULT_DURATION)
			emitter->runAction(Sequence::create(DelayTime::create(delay),ScaleTo::create(2, 3.0f), FadeOut::create(1.f), CallFunc::create(CC_CALLBACK_0(BoardEffect::endCallback, this, emitter)), NULL));
		else
			emitter->runAction(Sequence::create(DelayTime::create(delay), ScaleTo::create(duration*2.f / 3.f, 3.0f), /*淡出*/FadeOut::create(duration / 3.f), CallFunc::create(CC_CALLBACK_0(BoardEffect::endCallback, this, emitter)), NULL));
	}
		break;
	case 1:
	{//网格震动效果//未实现
		CCActionInterval* shaky3D = CCShaky3D::create(5, CCSize(10, 10), 15, false);  

		Size visibleSize = Size(400,400);
		Rect gridRect = Rect(visibleSize.width * 0.2,
			visibleSize.height * 0.2,
			visibleSize.width * 0.6,
			visibleSize.height * 0.6);
		auto _gridNodeTarget = NodeGrid::create(gridRect);
		_gridNodeTarget->setPosition(0, 0);
		target->addChild(_gridNodeTarget);
		_gridNodeTarget->runAction(shaky3D);

		auto s22 = Sprite::create("ChessBoard/decorations/1.png");
		s22->setPosition(2, 2);
		_gridNodeTarget->addChild(s22, 0);
		//s->setPosition(VisibleRect::center());
	}
		break;
	case 2:
	{	//上下震动
	
		target->runAction(Sequence::create(DelayTime::create(delay), JumpBy::create(duration ? duration : 1, Vec2(0, 0), 15, 100), NULL));
		
	}
		break;
	case 3:
	{	//碎片


	}
		break;
	case 4:
	{
		Animation *animation = Animation::create();
		auto node = Sprite::create();
		for (int i = 0; i < 4; i++)
		{
			char szName[50] = { 0 };
			sprintf(szName, "effects/png/%d.png", i);
			animation->addSpriteFrameWithFile(szName);
		}
		// should last 2.8 seconds. And there are 14 frames.
		animation->setDelayPerUnit(0.2f / 4.0f);
		animation->setRestoreOriginalFrame(true);

		auto action = Animate::create(animation);
		action->retain();
		node->runAction(Sequence::create(
			DelayTime::create(delay),
			action,
			CallFunc::create(CC_CALLBACK_0(Node::removeFromParent, node)),
			NULL));
		node->setScale(0.7);
		target->addChild(node);
	}
	default:
		break;
	}

}


void BoardEffect::endCallback(Node *sender)
{
	sender->removeFromParentAndCleanup(true);
}

