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


public:
	FAnimNode_Smr();


protected:
	//SMR logic goes in here
	virtual void EvaluateBoneTransforms(USkeletalMeshComponent* SkelComp, FCSPose<FCompactPose>& MeshBases, TArray<FBoneTransform>& OutBoneTransforms) override;
	
	//Some sort of skeleton validation would be good here, but return true is fine for now
	virtual bool IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones) override { return true; }

	//Initialize any bone references??
	virtual void InitializeBoneReferences(const FBoneContainer& RequiredBones) override;

private:
	TArray<FBoneReference> bonesToModify;
};
