#ifndef MYGAME_OBJECT_ANIM_H
#define MYGAME_OBJECT_ANIM_H

#include "GameObject.h"
#include "MathEngine.h"
#include "Model.h"
#include "GraphicsObject.h"
#include "PCSNode.h"
#include "Time.h"
#include "Skeleton.h"
class MyGameObjectAnim : public GameObject
{
public:
	MyGameObjectAnim(GraphicsObject  *graphicsObject);
	virtual ~MyGameObjectAnim() override;

	virtual void update(Time currentTime ) override;
	Matrix &getWorld();
	//GraphicsObject *getGraphicsObject();
    void setBoneOrientation( const Matrix & );
	Matrix getBoneOrientation( void ) const;

	void setIndex( int val );

public:
	Vect scale;
	Vect pos;
	Vect dof;
	Vect up;

	// Animation stuff: 	
	Matrix      local;
	Matrix		BoneOrientation;


	int         indexBoneArray;
	Skeleton *  tedy;
private:

//	GraphicsObject  *pGraphicsObject;

	// prevent from calling
	MyGameObjectAnim();
	MyGameObjectAnim( GameObject &copy);
};



#endif