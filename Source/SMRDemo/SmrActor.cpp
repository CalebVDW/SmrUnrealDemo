// Fill out your copyright notice in the Description page of Project Settings.

#include "SMRDemo.h"
#include "SmrFunctions.h"
#include "SmrActor.h"


// Sets default values
ASmrActor::ASmrActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASmrActor::BeginPlay()
{

}

// Called every frame
void ASmrActor::Tick(float DeltaTime)
{
	//Keep SMR animation up to date with Unreal scene
	m_framePause++;
	if (m_framePause > m_speed)
	{
		m_framePause = 0;
		m_frameIndex++;
	}
	if (uint32(m_frameIndex) >= m_motion.getNumFrames()) m_frameIndex = 0;
}

void ASmrActor::LoadSkeleton(FString path)
{
    FString rootDir = FPaths::RootDir();
    std::string stdRootDir(TCHAR_TO_UTF8(*rootDir));
	std::string skeletonFilePath = stdRootDir + "SMR/data/bvh/benTest.bvh";
	skeleton = loadSkeletonFromBVH(getFileName(skeletonFilePath));
	skeleton.setRotationOrder(TRANSLATIONFIRST);

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

void ASmrActor::LoadAnimation(FString path)
{
    FString rootDir = FPaths::RootDir();
    std::string stdRootDir(TCHAR_TO_UTF8(*rootDir));
    std::string motionFilePath = stdRootDir + "SMR/data/bvh/benTest.bvh";
	m_motion = loadMotionFromBVH(motionFilePath);
}

void ASmrActor::PoseCharacterWorldSpace(UPoseableMeshComponent* mesh)
{
	//Get skeleton and apply correct settings
	skeleton = m_motion.getSkeleton(m_frameIndex);
	skeleton.setRotationOrder(TRANSLATIONFIRST);
	skeleton.setMode(SMRModeType::ABSOLUTEMODE);

	//Apply rotation to each bone in the Unreal skeleton
	for (uint32 i = 0; i < skeleton.getNumJoints(); ++i)
	{
		FQuat orientation = USmrFunctions::RightCoordToLeft(USmrFunctions::MakeFQuat(skeleton.getJoint(i)->getOrientation()));
		FVector euler = orientation.Euler();
		FRotator rotator = FRotator::MakeFromEuler(euler);

		//Rotations are applied to bones with identical names so the skeletons must match exactly 
		mesh->SetBoneRotationByName(FName(skeleton.getJoint(i)->getName().c_str()), rotator, EBoneSpaces::WorldSpace);
	}
}

void ASmrActor::PoseCharacterLocalSpace(UPoseableMeshComponent* mesh)
{
	//Initialize skeleton
	skeleton = m_motion.getSkeleton(m_frameIndex);
	skeleton.setRotationOrder(TRANSLATIONFIRST);
	skeleton.setMode(SMRModeType::RELATIVEMODE);

	//Transform root bone
	SMRJoint* rootJoint = skeleton.getRootJoint();
	TransformBone(mesh, rootJoint);

	//Recursively transform children
	TransformChildren(mesh, rootJoint);

	//TODO//Transform root
}

void ASmrActor::TransformChildren(UPoseableMeshComponent* mesh, SMRJoint* bone)
{
	//Recursively apply transformations to all children of this bone
	std::vector<uint32> children = skeleton.getJointChildren(bone->getName());
	for (int i = 0; i < children.size(); ++i)
	{
		TransformBone(mesh, skeleton.getJoint(children[i]));
		TransformChildren(mesh, skeleton.getJoint(children[i]));
	}
}

void ASmrActor::TransformBone(UPoseableMeshComponent* mesh, SMRJoint* bone)
{
	//Build the local transform for this bone
	FTransform finalTransform;
	finalTransform.SetLocation(USmrFunctions::RightCoordToLeft(bone->getPosition()));
	finalTransform.SetRotation(USmrFunctions::RightCoordToLeft(bone->getOrientation()));

	if (bone->hasParent())
	{
		//Get the component space transform for the parent bone
		FName parentName(bone->getParentName().c_str());
		FTransform parentTransform = mesh->GetBoneTransformByName(parentName, EBoneSpaces::ComponentSpace);

		//Convert local transform to component space
		finalTransform *= parentTransform;
	}
	//Convert quaternion to Euler angles and apply to the mesh
	FVector euler = finalTransform.GetRotation().Euler();
	FRotator rotator = FRotator::MakeFromEuler(euler);
	FName boneName(bone->getName().c_str());
	mesh->SetBoneRotationByName(boneName, rotator, EBoneSpaces::ComponentSpace);
}

const SMRSkeleton& ASmrActor::getSkeleton() { return skeleton; }
