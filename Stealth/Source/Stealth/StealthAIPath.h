// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StealthAIPath.generated.h"

UENUM(BlueprintType)
enum class EStealthAIPathFollowingMode : uint8
{
	OneShot,			// AI will go through specified path and stays at the end - 1....N
	Loop,				// AI will go through specified path and goes directly to first path segment - 1....N.1....N....
	LoopBackward,		// AI will go through specified path and returns through same path segments - 1....N....1....
};

UCLASS(Blueprintable)
class STEALTH_API AStealthAIPath : public AActor
{
	GENERATED_BODY()
	
public:	
	
	// Sets default values for this actor's properties
	AStealthAIPath();

	/** Returns true if this path was correctly constructed and has valid data. */
	UFUNCTION(BlueprintPure, Category = "Path")
	bool IsCorrectlyConstructed() const;

	/** Returns the world location of specified path segment. */
	UFUNCTION(BlueprintPure, Category = "Path")
	FVector GetPathSegmentLocation(int32 SegmentIndex) const;

	/** Returns number of path segments. */
	UFUNCTION(BlueprintPure, Category = "Path")
	int32 GetNumPathSegments() const;

protected:

	/** Defines how path segments should be traversed. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Path")
	EStealthAIPathFollowingMode PathFollowingMode = EStealthAIPathFollowingMode::OneShot;

	/** How long should AI wait when he cames at the start of the path. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Path")
	float WaitTimeAtPathStart = 0.0f;

	/** How long should AI wait when he cames at new path segment. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Path")
	float WaitTimeAtPathSegment = 0.0f;

	/** How long should AI wait when he cames at the end of the path. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Path")
	float WaitTimeAtTheEnd = 0.0f;

private:

	/** Points on the path that AI should go through. */
	UPROPERTY(EditAnywhere, Category = "Path", meta = (MakeEditWidget))
	TArray<FVector> PathSegments;
};
