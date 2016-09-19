#include"BoardBG.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************BoardDecoration****************************************************/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BoardDecoration*BoardDecoration::create(int ID)
{
	//Sprite *sprite = new (std::nothrow) Sprite();
	//if (sprite && sprite->initWithFile(filename))
	//{
	//	sprite->autorelease();
	//	return sprite;
	//}
	//CC_SAFE_DELETE(sprite);
	//return nullptr;
	auto decoration = new (std::nothrow)BoardDecoration();
	switch (ID)
	{
	case 0:
	{
		auto sprite = Sprite::create("ChessBoard/decorations/5.png");
		decoration->addChild(sprite);
		return decoration;
	}
		break;
	case 1:
	{
		auto sprite = Sprite::create("ChessBoard/decorations/6.png");
		decoration->addChild(sprite);
		return decoration;
	}
		break;
	case 2:
	{
		auto sprite = Sprite::create("ChessBoard/decorations/7.png");
		decoration->addChild(sprite);
		return decoration;
	}
		break;
	case 3:
	{
		auto sprite = Sprite::create("ChessBoard/decorations/8.png");
		decoration->addChild(sprite);
		return decoration;
	}
		break;
	default:
		break;
	}
	CC_SAFE_DELETE(decoration);
	return nullptr;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*********************************************************BoardBG*********************************************************/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BoardBG::onEnter()
{
	Node::onEnter();
	auto s = Size(1024, 768);
	auto a = Sprite::create("ChessBoard/bg/board2.jpg");

	a->setPosition(0, 0);
	addChild(a);
	_curDecoration = 0;
	addDecoration(0,-437,-300);
	addDecoration(1, -437, 300);
	addDecoration(2, 437,  300);
	addDecoration(3, 437, -300);
}

bool BoardBG::addDecoration(int decorationID,float X,float Y)
{	

	if (_curDecoration == BOARD_DECORATIONS_MAXSIZE)
		return false;
	_decoration[_curDecoration] = BoardDecoration::create(decorationID);
	
	if (!_decoration[_curDecoration])
		return false;
	_decoration[_curDecoration]->setPosition(Vec2(X,Y));
	addChild(_decoration[_curDecoration++]);
	return true;
}

BoardDecoration* BoardBG::getDecoration(int DecorationID)
{
	return _decoration[DecorationID];
}

