// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AnimGraphNode_Base.h"
#include "AnimNode_SmrPose.h"
#include "EdGraph/EdGraphNodeUtils.h"
#include "AnimGraphNode_SmrPose.generated.h"

/**
 * 
 */
UCLASS()
class SMRDEMO_API UAnimGraphNode_SmrPose : public UAnimGraphNode_Base
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = SMR)
	FAnimNode_SmrPose Node;

	virtual FString GetNodeCategory() const override;
	virtual FLinearColor GetNodeTitleColor() const override;
	
};
