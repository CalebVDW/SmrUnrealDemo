#pragma once
// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Animation/AnimNodeBase.h"
#include "SmrMotion.h"
#include "AnimNode_SmrPose.generated.h"


/**
*Applies an SMR skeleton to the Unreal representation of it
*/
USTRUCT()
struct FAnimNode_SmrPose : public FAnimNode_Base
{
	GENERATED_USTRUCT_BODY()

	//SMR skeleton that will be applied to the mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (PinShownByDefault))
	mutable ASmrMotion* SmrInput;


public:
	FAnimNode_SmrPose();

	virtual void Evaluate(FPoseContext& Output) override;
	virtual void GatherDebugData(FNodeDebugData& DebugData) override;
	virtual void Update(const FAnimationUpdateContext& Context) override;
	virtual void Initialize(const FAnimationInitializeContext& Context) override;
	virtual void CacheBones(const FAnimationCacheBonesContext& Context) override;

};
