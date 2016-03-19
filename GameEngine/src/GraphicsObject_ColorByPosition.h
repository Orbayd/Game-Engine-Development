#ifndef GRAPHICS_OBJECT_COLOR_BY_POSITION_H
#define GRAPHICS_OBJECT_COLOR_BY_POSITION_H

#include "GraphicsObject.h"

class GraphicsObject_ColorByPosition :public GraphicsObject
{
public:
	GraphicsObject_ColorByPosition(Model *model, RenderMaterial *render);
	virtual void Render() override;

// data:  place uniform instancing here
	

};
#endif