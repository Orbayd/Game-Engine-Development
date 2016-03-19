#ifndef GRAPHICS_OBJECT_WIREFRAME_H
#define GRAPHICS_OBJECT_WIREFRAME_H

#include "GraphicsObject.h"

class GraphicsObject_Wireframe :public GraphicsObject
{
public:
	GraphicsObject_Wireframe(Model *model, RenderMaterial *render);
	virtual void Render() override;

// data:  place uniform instancing here
	

};
#endif