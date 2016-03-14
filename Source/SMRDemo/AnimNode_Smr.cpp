// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "SMRDemo.h"
#include "SmrFunctions.h"
#include "AnimNode_Smr.h"
#include "AnimationRuntime.h"

/////////////////////////////////////////////////////
// FAnimNode_ModifyBone

FAnimNode_Smr::FAnimNode_Smr()
	:FAnimNode_SkeletalControlBase()
{
}

//SMR logic goes in here
void FAnimNode_Smr::EvaluateBoneTransforms(USkeletalMeshComponent* SkelComp, FCSPose<FCompactPose>& MeshBases, TArray<FBoneTransform>& OutBoneTransforms)
{
	check(OutBoneTransforms.Num() == 0);
	const FBoneContainer BoneContainer = MeshBases.GetPose().GetBoneContainer();

	//Loop through all bones
	for (int i = 0; i < BoneContainer.GetNumBones(); ++i)
	{
		//Retrieve SMR skeleton
		SMRSkeleton smrSkeleton;
		if (SmrInput)
			smrSkeleton = SmrInput->getSkeleton();
		else
			break;
		smrSkeleton.setMode(SMRModeType::RELATIVEMODE);
		smrSkeleton.setRotationOrder(TRANSLATIONFIRST);

		//Get SMR bone
		FName boneName = BoneContainer.GetReferenceSkeleton().GetBoneName(i);
		SMRJoint* smrBone = smrSkeleton.getJointByName(std::string(TCHAR_TO_UTF8(*boneName.ToString())));
		if (!smrBone)
			break;

		//Set the parent space transformations
		FTransform newBoneTransform;
		newBoneTransform.SetTranslation(USmrFunctions::MakeFVector(smrBone->getPosition()));
		newBoneTransform.SetRotation(USmrFunctions::RightCoordToLeft(USmrFunctions::MakeFQuat(smrBone->getOrientation())));

		//Convert from parent space to component space
		FAnimationRuntime::ConvertBoneSpaceTransformToCS(SkelComp, MeshBases, newBoneTransform,
			FCompactPoseBoneIndex(i), EBoneControlSpace::BCS_ParentBoneSpace);

		OutBoneTransforms.Add(FBoneTransform(FCompactPoseBoneIndex(i), newBoneTransform));
	}
}

//Initialize any bone references??
void FAnimNode_Smr::InitializeBoneReferences(const FBoneContainer& RequiredBones)
{
	//TODO//
	//Get a list of FBoneReferences to modify (all of them) and call initialize on them

	//This may not be necessary since it seems to only deal with FBoneReferences
}


/*
void FAnimNode_Smr::Evaluate(FPoseContext& Output)
{
	basePose.Evaluate(Output);

	FReferenceSkeleton unrealSkeleton = Output.Pose.GetBoneContainer().GetReferenceSkeleton();

	SMRSkeleton smrSkeleton;
	if (SmrInput)
		smrSkeleton = SmrInput->getSkeleton();
	else
		return;
	smrSkeleton.setMode(SMRModeType::RELATIVEMODE);
	smrSkeleton.setRotationOrder(TRANSLATIONFIRST);

	//Step through all bones in the output context
	for (int i = 0; i < Output.Pose.GetNumBones(); ++i)
	{	
		//Get the SMR bone that corresponds to the current Unreal bone
		FName boneName = unrealSkeleton.GetBoneName(i);
		SMRJoint* smrBone = smrSkeleton.getJointByName(std::string(TCHAR_TO_UTF8(*boneName.ToString())));

		if (smrBone)
		{
			//Build a transform from the SMR bone data
			FTransform newTransform;
			newTransform.SetTranslation(USmrFunctions::MakeFVector(smrBone->getPosition()));
			newTransform.SetRotation(USmrFunctions::RightCoordToLeft(USmrFunctions::MakeFQuat(smrBone->getOrientation())));


			//Apply transform to output pose
			//FCompactPose uses indexing operator to access transforms of bones
			//Bones are actually stored only as transforms
			Output.Pose[FCompactPoseBoneIndex(i)] = newTransform;
		}
	}
}
*/
