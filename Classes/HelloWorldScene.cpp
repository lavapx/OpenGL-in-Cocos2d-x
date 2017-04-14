#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;


Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...
	this->createGL();
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}

void HelloWorld::createGL()
{

	glProgram = GLProgram::createWithFilenames("Shaders/BasicShader.vert", "Shaders/BasicShader.frag");

	auto glProgramState = GLProgramState::create(glProgram);
	setGLProgramState(glProgramState);

	CHECK_GL_ERROR_DEBUG();

	auto size = Director::getInstance()->getWinSize();

	GLfloat vertices[] = {

		90,30,
		size.width - 90, 30,
		size.width / 2, size.width - 180

	};
	
	GLfloat colors[] = {

		1, 0, 0, 1,
		0, 1, 0, 1,
		0, 0, 1, 1

	};

	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_POLYGON_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glGenVertexArrays(1, &vao);

	glGenBuffers(1, &vbo1);
	glGenBuffers(1, &vbo2);


	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo1);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);

	glBindBuffer(GL_ARRAY_BUFFER, vbo2);

	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_COLOR);

	glBindVertexArray(0);


	CHECK_GL_ERROR_DEBUG();

}


void HelloWorld::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t parentFlags)
{
	Layer::draw(renderer, transform, parentFlags);
	CustomCommand *_customCommand = new CustomCommand();
	_customCommand->init(_globalZOrder, transform, parentFlags);
	_customCommand->func = CC_CALLBACK_0(HelloWorld::onDraw, this, transform, parentFlags);
	Director::getInstance()->getRenderer()->addCommand(_customCommand);

}

void HelloWorld::onDraw(const Mat4 &transform, uint32_t flags)
{
	
	getGLProgramState()->applyGLProgram(transform);

	glBindVertexArray(vao);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 3);

	glBindVertexArray(0);

	CHECK_GL_ERROR_DEBUG();
}