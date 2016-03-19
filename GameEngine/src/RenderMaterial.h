#ifndef RENDER_MATERIAL_H
#define RENDER_MATERIAL_H

#include "GameObject.h"
#include "ShaderObject.h"

class RenderMaterial
{
public:

	RenderMaterial( ShaderObject *shaderObject );
	enum class RenderType
	{
		ColorByPosition,
		Wireframe,
		FlatTexture,
		TextureLight,

	};

public:
	virtual void State( GraphicsObject *p) = 0;
	virtual void Draw( GraphicsObject *p) = 0;

	void Process(  GraphicsObject *p );

	ShaderObject *pShaderObj;

};


#endif