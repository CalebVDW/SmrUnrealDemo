// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Smr.h"
#include "SmrMotion.generated.h"

UCLASS()
class SMRDEMO_API ASmrMotion : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASmrMotion();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	//Loads the skeleton from a BVH file
	void LoadSkeleton(FString path);
	
	//Loads the animation from a BVH file
	void LoadAnimation(FString path);

	const SMRSkeleton& getSkeleton();

private:
	int32 m_frameIndex;
	int32 m_framePause;
	int32 m_speed;

	SMRMotion m_motion;
	SMRSkeleton skeleton;
	
};
