// Fill out your copyright notice in the Description page of Project Settings.

#include "SMRDemo.h"
#include "AnimGraphNode_SmrPose.h"


FString UAnimGraphNode_SmrPose::GetNodeCategory() const
{
	return TEXT("SMR Pose");
}

FLinearColor UAnimGraphNode_SmrPose::GetNodeTitleColor() const
{
	return FColor(0, 255, 0);
}

