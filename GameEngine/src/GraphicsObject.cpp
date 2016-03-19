#include <assert.h>

#include "GraphicsObject.h"
#include "MathEngine.h"
#include "Model.h"


GraphicsObject::GraphicsObject(Model *model, RenderMaterial *render)
	: pModel(model), pRender(render)
{
	this->world.set(IDENTITY);
	assert(model);
	assert(render);
}



Model *GraphicsObject::getModel() const
{
	return this->pModel;
}

RenderMaterial *GraphicsObject::getRender() const
{
	return this->pRender;
}

Matrix &GraphicsObject::getWorld() 
{
	return this->world;
}

void GraphicsObject::setWorld( Matrix &_world)
{
	this->world = _world;
}
