#ifndef FRAME_BUCKET
#define FRAME_BUCKET

#include "Timer.h"
#include "Vect.h"
#include "Quat.h"

struct Bone 
{
   Vect  T;
   Quat  Q;
   Vect  S;
};
struct Frame_Bucket_List
{
	Frame_Bucket_List():nextlist(0),prevlist(0){}
	Frame_Bucket_List *nextlist;
	Frame_Bucket_List *prevlist;
};
struct Frame_Bucket : public Frame_Bucket_List
{
	Frame_Bucket *nextBucket;
	Frame_Bucket *prevBucket;
	Time		  KeyTime;
	Bone		  *pBone;
	unsigned int index;
};

#endif