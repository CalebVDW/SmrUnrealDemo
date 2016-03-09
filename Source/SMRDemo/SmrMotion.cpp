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
	//Keep SMR animation up to date with Unreal scene
	m_framePause++;
	if (m_framePause > m_speed)
	{
		m_framePause = 0;
		m_frameIndex++;
	}
	if (uint32(m_frameIndex) >= m_motion.getNumFrames()) m_frameIndex = 0;
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

void ASmrMotion::PoseCharacterWorldSpace(UPoseableMeshComponent* mesh)
{
	SMRSkeleton skeleton = m_motion.getSkeleton(m_frameIndex);
	skeleton.setRotationOrder(TRANSLATIONFIRST);
	skeleton.setMode(SMRModeType::ABSOLUTEMODE);

	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString(rotator.ToString()));

	for (uint32 i = 0; i < skeleton.getNumJoints(); ++i)
	{
		FQuat orientation = USmrFunctions::RightCoordToLeft(USmrFunctions::MakeFQuat(skeleton.getJoint(i)->getOrientation()));
		FVector euler = orientation.Euler();
		FRotator rotator = FRotator::MakeFromEuler(euler);
		mesh->SetBoneRotationByName(FName(skeleton.getJoint(i)->getName().c_str()), rotator, EBoneSpaces::WorldSpace);
	}
}

const SMRSkeleton& ASmrMotion::getSkeleton() { return skeleton; }
