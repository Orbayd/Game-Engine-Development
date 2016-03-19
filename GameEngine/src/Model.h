#ifndef MODEL_H
#define MODEL_H

#include "MathEngine.h"
#include "sb6.h"

class Model
{
public:
	Model();
	virtual ~Model();

// Data
	int numVerts;
	int numTris;

	GLuint vao;
	GLuint vbo[2];

private:
	// load VAO
	virtual void privCreateVAO( const char * const modelFileName  ) = 0;

	// prevent from copying
	Model( Model &copyModel );
	Model & operator = (Model &copyModel);
};

#endif