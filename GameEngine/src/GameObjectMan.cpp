#include <assert.h>

#include "GameObject.h"
#include "GameObjectMan.h"


void GameObjectMan::Add( GameObject *pObj, GameObject *pParent )
{
	assert( pObj != 0 );
    assert( pParent != 0 );

	// Get singleton
	GameObjectMan *pGOM = GameObjectMan::privGetInstance();

	// insert object to root
	pGOM->pRootTree->insert( pObj, pParent );

}

PCSTree *GameObjectMan::GetPCSTree()
{
	// Get singleton
	GameObjectMan *pGOM = GameObjectMan::privGetInstance();
	assert(pGOM);

	// Get root node
	

	return pGOM->pRootTree;
}

GameObject *GameObjectMan::GetRoot()
{
	// Get singleton
	GameObjectMan *pGOM = GameObjectMan::privGetInstance();
	assert(pGOM);

	// Get root node
	PCSNode *pRootNode = pGOM->pRootTree->getRoot();
	assert(pRootNode);

	GameObject *pGameObj = (GameObject *) pRootNode;
	assert(pGameObj);

	return pGameObj;
}

void GameObjectMan::Update( Time currentTime)
{
	GameObjectMan *pGOM = GameObjectMan::privGetInstance();
	assert( pGOM );

	PCSNode *pRootNode = pGOM->pRootTree->getRoot();
	assert( pRootNode );
	
	PCSNode *pNode = pRootNode->getChild();

	// walk through all the nodes
	//pGOM->privDepthFirstUpdate(pNode, currentTime);

	
	while(pNode!=0)
	{
		pGOM->privDepthFirstUpdate(pNode, currentTime);
		pNode= pNode->getSibling();
	}
		
			
}

void GameObjectMan::privDepthFirstUpdate( PCSNode *node, Time currentTime ) 
{
   PCSNode *child = 0;

   // Create an iterator!
   // Update the game object

  // node->printNode();

		GameObject *pGameObj = (GameObject *)node;
        pGameObj->update(currentTime);


   // iterate through all of the active children 
   if (node->getChild() != 0)
	{  
	   child =	node->getChild();
	   // make sure that allocation is not a child node 
	   while (child != 0)
	   {
         privDepthFirstUpdate( child, currentTime );
         // goto next sibling
         child = child->getSibling();
	   }
   }
   else
	{
      // bye bye exit condition
	}

}


void GameObjectMan::Draw()
{
	GameObjectMan *pGOM = GameObjectMan::privGetInstance();
	assert( pGOM );

	PCSNode *pRootNode = pGOM->pRootTree->getRoot();
	assert( pRootNode );

	PCSNode *pNode = pRootNode->getChild();

	// walk through all the nodes
	while(pNode!=0)
	{
		pGOM->privDepthFirstDraw( pNode );
		pNode = pNode->getSibling();
	}
}

void GameObjectMan::privDepthFirstDraw( PCSNode *node ) 
{
   PCSNode *child = 0;

   // Create an iterator!
   // draw the game objects
		GameObject *pGameObj = (GameObject *)node;
		GraphicsObject *pGraphicsObj = pGameObj->getGraphicsObject();

		// HACK
		if( pGraphicsObj != 0)
		{
			pGraphicsObj->Render();
		}


   // iterate through all of the active children 
   if (node->getChild() != 0)
	{  
	   child =	node->getChild();
	   // make sure that allocation is not a child node 
	   while (child != 0)
	   {
         privDepthFirstDraw( child );
         // goto next sibling
         child = child->getSibling();
	   }
   }
   else
	{
      // bye bye exit condition
	}

}


GameObjectMan::GameObjectMan( )
{
	this->pRootTree = new PCSTree();
	assert(this->pRootTree);

	//PCSNode *pRootNode = new PCSNode("GameObject_Root");
	//assert( pRootNode );

    GameObject *pRootGameObject = new GameObject(0);
	assert( pRootGameObject );


	// Set it to be root
	pRootTree->insert( pRootGameObject, 0 );
}
	


GameObjectMan * GameObjectMan::privGetInstance( void )
{
	// This is where its actually stored (BSS section)
	static GameObjectMan gom;
	return &gom;
}
void GameObjectMan::Delete(GameObject *pObj)
{
	GameObjectMan *pGOM = GameObjectMan::privGetInstance();
	assert( pGOM );

	 pGOM->pRootTree->remove(pObj);
	
}
