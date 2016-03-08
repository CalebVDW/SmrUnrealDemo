// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AnimGraphNode_SkeletalControlBase.h"
#include "AnimNode_Smr.h"
#include "AnimGraphNode_SmrControl.generated.h"

/**
 * 
 */
UCLASS()
class SMRDEMO_API UAnimGraphNode_SmrControl : public UAnimGraphNode_Base
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = Settings)
	FAnimNode_Smr Node;
public:
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FText GetTooltipText() const override;

	virtual FString GetNodeCategory() const override;
	virtual void ValidateAnimNodeDuringCompilation(class USkeleton* ForSkeleton, class FCompilerResultsLog& MessageLog) override;

};
