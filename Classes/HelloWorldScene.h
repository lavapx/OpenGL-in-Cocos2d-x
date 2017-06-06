#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"


class HelloWorld : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	
	virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& parentTransform, uint32_t parentFlags) override;

	void onDraw(const cocos2d::Mat4 &transform, uint32_t flags);


	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	
	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);

private:

	void createGL();

	cocos2d::GLProgram* _glProgram;

	GLuint _program;
	GLuint _vbo1, _vbo2;
	GLuint _vao;
};

#endif // __HELLOWORLD_SCENE_H__
