#ifndef CUBE_MODEL_H
#define CUBE_MODEL_H

#include "Model.h"

class CubeModel : public Model
{
public:
	CubeModel( const char * const modelFileName );
	~CubeModel();

private:
	void privCreateVAO( const char * const modelFileName  ) override;



};

#endif