#ifndef RENDER_COLOR_BY_POSITION_H
#define RENDER_COLOR_BY_POSITION_H

#include "GameObject.h"
#include "RenderMaterial.h"
#include "ShaderObject.h"


class Render_ColorByPosition: public RenderMaterial
{
public:
	Render_ColorByPosition( ShaderObject *shaderObject );

private:
	void State( GraphicsObject *p) override;
	void Draw( GraphicsObject *p) override;

	RenderType type;

};

#endif