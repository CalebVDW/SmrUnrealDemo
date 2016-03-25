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
//Applies transformations recursively since they are in parent space coords
void FAnimNode_SmrPose::Evaluate(FPoseContext& Output)
{
	//Validate input from SMR
	if (!SmrInput)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Black, FString(TEXT("Null SMR input")));
		return;
	}
	//Apply correct settings to skeleton
	//TODO//Make sure that the getSkeleton function is working as intended 
	smrSkeleton = SmrInput->getSkeleton();
	smrSkeleton.setMode(SMRModeType::RELATIVEMODE);
	smrSkeleton.setRotationOrder(TRANSLATIONFIRST);

	SMRJoint* rootBone = smrSkeleton.getRootJoint();
	if (!rootBone)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Black, FString(TEXT("No root joint in SMRSkeleton!")));
		return;
	}
	EvaluateBone(Output, rootBone, nullptr);
	EvaluateChildren(Output, rootBone);
}

void FAnimNode_SmrPose::EvaluateChildren(FPoseContext& Output, SMRJoint* parent)
{
	//Get a list of all children
	if (!parent)
		return;
	std::vector<uint32> children = smrSkeleton.getJointChildren(parent->getName());

	//Evaluate each child joint
	for (int i = 0; i < children.size(); ++i)
	{
		SMRJoint* currentChild = smrSkeleton.getJoint(children[i]);
		EvaluateBone(Output, currentChild, parent);
	}
}
void FAnimNode_SmrPose::EvaluateBone(FPoseContext& Output, SMRJoint* joint, SMRJoint* parent)
{
	if (!joint)
		return;
	//Build a transform in parent space
	FTransform boneTransform;
	boneTransform.SetRotation(USmrFunctions::RightCoordToLeft(joint->getOrientation()));
	boneTransform.SetLocation(USmrFunctions::RightCoordToLeft(joint->getPosition()));

	//Get index of the bone in the Unreal Pose
	FName boneName(joint->getName().c_str());
	FBoneContainer boneContainer = Output.Pose.GetBoneContainer();
	uint32 unrealIndex = boneContainer.GetPoseBoneIndexForBoneName(boneName);

	if (parent)
	{
		//Convert parent space to component space
		USkeletalMeshComponent* SkelComp = Output.AnimInstance->GetSkelMeshComponent();
		FCSPose<FCompactPose> fcs = Output.Pose;
		FAnimationRuntime::ConvertBoneSpaceTransformToCS(SkelComp, fcs, boneTransform, FCompactPoseBoneIndex(unrealIndex), EBoneControlSpace::BCS_ParentBoneSpace);

		//Convert component space back to local spae
		FAnimationRuntime::ConvertCSTransformToBoneSpace(SkelComp, fcs, boneTransform, FCompactPoseBoneIndex(unrealIndex), RotationSpace);
		
	}

	

	//Apply transformation to Unreal pose
	Output.Pose[FCompactPoseBoneIndex(unrealIndex)] = boneTransform;
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