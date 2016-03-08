// Fill out your copyright notice in the Description page of Project Settings.

#include "SMRDemo.h"
#include "SmrFunctions.h"

FQuat USmrFunctions::MakeFQuat(SMRQuaternion q)
{
	return FQuat(q.m_x, q.m_y, q.m_z, q.m_w);
}

FQuat USmrFunctions::LeftCoordToRight(FQuat q)
{
	//TODO
	return q;
}

FQuat USmrFunctions::RightCoordToLeft(FQuat q)
{
	//TODO
	return q;
}


FVector USmrFunctions::MakeFVector(SMRVector3 v)
{
	return FVector{ v.m_x, v.m_y, v.m_z };
}