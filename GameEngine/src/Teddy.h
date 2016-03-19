#ifndef TEDDY_H
#define TEDDY_H
#include<vector>
#include "AnimationFile.h"
#include "MyAnimator.h"
#include "Skeleton.h"
#include "Time.h"
class GameObject;

struct Frame_Bucket;
class PCSNode;

class MyGameObjectAnim;
class Teddy : public Skeleton

{
public:
	Teddy();
	~Teddy();
	void SetAnimationData()override ;
	void ReadAnimationData(const char * filename)  override;
	void SetAnimationHierarchy() override ;
	void SetAnimationPose(  ) override ;
	void setBonePose( GameObject *node ) override ;
	void walk_anim_node( GameObject *node ) override;
	GameObject* GetFirstBone()override;
	MyGameObjectAnim* findByIndex(std::vector<MyGameObjectAnim*> list, int index) override ;

	Frame_Bucket * getHeadFrameBucket() override ;
	void ProcessAnimation(Time tCurr) override ;
	void findMaxTime(Time &tMax) override ;
	void ChangeAnimation() override;
private:
	std::vector<animationTree> listHirerachy;
	std::vector<timeFrameBucket> timeFrameList;
	std::vector<AnimatinBucket> animationList;
	PCSNode *root ;
	Frame_Bucket *pHead;
	Frame_Bucket *pHeadDebug[MAXANIMATION];
	
	
public:
	GameObject *pFirstBone;
	MyAnimator animator;
	Time tCurrent;
	
	unsigned int Headindex;
	unsigned int numberofFrameList;
};



#endif // !TEDDY_H
