// Fill out your copyright notice in the Description page of Project Settings.

#include "StealthAIPath.h"

AStealthAIPath::AStealthAIPath()
{
	PrimaryActorTick.bCanEverTick = false;
}

bool AStealthAIPath::IsCorrectlyConstructed() const
{
	return PathSegments.Num() > 0 && PathSegments[0] == FVector::ZeroVector;
}

FVector AStealthAIPath::GetPathSegmentLocation(int32 SegmentIndex) const
{
	return SegmentIndex < PathSegments.Num() ? GetActorLocation() + GetActorRotation().RotateVector(PathSegments[SegmentIndex]) : GetActorLocation();
}

int32 AStealthAIPath::GetNumPathSegments() const
{
	return PathSegments.Num();
}
