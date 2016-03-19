#ifndef ANIMATION_MANAGER_H
#define ANIMATION_MANAGER_H
#include "Skeleton.h"

class Time;
class AnimationManager
{
public:
	AnimationManager();
	~AnimationManager();
	void AddSkeleton(SkeletonNodeLink * pAnimNode);
	void ProcessAnimation();
	void ChangeAnimationSpeed(float coe);
	void ChangeAnimation(SkeletonType Type);
	void Rewind();
	static AnimationManager* GetInstance();
	void Start();
	void Pause();
	void Delete(SkeletonType type);
private:
	SkeletonNodeLink * pHead;
};






#endif // !ANIMATION_MANAGER_H
