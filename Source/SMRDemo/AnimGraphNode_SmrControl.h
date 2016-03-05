// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AnimGraphNode_SkeletalControlBase.h"
#include "AnimNode_Smr.h"
#include "AnimGraphNode_SmrControl.generated.h"

/**
 * 
 */
UCLASS()
class SMRDEMO_API UAnimGraphNode_SmrControl : public UAnimGraphNode_SkeletalControlBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = Settings)
	FAnimNode_Smr Node;
public:


protected:
	virtual void DoRotation(const USkeletalMeshComponent* SkelComp, FRotator& Rotation, FAnimNode_Base* InOutAnimNode) override;


};
