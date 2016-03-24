#pragma once

#include "SMRDemo.h"
#include "Private/AnimGraphPrivatePCH.h"
#include "SmrFunctions.h"
#include "AnimNode_SmrPose.h"
#include "AnimationRuntime.h"

FAnimNode_SmrPose::FAnimNode_SmrPose()
{

}

//Apply SMR animation data to the skeleton
void FAnimNode_SmrPose::Evaluate(FPoseContext& Output)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Black, FString(TEXT("Evaluating")));

	//Validate input from SMR
	SMRSkeleton smrSkeleton;
	if (!SmrInput)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Black, FString(TEXT("Null SMR input")));
		return;
	}
	smrSkeleton = SmrInput->getSkeleton();

	smrSkeleton.setMode(SMRModeType::RELATIVEMODE);
	smrSkeleton.setRotationOrder(TRANSLATIONFIRST);

	FBoneContainer boneContainer = Output.Pose.GetBoneContainer();
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Black, FString(TEXT("SMR Input is valid")));


	//Step through SMR bones
	for (uint32 i = 0; i < smrSkeleton.getNumJoints(); ++i)
	{
		//Get current SMR bone
		SMRJoint* joint = smrSkeleton.getJoint(i);
		FName boneName(joint->getName().c_str());
		uint32 unrealIndex = boneContainer.GetPoseBoneIndexForBoneName(boneName);
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Black, boneName.ToString());


		//Build a transform for the SMR bone
		FTransform boneTransform;
		boneTransform.SetRotation(USmrFunctions::RightCoordToLeft(USmrFunctions::MakeFQuat(joint->getOrientation())));
		Output.Pose[FCompactPoseBoneIndex(unrealIndex)] = boneTransform;
	}

	/*
	for (const FCompactPoseBoneIndex BoneIndex : Output.Pose.ForEachBoneIndex())
	{
		const int32 SkeletonBoneIndex = GetBoneContainer().GetSkeletonIndex(BoneIndex);

		// Pose bone index should always exist in Skeleton
		checkSlow(SkeletonBoneIndex != INDEX_NONE);
		Bones[BoneIndex.GetInt()] = SkeletonRefPose[SkeletonBoneIndex];
	}
	*/

}

void FAnimNode_SmrPose::CacheBones(const FAnimationCacheBonesContext& Context)
{

}
void FAnimNode_SmrPose::Update(const FAnimationUpdateContext& Context)
{
	EvaluateGraphExposedInputs.Execute(Context);
}
void FAnimNode_SmrPose::Initialize(const FAnimationInitializeContext& Context)
{
	FAnimNode_Base::Initialize(Context);
}
void FAnimNode_SmrPose::GatherDebugData(FNodeDebugData& DebugData)
{
	FString DebugLine = DebugData.GetNodeName(this);
}