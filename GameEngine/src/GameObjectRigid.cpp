#include <assert.h>
#include <math.h>

#include "PCSNode.h"
#include "MathEngine.h"
#include "GameObject.h"
#include "GraphicsObject.h"
#include "Anim.h"
#include "FrameBucket.h"
#include "GameObjectRigid.h"

GameObjectRigid::GameObjectRigid( GraphicsObject  *graphicsObject )
	: GameObject(graphicsObject)
{
	this->scale.set(1.0f,1.0f,1.0f);
	this->pos.set(0.0f,0.0f,0.0f);
}

GameObjectRigid::~GameObjectRigid()
{
}



Matrix &GameObjectRigid::getWorld()
{
	return this->world;
}

void GameObjectRigid::update( Time  )
{
	Matrix T = Matrix( TRANS, this->pos);
	Matrix S = Matrix( SCALE, this->scale);

	Matrix M = S * T;

	this->world = M;

	//this->pGraphicsObject->setWorld( M );
}