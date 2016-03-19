#include "AnimationManager.h"
#include "Skeleton.h"
#include "Time.h"
#include "Teddy.h"
#include "GameObjectMan.h"
#include "GameObject.h"
AnimationManager::AnimationManager()
{
	pHead= 0;
}

AnimationManager::~AnimationManager()
{
}

void AnimationManager::AddSkeleton(SkeletonNodeLink * pAnimNode)
{
	
	if(pHead==0)
	{
	
		pHead =pAnimNode;
	}
	else
	{
		pAnimNode->next = pHead;
		pHead->prev= pAnimNode;

		pHead = pAnimNode;
	}


}

void AnimationManager::ProcessAnimation()
{
	SkeletonNodeLink * current = pHead;
	while(current!=0)
	{
		Skeleton *pNode =(Skeleton*)	current;

		pNode->SetAnimationPose();
		current= current->next;
	}


}

AnimationManager * AnimationManager::GetInstance()
{
	static AnimationManager instance;
	return & instance;

}
void AnimationManager::ChangeAnimationSpeed(float coe)
{
	SkeletonNodeLink * current = pHead;
	while(current!=0)
	{
		Skeleton *pNode =(Skeleton*)	current;
		
		pNode->changeSpeed(coe);
		current= current->next;
	}
	

}
void AnimationManager::ChangeAnimation(SkeletonType Type)
{
	SkeletonNodeLink * current = pHead;
	Skeleton *pNode =0;
	while (current!=0)
	{
		pNode =(Skeleton*)current;
		if(pNode->sType==Type)
			break;
		
		current=current->next;
	}
	if(pNode!=0)
		pNode->ChangeAnimation();

}

void AnimationManager::Rewind()
{
	SkeletonNodeLink * current = pHead;
	while(current!=0)
	{
		Skeleton *pNode =(Skeleton*)	current;
		
		pNode->rewind();
		current= current->next;
	}

}
void AnimationManager::Pause()
{
	SkeletonNodeLink * current = pHead;
	while(current!=0)
	{
		Skeleton *pNode =(Skeleton*)	current;
		
		pNode->Pause();
		current= current->next;
	}

}
void AnimationManager::Start()
{
	SkeletonNodeLink * current = pHead;
	while(current!=0)
	{
		Skeleton *pNode =(Skeleton*)	current;
		
		pNode->Start();
		current= current->next;
	}

}

void AnimationManager::Delete(SkeletonType Type)
{
	SkeletonNodeLink * current = pHead;
	Skeleton *pNode =0;
	while (current!=0)
	{
		pNode =(Skeleton*)current;
		if(pNode->sType==Type)
			break;
		
		current=current->next;
	}
	if(pNode!=0)
	{
		GameObject * pObj = pNode->GetFirstBone();
			
		GameObjectMan::Delete(pObj);
				
			
		if(pNode==pHead)
		{
			pHead = 0;
			
		}
		else if(pNode->next ==0)
		{
			pNode->prev->next = 0;
			
		}
		else{
			pNode->prev->next = pNode->next;
			pNode->next->prev = pNode->prev;
		}
		//delete pNode;

	}

}