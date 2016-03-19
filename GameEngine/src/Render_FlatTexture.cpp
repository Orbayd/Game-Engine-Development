#include <assert.h>
#include "MathEngine.h"
#include "GraphicsObject_FlatTexture.h"
#include "Render_FlatTexture.h"
#include "TextureManager.h"

#include "Camera.h"

extern Camera *pCam;
          
Render_FlatTexture::Render_FlatTexture( ShaderObject *shaderObject )
: RenderMaterial( shaderObject ), type( RenderMaterial::RenderType::FlatTexture )
{
	
}

void Render_FlatTexture::State( GraphicsObject *p )
{	
	GraphicsObject_FlatTexture *pGObj = (GraphicsObject_FlatTexture *)p;
	
	glActiveTexture(GL_TEXTURE0);

	// Bind the texture
	GLuint textureID = TextureMan::find( pGObj->textName );
	glBindTexture(GL_TEXTURE_2D, textureID);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
}

void Render_FlatTexture::Draw( GraphicsObject *p )
{	     
	// Back Pointer
		GraphicsObject_FlatTexture *pGObj = (GraphicsObject_FlatTexture *)p;

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


