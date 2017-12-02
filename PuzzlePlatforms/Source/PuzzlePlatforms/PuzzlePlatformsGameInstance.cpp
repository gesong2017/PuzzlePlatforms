// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformsGameInstance.h"

#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer)
{   
	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if (!ensure(MenuBPClass.Class != nullptr))
		return;

	menuClass = MenuBPClass.Class;
}

void UPuzzlePlatformsGameInstance::Init()
{   
	// Debug Purpose
	UE_LOG(LogTemp, Warning, TEXT("Found Class %s"), *menuClass->GetName());
}

void UPuzzlePlatformsGameInstance::LoadMenu()
{   
	if (!ensure(menuClass != nullptr))
		return;
	UUserWidget* Menu = CreateWidget<UUserWidget>(this, menuClass);
	if (!ensure(Menu != nullptr))
		return;
	Menu->AddToViewport();

	// Get the player controller first
	APlayerController* playerController = GetFirstLocalPlayerController();
	if (!ensure(playerController != nullptr))
		return;

	// Choose which mode we want to use
	FInputModeUIOnly inputModeData;
	inputModeData.SetWidgetToFocus(Menu->TakeWidget());
	inputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	// Use player controller to set the input mode
	playerController->SetInputMode(inputModeData);

	// make mouse cursor visible
	playerController->bShowMouseCursor = true;
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


