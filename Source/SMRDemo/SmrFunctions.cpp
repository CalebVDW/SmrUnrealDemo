// Fill out your copyright notice in the Description page of Project Settings.

#include "SMRDemo.h"
#include "SmrFunctions.h"

FQuat USmrFunctions::SmrQuatToFQuat(SMRQuaternion q)
{
	return FQuat(q.m_x, q.m_y, q.m_z, q.m_w);
}


