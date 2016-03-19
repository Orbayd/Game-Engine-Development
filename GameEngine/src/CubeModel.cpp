#include <sb6.h>
#include <assert.h>

#include "CubeModel.h"

struct Vert_xyzuvn
{
	float x;
	float y;
	float z;
	float u;
	float v;
	float nx;
	float ny;
	float nz;
};

struct Tri_index
{
	unsigned int v0;
	unsigned int v1;
	unsigned int v2;
};

#define TRILIST_NUM_TRIANGLES (sizeof(triList)/sizeof(Tri_index))


Tri_index triList[] =
{
	{0,1,2},
	{2,3,0},
	{4,5,6},
	{5,7,6},
	{8,9,10},
	{9,11,10},
	{12,13,14},
	{13,15,14},
	{16,17,18},
	{18,19,16},
	{20,21,22},
	{22,23,20}
};



#define CUBE_DATA_NUM_VERTS (sizeof(cubeData)/sizeof(Vert_xyzuvn))



Vert_xyzuvn  cubeData[] =
{
	// Triangle 0
	{-0.25f,  0.25f, -0.25f, 0.0f, 0.0f, -0.6f,  0.6f, -0.6f  }, //0
	{-0.25f, -0.25f, -0.25f, 0.0f, 1.0f, -0.6f, -0.6f, -0.6f  },// 1
	{ 0.25f, -0.25f, -0.25f, 1.0f, 1.0f,  0.6f, -0.6f, -0.6f  }, //2

	// Triangle 1

	{ 0.25f,   0.25f, -0.25f, 1.0f, 0.0f,  0.6f,  0.6f, -0.6f  },  //4  3


	// Triangle 2
	{ 0.25f, -0.25f, -0.25f, 0.0f, 1.0f, 0.6f, -0.6f, -0.6f  }, //6
	{ 0.25f, -0.25f,  0.25f, 1.0f, 1.0f, 0.6f, -0.6f,  0.6f  }, //7
	{ 0.25f,  0.25f, -0.25f, 0.0f, 0.0f, 0.6f,  0.6f, -0.6f  }, //8

	// Triangle 3

	{ 0.25f,  0.25f,  0.25f, 1.0f, 0.0f, 0.6f,  0.6f,  0.6f  }, //9 


	// Triangle 4
	{ 0.25f, -0.25f,  0.25f, 1.0f, 1.0f,  0.6f, -0.6f, 0.6f  },  // 12
	{-0.25f, -0.25f, 0.25f, 0.0f, 1.0f, -0.6f, -0.6f, 0.6f  },   // 13
	{ 0.25f,  0.25f,  0.25f, 1.0f, 0.0f,  0.6f,  0.6f, 0.6f  },  // 14

	// Triangle 5

	{ -0.25f,  0.25f,  0.25f, 0.0f, 0.0f, -0.6f,  0.6f, 0.6f },  //15


	// Triangle 6
	{-0.25f, -0.25f,  0.25f, 0.0f, 0.0f, -0.6f, -0.6f,  0.6f }, //18
	{-0.25f, -0.25f, -0.25f, 0.0f, 1.0f, -0.6f, -0.6f, -0.6f }, //19
	{-0.25f,  0.25f,  0.25f, 1.0f, 0.0f, -0.6f,  0.6f,  0.6f }, //20

	// Triangle 7

	{-0.25f,  0.25f, -0.25f, 1.0f, 1.0f, -0.6f,  0.6f, -0.6f }, // 21


	// Triangle 8
	{-0.25f, -0.25f,  0.25f, 0.0f, 0.0f, -0.6f, -0.6f,  0.6f }, //24
	{0.25f, -0.25f,   0.25f, 1.0f, 0.0f,  0.6f, -0.6f,  0.6f }, //25
	{0.25f, -0.25f,  -0.25f, 1.0f, 1.0f,  0.6f, -0.6f, -0.6f }, //26

	// Triangle 9

	{-0.25f, -0.25f, -0.25f, 0.0f, 1.0f, -0.6f, -0.6f, -0.6f}, // 27


	// Triangle 10
	{-0.25f,  0.25f, -0.25f, 0.0f, 1.0f, -0.6f, 0.6f, -0.6f }, //30
	{0.25f,  0.25f,  -0.25f, 1.0f, 1.0f,  0.6f, 0.6f, -0.6f }, //31
	{0.25f,  0.25f,   0.25f, 1.0f, 0.0f,  0.6f, 0.6f,  0.6f }, //32

	// Triangle 11

	{-0.25f,  0.25f,  0.25f, 0.0f, 0.0f, -0.6f, 0.6f,  0.6f }, //33

};

void CubeModel::privCreateVAO( const char * const modelFileName )
{
	// future proofing it for a file
	modelFileName;

	this->numVerts = CUBE_DATA_NUM_VERTS;
	this->numTris = TRILIST_NUM_TRIANGLES;

	// Create a VAO
	glGenVertexArrays(1, &this->vao);
	assert( this->vao != 0 );
	glBindVertexArray(this->vao);

	// Create a VBO
    glGenBuffers(2, &this->vbo[0]);
	assert( this->vbo[0] != 0 );

	
    // Load the combined data: ---------------------------------------------------------

		glBindBuffer(GL_ARRAY_BUFFER, this->vbo[0]);

		// load the data to the GPU
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vert_xyzuvn) * this->numVerts, cubeData, GL_STATIC_DRAW);
		
		// Vertext data in location 0
			void *offsetVert = (void *)((unsigned int)&cubeData[0].x - (unsigned int)cubeData);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_xyzuvn), offsetVert);
			glEnableVertexAttribArray(0);

		// Texture data in location 1
			void *offsetTex = (void *)((unsigned int)&cubeData[0].u - (unsigned int)cubeData);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vert_xyzuvn), offsetTex);
			glEnableVertexAttribArray(1);

		// Normal data in location 2
			void *offsetNorm = (void *)((unsigned int)&cubeData[0].nx - (unsigned int)cubeData);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_xyzuvn), offsetNorm);
			glEnableVertexAttribArray(2);


	  // Load the index data: ---------------------------------------------------------
	
            /* Bind our 2nd VBO as being the active buffer and storing index ) */
		      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);

	         /* Copy the index data to our buffer */
		      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Tri_index) * this->numTris, triList, GL_STATIC_DRAW);

}


CubeModel::CubeModel( const char * const modelFileName )
	: Model()
{
	this->privCreateVAO( modelFileName );
}

CubeModel::~CubeModel()
{
	// remove anything dynamic here
}