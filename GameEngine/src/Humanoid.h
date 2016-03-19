#ifndef HUMANOID
#define HUMANOID
#include<vector>
#include "AnimationFile.h"
#include "MyAnimator.h"
#include "Skeleton.h"
#include "Time.h"
class GameObject;

struct Frame_Bucket;
class PCSNode;

class MyGameObjectAnim;
class Humanoid : public Skeleton

{
public:
	Humanoid();
	~Humanoid();
	void SetAnimationData()override ;
	void ReadAnimationData(const char * filename)  override;
	void SetAnimationHierarchy() override ;
	void SetAnimationPose( ) override ;
	void setBonePose( GameObject *node ) override ;
	void walk_anim_node( GameObject *node ) override;
	
	MyGameObjectAnim* findByIndex(std::vector<MyGameObjectAnim*> list, int index) override ;
	GameObject* GetFirstBone()override;
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
	std::vector<MyGameObjectAnim*> goList;
	unsigned int Headindex;
	unsigned int numberofFrameList;
};
#endif // !HUMANOID
