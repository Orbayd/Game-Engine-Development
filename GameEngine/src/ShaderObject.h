#ifndef SHADER_OBJECT_H
#define SHADER_OBJECT_H

#include "sb6.h"

enum class ShaderName
{
	COLOR_LIGHT,
	TEXTURE_SIMPLE,
	TEXTURE_POINT_LIGHT,
};


class ShaderObject
{
public:
	ShaderObject( ShaderName shaderName, const char * const shaderBaseFileName );
	void SetActive();
	GLuint GetLocation( const char * uniformName);

private:
	bool privCreateShader(  GLuint &programObject, const char * const shaderBaseFileName  );
	bool privLoadNCompile(GLuint &shaderObject, const char * const shaderFileName, GLenum shader_type );

public:

// data
	ShaderName  name;
	GLuint		programObject;

};

#endif