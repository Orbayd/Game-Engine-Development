#include <assert.h>

#include "GraphicsObject_FlatTexture.h"
#include "RenderMaterial.h"



GraphicsObject_FlatTexture::GraphicsObject_FlatTexture(Model *model, RenderMaterial *render, TextureName name)
: GraphicsObject(model, render), textName(name)
{
	
}

void GraphicsObject_FlatTexture::Render() 
{
	pRender->Process( this );
}

