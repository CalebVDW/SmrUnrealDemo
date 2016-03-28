// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Smr.h"
#include "SmrFunctions.generated.h"

/*A set of convenience functions for converting math types and other misc tasks
 * 
 */
UCLASS()
class SMRDEMO_API USmrFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	//Creates a FQuat struct from a SMRQuaternion. Does no conversions between coords. Simply copies x, y, z, w values
	static FQuat MakeFQuat(SMRQuaternion q);
	static FQuat RightCoordToLeft(FQuat q);
	static FQuat RightCoordToLeft(SMRQuaternion q);

	static FVector RightCoordToLeft(SMRVector3);
	static FVector MakeFVector(SMRVector3);
};
