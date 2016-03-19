#include "DebugOut.h"
#include "GameObject.h"
#include "MathEngine.h"
#include "Game.h"
#include "ShaderObject.h"
#include "CubeModel.h"
#include "PyramidModel.h"
#include "GraphicsObject.h"
#include "GraphicsObject_ColorByPosition.h"
#include "Render_ColorByPosition.h"
#include "GraphicsObject_Wireframe.h"
#include "Render_Wireframe.h"
#include "GraphicsObject_FlatTexture.h"
#include "Render_FlatTexture.h"
#include "GraphicsObject_TextureLight.h"
#include "Render_TextureLight.h"
#include "TextureManager.h"
#include "InputMan.h"
#include "Camera.h"
#include "GameObjectMan.h"
#include "Time.h"
#include "Timer.h"
#include "VectApp.h"
#include "QuatApp.h"
#include "Anim.h"
#include "Constants.h"
#include "VectApp.h"
#include "QuatApp.h"
#include "FrameBucket.h"
#include "GameObjectAnim.h"
#include "GameObjectRigid.h"
#include "AnimationFile.h"

#define BONE_WIDTH 8.0f
void setBonePose( GameObject *node );
void walk_anim_node( GameObject *node );
GameObjectAnim *findByIndex(std::vector<GameObjectAnim*> list, int index);
Frame_Bucket *pHead;
Frame_Bucket *pHeadDebug[2];
GameObject *pFirstBone;
PCSNode *root = 0;

std::vector<animationTree> listHirerachy;
std::vector<timeFrameBucket> timeFrameList;
std::vector<AnimatinBucket> animationList;
void SetAnimationHierarchy()
{

	// Load the model 
		PyramidModel *pPyramidModel = new PyramidModel( "pyramidModel.azul" );pPyramidModel;

	// Create/Load Shader 
		ShaderObject *pShaderObject_textureLight = new ShaderObject( ShaderName::TEXTURE_POINT_LIGHT, "texturePointLightDiff");
	
	// Setup renderer
		Render_TextureLight *pRender_TextureLight    = new Render_TextureLight( pShaderObject_textureLight );pRender_TextureLight;


	// GraphicsObject for a specific instance
		GraphicsObject_TextureLight *pGraphics_TextureLight;pGraphics_TextureLight;

	// Create GameObject
	Vect color;
	Vect pos(1,1,1);

	PCSTree *pTree = GameObjectMan::GetPCSTree();
	root = pTree->getRoot();

	GameObjectRigid *pGameRigid = new GameObjectRigid( 0 );
	GameObjectMan::Add(  pGameRigid, GameObjectMan::GetRoot() );
	pGameRigid->setName("Rigid");
	pGameRigid->scale = Vect(10,10,10);
	

	//// TEDDY BEAR
	color.set(1.00f, 1.0f, 50.00f, 1.0f);
	FILE* file;
	fopen_s(&file, "teddy1.bp","rb");
	headerBin outHeader;
	fread(&outHeader, sizeof(headerBin), 1, file);
	int size = outHeader.boneNum;
	int NumAnim = outHeader.animNum;
	//read hier first
	printf("\nRead Faces");
	listHirerachy.reserve(size);
	for(int i = 0; i < size; i++)
	{
		animationTree temp;
		fread(&temp, sizeof(animationTree), 1, file);
		listHirerachy.push_back(temp);
	}
	//read time next
	printf("\nRead Vert");
	timeFrameList.reserve(size);
	for(int k=0;k<NumAnim;k++)
	{
		AnimatinBucket animBucketDebug;
	    fread(&animBucketDebug.name,sizeof(animBucketDebug.name), 1, file);
		fread(&animBucketDebug.framenum,sizeof(int), 1, file);
		for(int i = 0; i <animBucketDebug.framenum; i++)
		{
			timeFrameBucket temp;
			int timeFrame;
			fread(&timeFrame, sizeof(int), 1, file);
			temp.timeFrame = timeFrame;

			for(int j = 0; j < outHeader.boneNum; j++)
			{
				BonesData boneData;
				fread(&boneData, sizeof(BonesData), 1, file);
				temp.bones.push_back(boneData);
			}
			timeFrameList.push_back(temp);
		}
		animBucketDebug.timeFrameList =(timeFrameList);
		animationList.push_back(animBucketDebug);
		timeFrameList.clear();
	}
	std::vector<GameObjectAnim*> goList;
	for (unsigned int i = 0; i < listHirerachy.size(); i++)
	{
			//initial
			pGraphics_TextureLight = new GraphicsObject_TextureLight( pPyramidModel, pRender_TextureLight, TextureName::DUCKWEED, color, pos);
			GameObjectAnim *pBone = new GameObjectAnim( pGraphics_TextureLight );
			pBone->setIndex(listHirerachy[i].index);
			pBone->setName(listHirerachy[i].Name);
			goList.push_back(pBone);
			if(listHirerachy[i].index==0)
			{
				pFirstBone= pBone;
			}

	}
	for (unsigned int j = 0; j < listHirerachy.size(); j++)
	{
			
			//craete hierachy
			if( j == 0)
			{
				GameObjectAnim* temp = goList[0];
				//GameObjectMan::Add( temp, pGameRigid );
				GameObjectMan::Add( temp,GameObjectMan::GetRoot());
			}
			else
			{	
				GameObjectAnim* temp = goList[j];
				GameObjectAnim* tempParent = findByIndex(goList,listHirerachy[j].ParentIndex);
				GameObjectMan::Add( temp, tempParent );
			}
	}
	pTree->printTree();

	fclose( file );
}
GameObjectAnim* findByIndex(std::vector<GameObjectAnim*> list, int index)
{
	//GameObjectAnim *a = 0;
	for( unsigned int i = 0;  i < list.size(); i++)
	{
		if(index == list[i]->indexBoneArray)
		{
			return list[i];
		}
	}
	return 0;
}
void SetAnimationPose( GameObject *root, Time tCurr )
{
	// First thing, get the first frame of animation
	ProcessAnimation( tCurr );

	// walks the anim node does the pose for everything that
	walk_anim_node( root );
}

void setBonePose( GameObject *node )
{
	// Now get the world matrices
	// getting the parent from current node
	GameObjectAnim *childNode = (GameObjectAnim *)node;
	GameObject *parentNode = (GameObject *)node->getParent();
	//GameObjectAnim *parentNode;
	/*if( node->getParent()->getParent()->getParent() != 0)
	parentNode = (GameObjectAnim *)node->getParent();
	else
	parentNode = 0;*/

	
	if( parentNode == root )
		return;

	if( parentNode != 0 && childNode != 0 )
	{
		// starting point
		Vect start(0.0f,0.0f,0.0f);

	   //  At this point, Find the two bones initial positions in world space
	   //  Now get the length and directions

		Vect ptA = start * parentNode->getWorld();

		Vect ptB = start * childNode->getWorld();

		// direction between the anchor points of the respective bones
		Vect dir = -(ptB - ptA);

		// length of the bone 0
		float mag = dir.mag();

		Matrix S( SCALE, BONE_WIDTH, BONE_WIDTH, mag);
		Quat Q( ROT_ORIENT, dir.getNorm(), Vect( 0.0f, 1.0f, 0.0f) );
		Matrix T( TRANS, ptB);

		/*Matrix Sp( SCALE, BONE_WIDTH, BONE_WIDTH, mag);
		Quat Qp( ROT_ORIENT, dir.getNorm(), Vect( 0.0f, 1.0f, 0.0f) );
		Matrix Tp( TRANS, ptA);*/

		Matrix BoneOrient = S * Q * T;
		//Matrix BoneOrientp  =Sp * Qp * Tp;
		//parentNode->setBoneOrientation(BoneOrientp);
		childNode->setBoneOrientation(BoneOrient); 
	}

}


void walk_anim_node( GameObject *node ) 
{
	// --------- Do pose stuff here -----------------------
	setBonePose( node );
   
	// --------- Do pose stuff here -----------------------
	GameObject *child = 0;

	// iterate through all of the active children 
	if (node->getChild() != 0)
	{  
		child =	(GameObject *)node->getChild();
		// make sure that allocation is not a child node 
		while (child != 0)
		{
			walk_anim_node( child );
			// goto next sibling
			child = (GameObject *)child->getSibling();
		}
	}
	else
	{
		// bye bye exit condition
	}
}



void SetAnimationData()
{
	// --------  Result Frame  ----------------------
	unsigned int index =0;
	//FILE* file;
	//fopen_s(&file, "teddyDebug.txt","w");
	for(;index<animationList.size()-1;index++){
			pHeadDebug[index] = new Frame_Bucket();
			pHeadDebug[index]->prevBucket = 0;
			pHeadDebug[index]->nextBucket = 0;
			pHeadDebug[index]->KeyTime = Time(TIME_ZERO);
			pHeadDebug[index]->pBone = new Bone[NUM_BONES];
			Frame_Bucket *current = pHeadDebug[index];
			//out("\n---Animation[%d]:<%s>:\n",index,animationList[index].name );
			for(  int i = 0; i <animationList[index].framenum; i++)
			{
				int keyframe = i;
				//if(animationList[index].timeFrameList[i].timeFrame==0|| animationList[index].timeFrameList[i].timeFrame==10000|| animationList[index].timeFrameList[i].timeFrame==20000){
				Frame_Bucket *pTmp = new Frame_Bucket();
				pTmp->prevBucket = current;
				pTmp->nextBucket = 0;
				if(keyframe==0)
				{
					pTmp->KeyTime =Time(TIME_ZERO);
				}
				else
				{
					pTmp->KeyTime = keyframe*  Time(TIME_NTSC_30_FRAME);
				}
				pTmp->pBone = new Bone[NUM_BONES];
				pTmp->index = i;
				current->nextBucket = pTmp;
				if(i==0)
				{
					pHeadDebug[index]=pTmp;
				
				}
			//	fprintf(file,"\n---KeyFrame[%d]:<%d>:\n",pTmp->index,pTmp->KeyTime );
			//	fprintf(file,"\n---Prev- KeyFrame[%d]:<%d>:\n",pTmp->prevBucket->index,pTmp->prevBucket->KeyTime);

			//	out("\n---KeyFrame[%d]:<%d>:\n",i,animationList[index].timeFrameList[i].timeFrame  );
				for(unsigned int  j = 0; j < NUM_BONES; j++)
				{
			//		out("\nBone[%d] x:%f y:%f z:%f\n",j,animationList[index].timeFrameList[i].bones[j].t_x, animationList[index].timeFrameList[i].bones[j].t_y, animationList[index].timeFrameList[i].bones[j].t_z)
			//		out("nBone[%d] x:%f y:%f z:%f\n",j, animationList[index].timeFrameList[i].bones[j].r_x , animationList[index].timeFrameList[i].bones[j].r_y , animationList[index].timeFrameList[i].bones[j].r_z);
					//out("nBone[%d] x:%f y:%f z:%f\n",j, b.S[x],b.S[y],b.S[z]);
					pTmp->pBone[j].T.set( Vect(
						animationList[index].timeFrameList[i].bones[j].t_x,
						animationList[index].timeFrameList[i].bones[j].t_y, 
						animationList[index].timeFrameList[i].bones[j].t_z));
					
					pTmp->pBone[j].Q.set(Quat(ROT_XYZ,
						animationList[index].timeFrameList[i].bones[j].r_x ,
						animationList[index].timeFrameList[i].bones[j].r_y ,
						animationList[index].timeFrameList[i].bones[j].r_z ));
					if(j==0)
					pTmp->pBone[j].S.set( Vect(1.0f,1.0f,1.0f));
					else
					pTmp->pBone[j].S.set( Vect(animationList[index].timeFrameList[i].bones[j].s_x,animationList[index].timeFrameList[i].bones[j].s_y,animationList[index].timeFrameList[i].bones[j].s_z));
				}
				current = pTmp;
			//}
		
	   }

	}
	//for(unsigned int  j = 0; j < NUM_BONES; j++)
	//{
	//	Bone b = pHead->nextBucket->pBone[j];
	//	out("\nBone[%d] x:%f y:%f z:%f\n",j, b.T[x],b.T[y],b.T[z]);
	//    out("nBone[%d] x:%f y:%f z:%f\n",j, b.Q[x],b.Q[y],b.Q[z]);
	//	out("nBone[%d] x:%f y:%f z:%f\n",j, b.S[x],b.S[y],b.S[z]);
	//}
	pHead = pHeadDebug[0];
	//fclose( file );



}