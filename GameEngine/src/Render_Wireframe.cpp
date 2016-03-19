#include <assert.h>
#include "MathEngine.h"
#include "GraphicsObject_Wireframe.h"
#include "Render_Wireframe.h"

#include "Camera.h"

extern Camera *pCam;
          
Render_Wireframe::Render_Wireframe( ShaderObject *shaderObject )
: RenderMaterial( shaderObject ), type( RenderMaterial::RenderType::Wireframe )
{
	
}

void Render_Wireframe::State( GraphicsObject *p )
{	
	GraphicsObject_Wireframe *pGObj = (GraphicsObject_Wireframe *)p;
	pGObj;

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
}

void Render_Wireframe::Draw( GraphicsObject *p )
{	     
	// Back Pointer
		GraphicsObject_Wireframe *pGObj = (GraphicsObject_Wireframe *)p;

	// Draw Me: -----------------------------------------

		// set the vao
		glBindVertexArray(pGObj->getModel()->vao);
	
			// Set state
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDisable(GL_CULL_FACE);

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
  

			// Restore state
			glEnable(GL_CULL_FACE);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			



}


