#ifndef RENDER_TEXTURE_H
#define RENDER_TEXTURE_H

#include "GameObject.h"
#include "RenderMaterial.h"
#include "ShaderObject.h"


class Render_FlatTexture: public RenderMaterial
{
public:
	Render_FlatTexture( ShaderObject *shaderObject );

private:
	void State( GraphicsObject *p) override;
	void Draw( GraphicsObject *p) override;

	RenderType type;

};

#endif