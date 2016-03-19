#include <assert.h>
#include <math.h>

#include "PCSNode.h"
#include "MathEngine.h"
#include "GameObject.h"
#include "GraphicsObject.h"
#include "Anim.h"
#include "FrameBucket.h"

//extern Frame_Bucket *pHead;

GameObject::GameObject( GraphicsObject  *graphicsObject )
	: PCSNode(),
	world(IDENTITY), 
	pGraphicsObject( graphicsObject )
{

}

GameObject::~GameObject()
{
}

GraphicsObject *GameObject::getGraphicsObject()
{
	return this->pGraphicsObject;
}

Matrix &GameObject::getWorld()
{
	return this->world;
}

void GameObject::update( Time  )
{
	
	// Get the parent world

		// Isn't awesome that we can multiply Quat with matrices!
	Matrix M(IDENTITY);
	
	this->world = M;


}