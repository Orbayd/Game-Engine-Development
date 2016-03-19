#include <assert.h>
#include "InputMan.h"
#include "AnimationManager.h"
#include "Skeleton.h"
InputMan *InputMan::pInputMan = 0;

void InputMan::Create( )
{
	InputMan::privCreate( );
}

InputMan::InputMan( )
{
	this->pKeyboard = new Keyboard(  );
	assert(this->pKeyboard);
}

void InputMan::privCreate(   )
{
	InputMan::pInputMan = new InputMan(  );
}

InputMan::~InputMan()
{
	delete this->pKeyboard;
}

Keyboard *InputMan::GetKeyboard()
{
	InputMan *pInputMan = InputMan::privInstance();
	return pInputMan->pKeyboard;
}

InputMan *InputMan::privInstance()
{
	assert( pInputMan );
	return pInputMan;
}
void InputMan::Event(Keyboard * pKey)
{


	if( pKey->GetKeyState( AZUL_KEY::KEY_A ) == true)
	{
		AnimationManager::GetInstance()->ChangeAnimationSpeed(1.0005f);
	}
	if( pKey->GetKeyState( AZUL_KEY::KEY_S ) == true)
	{
		AnimationManager::GetInstance()->ChangeAnimationSpeed(0.99995f);
	}

	if( pKey->GetKeyState( AZUL_KEY::KEY_1 ) == true)
	{
		AnimationManager::GetInstance()->ChangeAnimation(SkeletonType::TEDDY);
	}
	if( pKey->GetKeyState( AZUL_KEY::KEY_2 ) == true)
	{
		AnimationManager::GetInstance()->ChangeAnimation(SkeletonType::HUMAN);
	}
	if( pKey->GetKeyState( AZUL_KEY::KEY_Q) == true)
	{
		AnimationManager::GetInstance()->Rewind();
	}
	if( pKey->GetKeyState( AZUL_KEY::KEY_W) == true)
	{
		AnimationManager::GetInstance()->Start();
	}
		if( pKey->GetKeyState( AZUL_KEY::KEY_E) == true)
	{
		AnimationManager::GetInstance()->Pause();
	}

	if( pKey->GetKeyState( AZUL_KEY::KEY_Z) == true)
	{
		AnimationManager::GetInstance()->Delete(SkeletonType::HUMAN);
	}

}

