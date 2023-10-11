// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TetrisBlock.generated.h"


UCLASS()
class TETRISSOLUTION_API ATetrisBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATetrisBlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	UFUNCTION(BlueprintCallable)
	void SetBlockScale(const float NewSize);

	UFUNCTION(BlueprintCallable)
	const FLinearColor& GetBlockColor() const;

	UFUNCTION(BlueprintCallable)
	void SetBlockColor(const FLinearColor& NewColor);

private:
	UPROPERTY(EditAnywhere)
	UMaterialInstance* MaterialInstance;

	UPROPERTY(EditAnywhere)
	FName ColorParameterName = "BlockColor";

	UPROPERTY()
	UStaticMeshComponent* MeshComponent;

	UPROPERTY()
	UMaterialInstanceDynamic* MyDynamicMaterial;

	UPROPERTY(EditAnywhere)
	FLinearColor CurrentColor = FLinearColor::Gray;
	
};
