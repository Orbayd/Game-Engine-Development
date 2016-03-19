#ifndef ANIMATION_FILE_H
#define ANIMATION_FILE_H
#include <vector>

struct headerBin
{
	int boneNum;
	int animNum;
};
struct BonesData
{
	int index;
	//trans
	float t_x;
	float t_y;
	float t_z;

	//rotation
	float r_x;
	float r_y;
	float r_z;

	//scale
	float s_x;
	float s_y;
	float s_z;

};

struct timeFrameBucket
{
	int timeFrame;
	std::vector<BonesData> bones;
};
struct AnimatinBucket
{
	char name[64];
	std::vector<timeFrameBucket> timeFrameList;
	int framenum;

};
struct animationTree
{
	int index;
	char Name[64];
	int ParentIndex;
};

#endif // !ANIMATION_FILE_H