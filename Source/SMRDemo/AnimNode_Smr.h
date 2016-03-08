// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "AnimNode_SkeletalControlBase.h"
#include "SmrMotion.h"
#include "AnimNode_Smr.generated.h"


/**
 *Applies an SMR skeleton to the Unreal representation of it
 */
USTRUCT()
struct FAnimNode_Smr : public FAnimNode_Base
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links)
	FPoseLink basePose;

	//SMR skeleton that will be applied to the mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkeletalControl, meta = (PinShownByDefault))
	ASmrMotion* SmrInput;

	//Unreal SkeletalMesh that is being used for the model being animated
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkeletalControl, meta = (PinShownByDefault))
	USkeletalMeshComponent* SkeletonComp;

public:
	FAnimNode_Smr();

	// FAnimNode_Base interface
	virtual void Initialize(const FAnimationInitializeContext& Context) override;
	virtual void CacheBones(const FAnimationCacheBonesContext & Context) override;
	virtual void Update(const FAnimationUpdateContext & Context) override;
	virtual void Evaluate(FPoseContext& Output) override;
	virtual void GatherDebugData(FNodeDebugData& DebugData) override;

};
