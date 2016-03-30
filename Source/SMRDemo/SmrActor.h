// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Smr.h"
#include "Classes/Components/PoseableMeshComponent.h"
#include "SmrActor.generated.h"


/*
* Stores a skeleton and motion file loaded with the SMR library
* Skeleton is automatically updated every frame
* The getSkeleton() method provides access to the pose for the current frame
*/
UCLASS()
class SMRDEMO_API ASmrActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASmrActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	//Loads the skeleton from a BVH file
	UFUNCTION(BlueprintCallable, Category = SMR)
		void LoadSkeleton(FString path);

	//Loads the animation from a BVH file
	UFUNCTION(BlueprintCallable, Category = SMR)
		void LoadAnimation(FString path);

	//Apply world space pose to a poseable mesh
	UFUNCTION(BlueprintCallable, Category = SMR)
		void PoseCharacterWorldSpace(UPoseableMeshComponent* mesh);

	//Apply local space pose to a poseable mesh
	UFUNCTION(BlueprintCallable, Category = SMR)
		void PoseCharacterLocalSpace(UPoseableMeshComponent* mesh);

	const SMRSkeleton& getSkeleton();

private:
	int32 m_frameIndex;
	int32 m_framePause;
	int32 m_speed;

	SMRMotion m_motion;
	SMRSkeleton skeleton;

	void TransformChildren(UPoseableMeshComponent* mesh, SMRJoint* parent);
	void TransformBone(UPoseableMeshComponent* mesh, SMRJoint* bone);
};
