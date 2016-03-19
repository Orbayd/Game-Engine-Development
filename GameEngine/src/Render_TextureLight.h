#ifndef RENDER_TEXTURE_LIGHT_H
#define RENDER_TEXTURE_LIGHT_H

#include "GameObject.h"
#include "RenderMaterial.h"
#include "ShaderObject.h"


class Render_TextureLight: public RenderMaterial
{
public:
	Render_TextureLight( ShaderObject *shaderObject );

private:
	void State( GraphicsObject *p) override;
	void Draw( GraphicsObject *p) override;

	RenderType type;

};

#endif