#include <assert.h>
#include "MathEngine.h"
#include "GraphicsObject_TextureLight.h"
#include "Render_TextureLight.h"
#include "TextureManager.h"

#include "Camera.h"

extern Camera *pCam;
          
Render_TextureLight::Render_TextureLight( ShaderObject *shaderObject )
: RenderMaterial( shaderObject ), type( RenderMaterial::RenderType::TextureLight )
{
	
}

void Render_TextureLight::State( GraphicsObject *p )
{	
	GraphicsObject_TextureLight *pGObj = (GraphicsObject_TextureLight *)p;
	
	glActiveTexture(GL_TEXTURE0);

	// Bind the texture
	GLuint textureID = TextureMan::find( pGObj->textName );
	glBindTexture(GL_TEXTURE_2D, textureID);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
}

void Render_TextureLight::Draw( GraphicsObject *p )
{	     
	// Back Pointer
		GraphicsObject_TextureLight *pGObj = (GraphicsObject_TextureLight *)p;

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

		Vect lightPos = pGObj->lightPos;
		Vect lightColor = pGObj->lightColor;
		glUniform3fv(this->pShaderObj->GetLocation("vLightPos"), 1, (float *)&lightPos);
		glUniform4fv(this->pShaderObj->GetLocation("vColor"), 1, (float *)&lightColor);

		// draw
		//glDrawArrays(GL_TRIANGLES, 0, (3 * pGObj->getModel()->numVerts) );

		//The starting point of the IBO
		glDrawElements(GL_TRIANGLES, 3 * pGObj->getModel()->numTris, GL_UNSIGNED_INT, 0);   //The starting point of the IBO
  


}


