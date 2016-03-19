#ifndef PYRAMID_MODEL_H
#define PYRAMID_MODEL_H

#include "Model.h"

class PyramidModel : public Model
{
public:
	PyramidModel( const char * const modelFileName );
	~PyramidModel();

private:
	void privCreateVAO( const char * const modelFileName  ) override;



};

#endif