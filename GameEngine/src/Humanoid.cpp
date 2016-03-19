#include "Humanoid.h"
#include "Time.h"
#include "GameObject.h"

#include "MyGameObjAnim.h"
#include "GraphicsObject_TextureLight.h"
#include "PyramidModel.h"
#include "Render_TextureLight.h"
#include "GameObjectMan.h"
#include "GameObjectRigid.h"

#include "FrameBucket.h"
#include "Anim.h"
//#define BONE_WIDTH 2.0f
Humanoid
::Humanoid
():tCurrent(TIME_ZERO)
{
	this->root = 0;
	this->boneSize = 80;
	this->boneWidth = 2.0f;
	this->sType = SkeletonType::HUMAN;
	this->numberofFrameList = 0;
	this->Headindex = 0;
}

Humanoid
::~Humanoid
()
{
}

void Humanoid::ReadAnimationData(const char * filename)
{
	FILE* file;
	fopen_s(&file, filename,"rb");
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
	fclose(file);
}

void Humanoid::SetAnimationHierarchy()
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
	pGameRigid->scale = Vect(0.05f,0.05f,0.05f);
	

	//// Humanoid BEAR
	color.set(1.00f, 2.0f, 1.00f, 1.0f);
	
	
	
	
	for (unsigned int i = 0; i < listHirerachy.size(); i++)
	{
			//initial
			pGraphics_TextureLight = new GraphicsObject_TextureLight( pPyramidModel, pRender_TextureLight, TextureName::DUCKWEED, color, pos);
			MyGameObjectAnim *pBone = new MyGameObjectAnim( pGraphics_TextureLight );
			pBone->setIndex(listHirerachy[i].index);
			pBone->setName(listHirerachy[i].Name);
			goList.push_back(pBone);

			pBone->tedy = this;
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
				MyGameObjectAnim* temp = goList[0];
				GameObjectMan::Add( temp, pGameRigid );
				//GameObjectMan::Add( temp,GameObjectMan::GetRoot());
			}
			else
			{	
				MyGameObjectAnim* temp = goList[j];
				MyGameObjectAnim* tempParent = findByIndex(goList,listHirerachy[j].ParentIndex);
				GameObjectMan::Add( temp, tempParent );
			}
	}
	//pTree->printTree();
	listHirerachy.clear();
	goList.clear();
}


void Humanoid::SetAnimationPose( )
{
	
	// First thing, get the first frame of animation
	animator.ProcessAnimation( tCurrent,pHead,80 );

	// walks the anim node does the pose for everything that
	walk_anim_node( pFirstBone );

	    Time deltaTime =  animationSpeed * Time(TIME_NTSC_30_FRAME);
		Time maxTime;

		tCurrent += deltaTime;

	
		 findMaxTime(maxTime);
		// protection for time values for looping
		if( tCurrent < Time(TIME_ZERO) )
		{
			tCurrent = maxTime;
		}
		else if ( tCurrent > maxTime )
		{
			tCurrent = Time(TIME_ZERO);
		}
		else
		{
			// do nothing
		}


}
void Humanoid::setBonePose(GameObject *node)
{

	MyGameObjectAnim *childNode = (MyGameObjectAnim *)node;
	//GameObject *parentNode = (GameObject *)node->getParent();
	MyGameObjectAnim *parentNode;
	if( node->getParent()->getParent()->getParent() != 0)
	parentNode = (MyGameObjectAnim *)node->getParent();
	else
	parentNode = 0;

	
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

		Matrix S( SCALE, boneWidth, boneWidth, mag);
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
void Humanoid::walk_anim_node(GameObject *node )
{
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
void Humanoid::SetAnimationData()
{
	// --------  Result Frame  ----------------------
	unsigned int index =0;

	for(;index<animationList.size();index++){

			numberofFrameList++;
			pHeadDebug[index] = new Frame_Bucket();
			pHeadDebug[index]->prevBucket = 0;
			pHeadDebug[index]->nextBucket = 0;
			pHeadDebug[index]->KeyTime = Time(TIME_ZERO);
			pHeadDebug[index]->pBone = new Bone[boneSize];
			Frame_Bucket *current = pHeadDebug[index];
			
			for(  int i = 0; i <animationList[index].framenum; i++)
			{
				int keyframe = i;
				
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
				pTmp->pBone = new Bone[boneSize];
				pTmp->index = i;
				current->nextBucket = pTmp;
				if(i==0)
				{
					pHeadDebug[index]=pTmp;
				
				}
		
				for(unsigned int  j = 0; j < boneSize; j++)
				{
			
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
	
	pHead = pHeadDebug[0];
	

}

MyGameObjectAnim* Humanoid::findByIndex(std::vector<MyGameObjectAnim*> list, int index)
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
Frame_Bucket *  Humanoid::getHeadFrameBucket()
{
	
	return pHead;
}

void Humanoid::findMaxTime(Time &tMax)
{
	animator.findMaxTime(tMax,pHead);

}

void Humanoid::ProcessAnimation(Time tCurr)
{


	animator.ProcessAnimation(tCurr,pHead,boneSize);


}

void Humanoid::ChangeAnimation()
{
	if(Headindex<numberofFrameList-1 &&Headindex<MAXANIMATION)
	{
		pHead = pHeadDebug[Headindex+1];
		Headindex++;
	}
	else
	{
		Headindex=0;
		pHead = pHeadDebug[Headindex];
	}
}
GameObject* Humanoid::GetFirstBone()
{

	return pFirstBone;
}