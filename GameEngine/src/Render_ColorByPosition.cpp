#include <assert.h>
#include "MathEngine.h"
#include "GraphicsObject_ColorByPosition.h"
#include "Render_ColorByPosition.h"
#include "Camera.h"

extern Camera *pCam;
          
Render_ColorByPosition::Render_ColorByPosition( ShaderObject *shaderObject )
: RenderMaterial( shaderObject ), type( RenderMaterial::RenderType::ColorByPosition )
{
	
}

void Render_ColorByPosition::State( GraphicsObject *p )
{	
	GraphicsObject_ColorByPosition *pGObj = (GraphicsObject_ColorByPosition *)p;
	pGObj;

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
}

void Render_ColorByPosition::Draw( GraphicsObject *p )
{	     
	// Back Pointer
		GraphicsObject_ColorByPosition *pGObj = (GraphicsObject_ColorByPosition *)p;

	// Draw Me: -----------------------------------------

		// set the vao
		glBindVertexArray(pGObj->getModel()->vao);
	
		// use this shader
		this->pShaderObj->SetActive();

		Matrix world = pGObj->getWorld();
		Matrix view = pCam->getViewMatrix();
		Matrix proj = pCam->getProjMatrix();

		glUniformMatrix4fv(this->pShaderObj->GetLocation("proj_matrix"), 1, GL_FALSE, (float *)&proj);
		glUniformMatrix4fv(this->pShaderObj->GetLocation("view_matrix"), 1, GL_FALSE, (float *)&view);
		glUniformMatrix4fv(this->pShaderObj->GetLocation("world_matrix"), 1, GL_FALSE, (float *)&world);

		// draw
		//glDrawArrays(GL_TRIANGLES, 0, (3 * pGObj->getModel()->numVerts) );

		//The starting point of the IBO
		glDrawElements(GL_TRIANGLES, 3 * pGObj->getModel()->numTris, GL_UNSIGNED_INT, 0);   //The starting point of the IBO
  
}


