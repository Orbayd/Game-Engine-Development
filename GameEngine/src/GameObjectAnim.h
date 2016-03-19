#ifndef GAME_OBJECT_ANIM_H
#define GAME_OBJECT_ANIM_H


#include "MathEngine.h"
#include "Model.h"
#include "GraphicsObject.h"
#include "PCSNode.h"
#include "Time.h"

class GameObjectAnim : public GameObject
{
public:
	GameObjectAnim(GraphicsObject  *graphicsObject);
	virtual ~GameObjectAnim() override;

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

private:

//	GraphicsObject  *pGraphicsObject;

	// prevent from calling
	GameObjectAnim();
	GameObjectAnim( GameObject &copy);
};



#endif