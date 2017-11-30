// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformsGameInstance.h"

#include "Engine/Engine.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer)
{   
	// Debug Puerpose
	UE_LOG(LogTemp, Warning, TEXT("GameInstace Constructor"));
}

void UPuzzlePlatformsGameInstance::Init()
{   
	// Debug Purpose
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Init"));
}

void UPuzzlePlatformsGameInstance::Host()
{
	UEngine* engine = GetEngine();
	if (!ensure(engine != nullptr))
		return;
	engine->AddOnScreenDebugMessage(0, 5, FColor::Green, TEXT("Hosting"));

	UWorld* world = GetWorld();
	if (!ensure(world != nullptr))
		return;

	world->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UPuzzlePlatformsGameInstance::Join(const FString& address)
{
	UEngine* engine = GetEngine();
	if (!ensure(engine != nullptr))
		return;
	engine->AddOnScreenDebugMessage(0, 10, FColor::Green, FString::Printf(TEXT("Joining %s"), *address));

	APlayerController* playerController = GetFirstLocalPlayerController();
	if (!ensure(playerController != nullptr))
		return;

	playerController->ClientTravel(address, ETravelType::TRAVEL_Absolute);
}


