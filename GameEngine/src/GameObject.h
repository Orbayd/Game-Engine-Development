#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "MathEngine.h"
#include "Model.h"
#include "GraphicsObject.h"
#include "PCSNode.h"
#include "Time.h"

class GameObject : public PCSNode
{
public:
	GameObject(GraphicsObject  *graphicsObject);
	virtual ~GameObject();
	virtual void update(Time currentTime );

	Matrix &getWorld();
	GraphicsObject *getGraphicsObject();
  //  void setBoneOrientation( const Matrix & );
//	Matrix getBoneOrientation( void ) const;
//	void setIndex( int val );

public:
	Matrix      local;
		
	//Vect scale;
	//Vect pos;
	//Vect dof;
	//Vect up;

	// Animation stuff: 	
//	GameObject	*boneParent;
	//Matrix		BoneOrientation;
	//int         indexBoneArray;

protected:
	Matrix world;
	GraphicsObject  *pGraphicsObject;

	// prevent from calling
	GameObject();
	GameObject( GameObject &copy);
};


#endif