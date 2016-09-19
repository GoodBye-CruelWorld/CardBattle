#ifndef OUTLINE_H
#define OUTLINE_H
#include<cocos2d.h>

namespace cocos2d {
	class Animate3D;
	class Sprite3D;
	class Delay;
	class Ray;
	class DrawNode3D;
	class GLProgramState;
	class GLProgram;
}
USING_NS_CC;
class EffectSprite3D;

class Effect3D : public cocos2d::Ref
{
public:
	virtual void draw(const cocos2d::Mat4 &transform) = 0;
	virtual void setTarget(EffectSprite3D *sprite) = 0;
protected:
	Effect3D() : _glProgramState(nullptr) {}
	virtual ~Effect3D()
	{
		CC_SAFE_RELEASE(_glProgramState);
	}
protected:
	cocos2d::GLProgramState* _glProgramState;
};

class Effect3DOutline : public Effect3D
{
public:
	static Effect3DOutline* create();

	void setOutlineColor(const cocos2d::Vec3& color);
	void setOutlineOpacity(float opacity);
	void setOutlineWidth(float width);

	virtual void draw(const cocos2d::Mat4 &transform) override;
	virtual void setTarget(EffectSprite3D *sprite) override;
protected:

	Effect3DOutline();
	virtual ~Effect3DOutline();

	bool init();

	cocos2d::Vec3 _outlineColor;
	float _outlineWidth;
	float _outlineOpacity;
	//weak reference
	EffectSprite3D* _sprite;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	cocos2d::EventListenerCustom* _backToForegroundListener;
#endif

protected:
	static const std::string _vertShaderFile;
	static const std::string _fragShaderFile;
	static const std::string _keyInGLProgramCache;

	static const std::string _vertSkinnedShaderFile;
	static const std::string _fragSkinnedShaderFile;
	static const std::string _keySkinnedInGLProgramCache;

	static cocos2d::GLProgram* getOrCreateProgram(bool isSkinned = false);
};

class EffectSprite3D : public cocos2d::Sprite3D
{
public:
	static EffectSprite3D* createFromObjFileAndTexture(const std::string& objFilePath, const std::string& textureFilePath);
	static EffectSprite3D* create(const std::string& path);

	void setEffect3D(Effect3D* effect);
	void addEffect(Effect3DOutline* effect, ssize_t order);
	virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;
protected:
	EffectSprite3D();
	virtual ~EffectSprite3D();

	std::vector<std::tuple<ssize_t, Effect3D*, cocos2d::CustomCommand>> _effects;
	Effect3D* _defaultEffect;
	cocos2d::CustomCommand _command;
};

#endif