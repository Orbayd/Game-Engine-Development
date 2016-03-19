#ifndef MYANIMATOR_H
#define MYANIMATOR_H
class Time;
class Quat;
struct Frame_Bucket;
class MyAnimator

{
public:
	MyAnimator();
	~MyAnimator();
	void findMaxTime( Time &tMax,Frame_Bucket *pHead );
	void ProcessAnimation( Time tCurr,Frame_Bucket *pHead,int numberofBones );
	void MagicSlerp( Quat &result, const Quat &source, const Quat &target, const float slerpFactor );
private:

};



#endif // !MYANIMATOR_H
