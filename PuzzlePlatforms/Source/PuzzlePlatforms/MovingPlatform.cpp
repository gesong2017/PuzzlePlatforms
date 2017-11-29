// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);

}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}

	startGloabalLocation = GetActorLocation();
	targetGlobalLocation = GetTransform().TransformPosition(targetRelativeLocation);

}

void AMovingPlatform::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	// if game is running on the server
	if (HasAuthority())
	{
		FVector currentLocation = GetActorLocation();
		float journeyDistance = (targetGlobalLocation - startGloabalLocation).Size();
		float travelledDistance = (currentLocation - startGloabalLocation).Size();
		if (travelledDistance >= journeyDistance)
		{
			FVector swap = targetGlobalLocation;
			targetGlobalLocation = startGloabalLocation;
			startGloabalLocation = swap;
		}

		FVector direction = (targetGlobalLocation - startGloabalLocation).GetSafeNormal();
		currentLocation += movingSpeed*direction*deltaTime;
		SetActorLocation(currentLocation);
	}
}


