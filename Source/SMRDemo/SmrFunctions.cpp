// Fill out your copyright notice in the Description page of Project Settings.

#include "SMRDemo.h"
#include "SmrFunctions.h"

FQuat USmrFunctions::MakeFQuat(SMRQuaternion q)
{
	return FQuat(q.m_x, q.m_y, q.m_z, q.m_w);
}

FQuat USmrFunctions::RightCoordToLeft(FQuat q)
{
	return FQuat(-q.X, q.Y, -q.Z, q.W);
}

FVector USmrFunctions::MakeFVector(SMRVector3 v)
{
	return FVector{ float(v.m_x), float(v.m_y), float(v.m_z) };
}