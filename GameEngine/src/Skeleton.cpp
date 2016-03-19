#include "Skeleton.h"

Skeleton
::Skeleton
()
{
	animationSpeed = 1.0f;
	minSpeed  =0.005f;
	maxSpeed = 2.0f;
	oldSpeed = minSpeed;
}

Skeleton
::~Skeleton
()
{
}
void Skeleton::changeSpeed(float coe)
{
	if(animationSpeed>maxSpeed)
		animationSpeed=maxSpeed;
	else if(animationSpeed<minSpeed)
	{
		animationSpeed = minSpeed;
	}
	else
		animationSpeed*=coe;
	
}

void Skeleton::rewind()
{

	animationSpeed = -animationSpeed;
}
void Skeleton::Pause()
{
	if(animationSpeed!=0)
	{
		oldSpeed = animationSpeed;
		animationSpeed = 0.0f;
	}
}
void Skeleton::Start()
{
	animationSpeed = oldSpeed;
}
