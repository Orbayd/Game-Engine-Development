#include <assert.h>

#include "GraphicsObject_TextureLight.h"
#include "RenderMaterial.h"



GraphicsObject_TextureLight::GraphicsObject_TextureLight(Model *model, RenderMaterial *render, TextureName name, Vect &LightColor, Vect &LightPos)
: GraphicsObject(model, render), textName(name), lightColor(LightColor), lightPos(LightPos)
{
	
}

void GraphicsObject_TextureLight::Render() 
{
	pRender->Process( this );
}

