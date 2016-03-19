#ifndef GRAPHICS_OBJECT_TEXTURE_H
#define GRAPHICS_OBJECT_TEXTURE_H

#include <sb6.h>
#include "GraphicsObject.h"
#include "TextureNode.h"

class GraphicsObject_FlatTexture :public GraphicsObject
{
public:
	GraphicsObject_FlatTexture(Model *model, RenderMaterial *render, TextureName name);
	virtual void Render() override;

// data:  place uniform instancing here
	
	//GLuint textureID;
	TextureName textName;


};
#endif