#include <assert.h>
#include <math.h>

#include "PCSNode.h"
#include "MathEngine.h"
#include "GameObject.h"
#include "GraphicsObject.h"
#include "Anim.h"
#include "FrameBucket.h"
#include "MyGameObjAnim.h"



MyGameObjectAnim::MyGameObjectAnim( GraphicsObject  *graphicsObject )
	: GameObject(graphicsObject),
	local(IDENTITY),
	BoneOrientation(IDENTITY)
{
	this->dof.set(0.0f,0.0f,0.0f);
	this->up.set(0.0f,1.0f,0.0f);
	this->scale.set(1.0f,1.0f,1.0f);
	this->pos.set(0.0f,0.0f,0.0f);
}

MyGameObjectAnim::~MyGameObjectAnim()
{
}

void MyGameObjectAnim::setBoneOrientation( const Matrix &tmp )
{
	this->BoneOrientation = tmp;
}

Matrix MyGameObjectAnim::getBoneOrientation( void ) const
{
	return Matrix(this->BoneOrientation);
}

//GraphicsObject *GameObjectAnim::getGraphicsObject()
//{
//	return this->pGraphicsObject;
//}

Matrix &MyGameObjectAnim::getWorld()
{
	return this->world;
}

void MyGameObjectAnim::setIndex( int val )
{
	this->indexBoneArray = val;
}

void MyGameObjectAnim::update( Time  )
{
	
	// Get the parent world
	Matrix ParentWorld;

    GameObject *pBoneParent = (GameObject *) this->getParent();

	if( pBoneParent == 0 )
	{
		ParentWorld.set(IDENTITY);
	}
	else
	{
		ParentWorld = pBoneParent->getWorld();
	}

    // REMEMBER this is for Animation and hierachy, you need to handle models differently
	// Get the result bone array
	//Bone *bResult = pHead->pBone;     olde one

	Bone *bResult = tedy->getHeadFrameBucket()->pBone;

	Matrix T = Matrix( TRANS, bResult[indexBoneArray].T);
	Matrix S = Matrix( SCALE, bResult[indexBoneArray].S);
	Quat   Q = bResult[indexBoneArray].Q;

	// Isn't awesome that we can multiply Quat with matrices!
	Matrix M = S * Q * T;

	this->local = M;
	this->world = this->local * ParentWorld;

	// push to graphics object
	Matrix mTmp =  this->BoneOrientation;
	assert(this->pGraphicsObject);
	this->pGraphicsObject->setWorld( mTmp );
}