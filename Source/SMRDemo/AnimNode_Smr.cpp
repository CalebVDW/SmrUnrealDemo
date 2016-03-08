// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "SMRDemo.h"
#include "SmrFunctions.h"
#include "AnimNode_Smr.h"
#include "AnimationRuntime.h"

/////////////////////////////////////////////////////
// FAnimNode_ModifyBone

FAnimNode_Smr::FAnimNode_Smr()
	:FAnimNode_Base()
{
}

void FAnimNode_Smr::Initialize(const FAnimationInitializeContext& Context)
{
	FAnimNode_Base::Initialize(Context);
	basePose.Initialize(Context);

}

void FAnimNode_Smr::CacheBones(const FAnimationCacheBonesContext& Context)
{
	basePose.CacheBones(Context);
}

void FAnimNode_Smr::Update(const FAnimationUpdateContext& Context)
{
	basePose.Update(Context);
}

void FAnimNode_Smr::Evaluate(FPoseContext& Output)
{
	//I have no idea what this evaluate function does
	FPoseContext NewPoseContext(Output);
	basePose.Evaluate(Output);

	FBoneContainer outputBones = Output.Pose.GetBoneContainer();
	SMRSkeleton smrSkeleton = SmrInput->getSkeleton();

	//Step through all bones in the output context
	for (int i = 0; i < outputBones.GetNumBones(); ++i)
	{	
		//Get name of current bone
		FName boneName = SkeletonComp->GetBoneName(i);
		SMRJoint* smrBone = smrSkeleton.getJointByName(std::string(TCHAR_TO_UTF8(*boneName.ToString())));

		//Build a transform from the SMR bone data
		FTransform newTransform;
		newTransform.SetTranslation(USmrFunctions::MakeFVector(smrBone->getPosition()));
		newTransform.SetRotation(USmrFunctions::MakeFQuat(smrBone->getOrientation()));

		//Apply transform to output pose
		//FCompactPose uses indexing operator to access transforms of bones
		//Bones are actually stored only as transforms
		Output.Pose[FCompactPoseBoneIndex(i)] = newTransform;
	}

}
void FAnimNode_Smr::GatherDebugData(FNodeDebugData& DebugData)
{
	/*Not sure what is supposed to go here but I'm sure I'll figure it out one day*/
}