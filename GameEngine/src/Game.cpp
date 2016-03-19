#include <sb6.h>
#include <sb6ktx.h>
#include <math.h>
#include <assert.h>

#include "DebugOut.h"
#include "Game.h"
#include "TextureManager.h"
#include "InputMan.h"
#include "Camera.h"
#include "GameObjectMan.h"
#include "Anim.h"
#include "Teddy.h"
#include "Skeleton.h"
#include "AnimationManager.h"
#include "Humanoid.h"
// Global:  todo make a singleton
char buff[256];

// -->  TODO get rid of the projection, move to the camera
// todo get rid of globals
Camera *pCam = 0;
//extern GameObject *pFirstBone;

//-----------------------------------------------------------------------------
//  Game::Game()
//		Game Engine Constructor
//-----------------------------------------------------------------------------
Game::Game( const char* windowName, const int Width,const int Height)
	:Engine( windowName, Width, Height)
{
	this->globalTimer.tic();
	this->intervalTimer.tic();
}

//-----------------------------------------------------------------------------
// Game::Initialize()
//		Allows the engine to perform any initialization it needs to before 
//      starting to run.  This is where it can query for any required services 
//      and load any non-graphic related content. 
//-----------------------------------------------------------------------------
void Game::Initialize()
{
   // don't worry we will use this area
	InputMan::Create();
	
}

//-----------------------------------------------------------------------------
// Game::LoadContent()
//		Allows you to load all content needed for your engine,
//	    such as objects, graphics, etc.
//-----------------------------------------------------------------------------
void Game::LoadContent()
{
		// Camera setup
		pCam = new Camera( CameraName::CAMERA_0 );
		pCam->setViewport(0, 0, (int)this->screenWidth, (int)this->screenHeight);
		pCam->setPerspective( 35.0f, (this->screenWidth/this->screenHeight), 1.0f, 500.0f);
		//pCam->setOrientAndPosition( Vect(0.0f,1.0f,1.0f), Vect(40.0f,0.0f,0.0f), Vect(40.0f,0.0f,400.0f) );
		pCam->setOrientAndPosition( Vect(0.0f, 0.0f,1.0f), Vect(0.0f,0.0f,10.0f), Vect(180.0f,0.0f,90.0f) );
	//	pCam->setOrientAndPosition( Vect(0.0f, 0.0f,1.0f), Vect(0.0f,0.0f,4.0f), Vect(20.0f,0.0f,10.0f) );

		pCam->updateCamera();

	// Textures
		TextureMan::addTexture("Rocks.tga", TextureName::ROCKS );
		TextureMan::addTexture("Stone.tga", TextureName::STONES );
		TextureMan::addTexture("RedBrick.tga", TextureName::RED_BRICK );
		TextureMan::addTexture("Duckweed.tga", TextureName::DUCKWEED );
		
			Humanoid *human= new Humanoid();
			Teddy	*b= new Teddy();

		b->ReadAnimationData("teddy2.bp");
		human->ReadAnimationData("humantest2.bp");
		
		human->SetAnimationData();
		b->SetAnimationData();
		
		
		
		human->SetAnimationHierarchy();
		b->SetAnimationHierarchy();
		b->SetAnimationPose();
	
		
		//b->ProcessAnimation(Time(TIME_ZERO));
		
		
		
		
	
		
		//human->ProcessAnimation(Time(TIME_ZERO));
		
	
		
		AnimationManager::GetInstance()->AddSkeleton(human);
	AnimationManager::GetInstance()->AddSkeleton(b);
		
}


//-----------------------------------------------------------------------------
// Game::Update()
//      Called once per frame, update data, tranformations, etc
//      Use this function to control process order
//      Input, AI, Physics, Animation, and Graphics
//-----------------------------------------------------------------------------
//static Time tCurrent(TIME_ZERO);

void Game::Update(float )
{
	
	// Mark our end time.
	this->intervalTimer.toc();
	this->intervalTimer.tic();

	// Update the camera
	pCam->updateCamera();

	// Game objects
	GameObjectMan::Update( this->globalTimer.toc() );

	AnimationManager::GetInstance()->ProcessAnimation();
	
	Keyboard *pKey = InputMan::GetKeyboard();
	InputMan::Event(pKey);
	


}

//-----------------------------------------------------------------------------
// Game::Draw()
//		This function is called once per frame
//	    Use this for draw graphics to the screen.
//      Only do rendering here
//-----------------------------------------------------------------------------
void Game::Draw()
{
	// draw all objects
	GameObjectMan::Draw();
}



//-----------------------------------------------------------------------------
// Game::UnLoadContent()
//       unload content (resources loaded above)
//       unload all content that was loaded before the Engine Loop started
//-----------------------------------------------------------------------------
void Game::UnLoadContent()
{
	// todo fix this.
}


//------------------------------------------------------------------
// Game::ClearBufferFunc()
// Allows user to change the way the clear buffer function works
//------------------------------------------------------------------
void Game::ClearBufferFunc()
{
	const GLfloat blue[] = { 0.4f, 0.4f, 0.8f, 1.0f };
    const GLfloat one = 1.0f;

    glViewport(0, 0, info.windowWidth, info.windowHeight);
    glClearBufferfv(GL_COLOR, 0, blue);
    glClearBufferfv(GL_DEPTH, 0, &one);
}
