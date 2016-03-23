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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkeletalControl, meta = (PinShownByDefault))
	ASmrMotion* SmrInput;


public:
	FAnimNode_SmrPose()
		: FAnimNode_Base() {}

	virtual void Evaluate(FPoseContext& Output) override;
	virtual void GatherDebugData(FNodeDebugData& DebugData) override;

};
