// Fill out your copyright notice in the Description page of Project Settings.

#include "SMRDemo.h"
#include "AnimGraphNode_SmrControl.h"

#define LOCTEXT_NAMESPACE "SmrNodes"


//PUBLIC INTERFACE/////////////////////////////////////////////////////////////////////////////////


void UAnimGraphNode_SmrControl::ValidateAnimNodeDuringCompilation(class USkeleton* ForSkeleton, class FCompilerResultsLog& MessageLog)
{
	/*
	*This function could contain a routine to check that the skeleton matches the animation file to be applied
	*/
	Super::ValidateAnimNodeDuringCompilation(ForSkeleton, MessageLog);
}

//SKELETAL CONTROL INTERFACE//
FText UAnimGraphNode_SmrControl::GetNodeTitle(ENodeTitleType::Type TitleType) const { return LOCTEXT("AnimGraphNode_SmrControl_Title", "Apply SMR Pose"); }
FText UAnimGraphNode_SmrControl::GetTooltipText() const { return LOCTEXT("AnimGraphNode_SmrControl_Tooltip", "Apply SMR pose to skeleton"); }
FText UAnimGraphNode_SmrControl::GetControllerDescription() const { return LOCTEXT("Apply SmrSkeleton", "Apply SmrSkeleton"); }
FString UAnimGraphNode_SmrControl::GetNodeCategory() const { return TEXT("SMR Nodes"); }

int32 UAnimGraphNode_SmrControl::GetWidgetCoordinateSystem(const USkeletalMeshComponent* SkelComp)
{
	return 1;
}

FVector UAnimGraphNode_SmrControl::GetWidgetLocation(const USkeletalMeshComponent* SkelComp, FAnimNode_SkeletalControlBase* AnimNode)
{
	USkeleton* Skeleton = SkelComp->SkeletalMesh->Skeleton;
	FVector WidgetLoc = FVector::ZeroVector;

	return WidgetLoc;
}


bool UAnimGraphNode_SmrControl::SetWidgetMode(const USkeletalMeshComponent* SkelComp, int32 InWidgetMode)
{
	return false;
}

FName UAnimGraphNode_SmrControl::FindSelectedBone()
{
	return FName(TEXT(""));
}

void UAnimGraphNode_SmrControl::DoTranslation(const USkeletalMeshComponent* SkelComp, FVector& Drag, FAnimNode_Base* InOutAnimNode)
{
	FAnimNode_Smr* ModifyBone = static_cast<FAnimNode_Smr*>(InOutAnimNode);

}

void UAnimGraphNode_SmrControl::DoRotation(const USkeletalMeshComponent* SkelComp, FRotator& Rotation, FAnimNode_Base* InOutAnimNode)
{
	FAnimNode_Smr* ModifyBone = static_cast<FAnimNode_Smr*>(InOutAnimNode);

}

void UAnimGraphNode_SmrControl::DoScale(const USkeletalMeshComponent* SkelComp, FVector& Scale, FAnimNode_Base* InOutAnimNode)
{
	FAnimNode_Smr* ModifyBone = static_cast<FAnimNode_Smr*>(InOutAnimNode);

}

void UAnimGraphNode_SmrControl::CopyNodeDataTo(FAnimNode_Base* OutAnimNode)
{
	FAnimNode_Smr* ModifyBone = static_cast<FAnimNode_Smr*>(OutAnimNode);

}

void UAnimGraphNode_SmrControl::CopyNodeDataFrom(const FAnimNode_Base* InNewAnimNode)
{
	
}
#undef LOCTEXT_NAMESPACE