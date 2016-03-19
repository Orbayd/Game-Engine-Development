#include <assert.h>

#include "GraphicsObject_Wireframe.h"
#include "RenderMaterial.h"



GraphicsObject_Wireframe::GraphicsObject_Wireframe(Model *model, RenderMaterial *render)
: GraphicsObject(model, render)
{

}

void GraphicsObject_Wireframe::Render() 
{
	pRender->Process( this );
}

