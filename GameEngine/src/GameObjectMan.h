#ifndef GAME_OBJECT_MAN_H
#define GAME_OBJECT_MAN_H

#include "GameObject.h"
#include "PCSTree.h"
#include "Time.h"


// Singleton
class GameObjectMan
{
public:
	
    static void Add( GameObject *pObj, GameObject *pParent );
	static void Draw( void );
	static void Update( Time currentTime );
	static GameObject *GetRoot();
	static PCSTree *GetPCSTree();
	static void Delete(GameObject *pObj);
private:
    void privDepthFirstDraw( PCSNode *node );
    void privDepthFirstUpdate( PCSNode *node, Time currentTime );
	GameObjectMan();
	static GameObjectMan *privGetInstance();
	PCSTree *pRootTree;

};

#endif