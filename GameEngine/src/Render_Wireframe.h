#ifndef RENDER_WIREFRAME_H
#define RENDER_WIREFRAME_H

#include "GameObject.h"
#include "RenderMaterial.h"
#include "ShaderObject.h"


class Render_Wireframe: public RenderMaterial
{
public:
	Render_Wireframe( ShaderObject *shaderObject );

private:
	void State( GraphicsObject *p) override;
	void Draw( GraphicsObject *p) override;

	RenderType type;

};

#endif