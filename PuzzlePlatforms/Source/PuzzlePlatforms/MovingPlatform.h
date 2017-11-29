// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:
	AMovingPlatform();

	virtual void BeginPlay() override;
	
	virtual void Tick(float deltaTime) override;

	UPROPERTY(EditAnywhere)
	float movingSpeed = 10.0f;

	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = true))
	FVector targetRelativeLocation; // relative location

private:
	FVector targetGlobalLocation;
	FVector startGloabalLocation;
};
