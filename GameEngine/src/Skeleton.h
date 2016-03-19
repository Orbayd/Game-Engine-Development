#ifndef SKELETON_H
#define SKELETON_H
#include<vector>
#include "AnimationFile.h"
#include "MyAnimator.h"
#define MAXANIMATION 10

class GameObject;
class Time;
struct Frame_Bucket;
class PCSNode;
class MyGameObjectAnim;
enum class SkeletonType
{
	TEDDY,
	HUMAN,
};
class SkeletonNodeLink
{
public:
	SkeletonNodeLink()
	{
		this->next = 0;
		this->prev = 0;
	}

	SkeletonNodeLink *next;
	SkeletonNodeLink *prev;
};


class Skeleton: public SkeletonNodeLink

{
public:
	Skeleton();
	~Skeleton();
	virtual void ReadAnimationData(const char * filename)=0;
	virtual void SetAnimationHierarchy()=0;
	virtual void SetAnimationPose()=0;
	virtual void setBonePose( GameObject *node )=0;
	virtual void walk_anim_node( GameObject *node )=0;
	virtual void SetAnimationData()=0;
	virtual MyGameObjectAnim* findByIndex(std::vector<MyGameObjectAnim*> list, int index)=0;

	virtual Frame_Bucket * getHeadFrameBucket()=0;
	virtual void ProcessAnimation(Time tCurr)=0;
	virtual void findMaxTime(Time &tMax)=0;

	virtual void ChangeAnimation()=0;
	virtual GameObject* GetFirstBone()=0;
	void changeSpeed(float coe);
	void rewind(); 
	
	
	SkeletonType sType;
	void Pause();
	void Start();
private:

protected:
	unsigned int boneSize;
	float animationSpeed;
	float boneWidth;
	float maxSpeed;
	float minSpeed;
	float oldSpeed;
};



#endif // !SKELETON_H
