#ifndef GRAPHICS_OBJECT_TEXTURE_LIGHT_H
#define GRAPHICS_OBJECT_TEXTURE_LIGHT_H

#include <sb6.h>
#include "GraphicsObject.h"
#include "TextureNode.h"

class GraphicsObject_TextureLight :public GraphicsObject
{
public:
	GraphicsObject_TextureLight(Model *model, RenderMaterial *render, TextureName name, Vect &LightColor, Vect &LightPos);
	virtual void Render() override;

// data:  place uniform instancing here
	
	//GLuint textureID;
	TextureName textName;
		Vect lightColor;
	Vect lightPos;
	
};
#endif