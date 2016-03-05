// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "SMRDemo.h"

#include "AnimNode_Smr.h"
#include "AnimationRuntime.h"

/////////////////////////////////////////////////////
// FAnimNode_ModifyBone

FAnimNode_Smr::FAnimNode_Smr()
	:FAnimNode_SkeletalControlBase()
{
}

void FAnimNode_Smr::GatherDebugData(FNodeDebugData& DebugData)
{
	
}

void FAnimNode_Smr::EvaluateBoneTransforms(USkeletalMeshComponent* SkelComp, FCSPose<FCompactPose>& MeshBases, TArray<FBoneTransform>& OutBoneTransforms)
{
	SMRSkeleton skeleton = SmrInput->getSkeleton();
	uint32 numBones = skeleton.getNumJoints();

	const FBoneContainer BoneContainer = MeshBases.GetPose().GetBoneContainer();

	//Apply rotation to each bone
	for (int i = 0; i < numBones; ++i)
	{
		FBoneReference BoneToModify;

		// Convert to Bone Space.
		FAnimationRuntime::ConvertCSTransformToBoneSpace(SkelComp, MeshBases, NewBoneTM, CompactPoseBoneToModify, RotationSpace);

		//Get data from SMR
		FQuat newRotation;		


		
		NewBoneTM.SetRotation(newRotation);

		// Convert back to Component Space.
		FAnimationRuntime::ConvertBoneSpaceTransformToCS(SkelComp, MeshBases, NewBoneTM, CompactPoseBoneToModify, RotationSpace);
	}
	
}

bool FAnimNode_Smr::IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones) 
{
	// if both bones are valid
	return true;
}

void FAnimNode_Smr::InitializeBoneReferences(const FBoneContainer& RequiredBones) 
{
	
}

SMRSkeleton FAnimNode_Smr::getCurrentSkeleton(){return SmrInput->getSkeleton(): }