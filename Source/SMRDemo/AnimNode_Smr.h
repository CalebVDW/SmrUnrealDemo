// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "AnimNode_SkeletalControlBase.h"
#include "SmrMotion.h"
#include "AnimNode_Smr.generated.h"


/**
 *Applies an SMR skeleton to the Unreal representation of it
 */
USTRUCT()
struct FAnimNode_Smr : public FAnimNode_SkeletalControlBase
{
	GENERATED_USTRUCT_BODY()

	//SMR skeleton that will be applied to the mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkeletalControl, meta = (PinShownByDefault))
	ASmrMotion* SmrInput;

	FAnimNode_Smr();

	// FAnimNode_Base interface
	virtual void GatherDebugData(FNodeDebugData& DebugData) override;

	// FAnimNode_SkeletalControlBase interface
	virtual void EvaluateBoneTransforms(USkeletalMeshComponent* SkelComp, FCSPose<FCompactPose>& MeshBases, TArray<FBoneTransform>& OutBoneTransforms) override;
	virtual bool IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones) override;
	// End of FAnimNode_SkeletalControlBase interface

	SMRSkeleton getCurrentSkeleton();

private:
	// FAnimNode_SkeletalControlBase interface
	virtual void InitializeBoneReferences(const FBoneContainer& RequiredBones) override;
	// End of FAnimNode_SkeletalControlBase interface
};
