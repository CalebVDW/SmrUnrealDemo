// Fill out your copyright notice in the Description page of Project Settings.

#include "SMRDemo.h"
#include "AnimGraphNode_SmrControl.h"


void UAnimGraphNode_SmrControl::DoRotation(const USkeletalMeshComponent* SkelComp, FRotator& Rotation, FAnimNode_Base* InOutAnimNode)
{
	FAnimNode_Smr* ApplySmrPose = static_cast<FAnimNode_Smr*>(InOutAnimNode);
}

