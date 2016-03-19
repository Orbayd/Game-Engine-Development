#ifndef GAME_OBJECT_RIGID_H
#define GAME_OBJECT_RIGID_H


#include "GameObject.h"
#include "MathEngine.h"
#include "Model.h"
#include "GraphicsObject.h"
#include "PCSNode.h"
#include "Time.h"

class GameObjectRigid : public GameObject
{
public:
	GameObjectRigid(GraphicsObject  *graphicsObject);

	virtual ~GameObjectRigid() override;
	virtual void update(Time currentTime ) override;

	Matrix &getWorld();


public:
	Vect scale;
	Vect pos;


private:
	// prevent from calling
	GameObjectRigid();
	GameObjectRigid( GameObject &copy);
};

#endif