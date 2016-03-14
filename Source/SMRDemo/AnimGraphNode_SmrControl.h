// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AnimGraphNode_SkeletalControlBase.h"
#include "AnimNode_Smr.h"
#include "EdGraph/EdGraphNodeUtils.h"
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
	virtual void ValidateAnimNodeDuringCompilation(class USkeleton* ForSkeleton, class FCompilerResultsLog& MessageLog) override;

	virtual FText UAnimGraphNode_SmrControl::GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FText UAnimGraphNode_SmrControl::GetTooltipText() const override;
	virtual FString GetNodeCategory() const override;

	virtual FText GetControllerDescription() const override;
	virtual int32 GetWidgetCoordinateSystem(const USkeletalMeshComponent* SkelComp) override;
	virtual FVector GetWidgetLocation(const USkeletalMeshComponent* SkelComp, struct FAnimNode_SkeletalControlBase* AnimNode) override;
	virtual int32 GetWidgetMode(const USkeletalMeshComponent* SkelComp) override { return 0; }
	virtual int32 ChangeToNextWidgetMode(const USkeletalMeshComponent* SkelComp, int32 InCurWidgetMode) override { return 0; }
	virtual bool SetWidgetMode(const USkeletalMeshComponent* SkelComp, int32 InWidgetMode) override;
	virtual FName FindSelectedBone() override;
	virtual void DoTranslation(const USkeletalMeshComponent* SkelComp, FVector& Drag, FAnimNode_Base* InOutAnimNode) override;
	virtual void DoRotation(const USkeletalMeshComponent* SkelComp, FRotator& Rotation, FAnimNode_Base* InOutAnimNode) override;
	virtual void DoScale(const USkeletalMeshComponent* SkelComp, FVector& Drag, FAnimNode_Base* InOutAnimNode) override;
	virtual void CopyNodeDataTo(FAnimNode_Base* OutAnimNode) override;
	virtual void CopyNodeDataFrom(const FAnimNode_Base* InNewAnimNode) override;

};
