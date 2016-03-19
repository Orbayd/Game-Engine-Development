#ifndef ANIM_2H
#define ANIM_2H

#include "Time.h"

#include "GameObject.h"

#define NUM_BONES 20

void SetAnimationHierarchy();
void SetAnimationData();

 void SetAnimationPose( GameObject *root, Time tCurr );

void ProcessAnimation( Time tCurr );
void findMaxTime( Time &tMax );

#endif