// Fill out your copyright notice in the Description page of Project Settings.

#include "SMRDemo.h"
#include "AnimGraphNode_SmrControl.h"

#define LOCTEXT_NAMESPACE "SmrNodes"


//PUBLIC INTERFACE/////////////////////////////////////////////////////////////////////////////////
FText UAnimGraphNode_SmrControl::GetNodeTitle(ENodeTitleType::Type TitleType) const { return LOCTEXT("AnimGraphNode_SmrControl_Title", "Apply SMR Pose"); }
FText UAnimGraphNode_SmrControl::GetTooltipText() const { return LOCTEXT("AnimGraphNode_SmrControl_Tooltip", "Apply SMR pose to skeleton"); }

FString UAnimGraphNode_SmrControl::GetNodeCategory() const { return TEXT("SMR Nodes"); }

void UAnimGraphNode_SmrControl::ValidateAnimNodeDuringCompilation(class USkeleton* ForSkeleton, class FCompilerResultsLog& MessageLog)
{
	/*
	*This function could contain a routine to check that the skeleton matches the animation file to be applied
	*/
}