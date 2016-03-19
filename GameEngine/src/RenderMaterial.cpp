#include <assert.h>

#include "GraphicsObject.h"
#include "RenderMaterial.h"

RenderMaterial::RenderMaterial( ShaderObject *shaderObject)
	: pShaderObj( shaderObject )
{
	assert( shaderObject != 0 );
}

void RenderMaterial::Process(  GraphicsObject *p )
{
	this->State(p);
	this->Draw(p);
}

