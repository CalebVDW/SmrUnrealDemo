// Fill out your copyright notice in the Description page of Project Settings.

#include "SMRDemo.h"
#include "SmrFunctions.h"
#include "SmrMotion.h"


// Sets default values
ASmrMotion::ASmrMotion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASmrMotion::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASmrMotion::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ASmrMotion::LoadSkeleton(FString path)
{
	std::string skeletonFilePath = "C:/Git/SMRFork/data/bvh/benTest.bvh";
	skeleton = loadSkeletonFromBVH(getFileName(skeletonFilePath));
	skeleton.setRotationOrder(ROTATIONFIRST);

	for (uint32 i = 0; i < skeleton.getNumJoints(); ++i)
	{
		//Replaces points with underscores because that is what Unreal does when it imports 
		std::string boneName = skeleton.getJoint(i)->getName();
		auto pos = boneName.find('.');
		while (pos != std::string::npos)
		{
			boneName.replace(pos, 1, "_");
			pos = boneName.find('.');
		}
		skeleton.getJoint(i)->setName(boneName);
		UE_LOG(LogTemp, Warning, TEXT("Bone Name: %s"), *FString(skeleton.getJoint(i)->getName().c_str()));
	}
}

void ASmrMotion::LoadAnimation(FString path)
{
	std::string motionFilePath = "C:/Git/SMRFork/data/bvh/benTest.bvh";
	m_motion = loadMotionFromBVH(motionFilePath);
}

const SMRSkeleton& ASmrMotion::getSkeleton() { return skeleton; }
