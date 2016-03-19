#include "MyAnimator.h"
#include "Time.h"
#include "FrameBucket.h"
#include "MathApp.h"
#include "MathEngine.h"
#include "Anim.h"// delete this one
#include <math.h>
MyAnimator
::MyAnimator
()
{
}

MyAnimator
::~MyAnimator
()
{
}

void MyAnimator::findMaxTime( Time &tMax, Frame_Bucket *pHead)
{
	Frame_Bucket *pTmp = pHead->nextBucket;

	while( pTmp->nextBucket != 0 )
	{
		pTmp = pTmp->nextBucket;
	}

	tMax = pTmp->KeyTime;
}

void MyAnimator::ProcessAnimation( Time tCurr ,Frame_Bucket *pHead ,int numberofBones)
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
	for( int i = 0; i < numberofBones ; i++ )
	{
		// interpolate ahoy!
		VectApp::Lerp(bResult->T, bA->T, bB->T, tS);
		//QuatApp::Slerp(bResult->Q, bA->Q, bB->Q, tS);
		MagicSlerp(bResult->Q, bA->Q, bB->Q, tS);
		VectApp::Lerp(bResult->S, bA->S, bB->S, tS);
		
		// advance the pointer
		bA++;
		bB++;
		bResult++;
   }

}

void MyAnimator::MagicSlerp( Quat &result, const Quat &source, const Quat &tar, const float slerpFactor )
{
	Quat target;
	
	const float Quat_Epsilon = 0.001f;

	float  cosom  = source.dot(tar);

	if(cosom<0.0f)
	{
		cosom= -cosom;
		target = -tar;
	
	}
	else
		target = tar;

	float tarFactor  = slerpFactor;
	float srcFactor = 1.0f- slerpFactor;

	if(cosom<(1.0f- Quat_Epsilon))
	{
		const float omega = acosf(cosom);
		const float sinom = 1.0f /sinf(omega);
		
		srcFactor = sinf(srcFactor *omega) *sinom;
		tarFactor = sinf(tarFactor* omega)* sinom;
	
	
	}
	result.set( source[x] * srcFactor + target[x]* tarFactor,
				source[y] * srcFactor + target[y]* tarFactor,
				source[z] * srcFactor + target[z]* tarFactor,
				source[w] * srcFactor + target[w]* tarFactor
		);


}