#include <stdio.h>

#include "DebugOut.h"
#include "Anim.h"
#include "Constants.h"
#include "VectApp.h"
#include "QuatApp.h"
#include "FrameBucket.h"

extern Frame_Bucket *pHead;

void findMaxTime( Time &tMax )
{
	Frame_Bucket *pTmp = pHead->nextBucket;

	while( pTmp->nextBucket != 0 )
	{
		pTmp = pTmp->nextBucket;
	}

	tMax = pTmp->KeyTime;
}

void ProcessAnimation( Time tCurr )
{
	//out("time:%f\n",tCurr/Time(TIME_ONE_SECOND));
	Frame_Bucket *pTmp = pHead->nextBucket;

	// Get the result bone array
	// Remember the firs Frame is the result
	Bone *bResult = pHead->pBone;

	// First one is the result, skip it
	pTmp = pHead->nextBucket;
	
	// Find which key frames
	while( tCurr >= pTmp->KeyTime  && pTmp->nextBucket != 0 )
	{
		pTmp = pTmp->nextBucket;
	}
	//out("\n---KeyFrame:<%d>:\n",pTmp->index);
	//out("\n---KeyFrame:<%d>:\n",pTmp->prevBucket->index);

	// pTmp is the "B" key frame
	// pTmp->prev is the "A" key frame
	Frame_Bucket *pA = pTmp->prevBucket;
	Frame_Bucket *pB = pTmp;

	// find the "S" of the time
	float tS = (tCurr - pA->KeyTime)  /(pB->KeyTime - pA->KeyTime);
	
	// interpolate to 
	Bone *bA = pA->pBone;
	Bone *bB = pB->pBone;

   // Interpolate to tS time, for all bones
	for( int i = 0; i < NUM_BONES; i++ )
	{
		// interpolate ahoy!
		VectApp::Lerp(bResult->T, bA->T, bB->T, tS);
		QuatApp::Slerp(bResult->Q, bA->Q, bB->Q, tS);
		VectApp::Lerp(bResult->S, bA->S, bB->S, tS);
		
		// advance the pointer
		bA++;
		bB++;
		bResult++;
   }

}