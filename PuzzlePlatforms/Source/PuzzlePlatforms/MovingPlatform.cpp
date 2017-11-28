// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);

}

void AMovingPlatform::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	if (HasAuthority())
	{
		FVector currentLocation = GetActorLocation();
		currentLocation += FVector(movingSpeed * deltaTime, 0.0f, 0.0f);
		SetActorLocation(currentLocation);
	}
}


