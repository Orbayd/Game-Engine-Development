#include <assert.h>

#include "GraphicsObject_ColorByPosition.h"
#include "RenderMaterial.h"



GraphicsObject_ColorByPosition::GraphicsObject_ColorByPosition(Model *model, RenderMaterial *render)
: GraphicsObject(model, render)
{

}

void GraphicsObject_ColorByPosition::Render() 
{
	pRender->Process( this );
}

