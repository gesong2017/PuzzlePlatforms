// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	if (HasAuthority())
	{
		SetMobility(EComponentMobility::Movable);
	}
	else
		SetMobility(EComponentMobility::Static);

}

void AMovingPlatform::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	FVector currentLocation = GetActorLocation();
	currentLocation += FVector(50 * deltaTime, 0.0f, 0.0f);
	SetActorLocation(currentLocation);
}


