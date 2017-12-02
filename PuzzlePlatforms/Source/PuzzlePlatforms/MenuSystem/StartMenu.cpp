// Fill out your copyright notice in the Description page of Project Settings.

#include "StartMenu.h"

#include "Components/Button.h"
#include "Engine/Engine.h"

void UStartMenu::SetMenuInterface(IMenuInterface* MenuInterface)
{
	menuInterface = MenuInterface;
}

void UStartMenu::Setup()
{   
	// Display the menu on the level
	this->AddToViewport();

	// Get the player controller from the world
	UWorld* world = GetWorld();
	if (!ensure(world != nullptr))
		return;
	APlayerController* playerController = world->GetFirstPlayerController();
	if (!ensure(playerController != nullptr))
		return;

	// Choose which input mode we want to use
	FInputModeUIOnly inputModeData;
	inputModeData.SetWidgetToFocus(this->TakeWidget());
	inputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	// Use player controller to set the input mode
	playerController->SetInputMode(inputModeData);

	// make mouse cursor visible
	playerController->bShowMouseCursor = true;
}

void UStartMenu::Teardown()
{   
	// Release the Menu being rendered
	this->RemoveFromViewport();

	// Get the player controller from the world
	UWorld* world = GetWorld();
	if (!ensure(world != nullptr))
		return;
	APlayerController* playerController = world->GetFirstPlayerController();
	if (!ensure(playerController != nullptr))
		return;

	// Choose which input mode we want to use
	FInputModeGameOnly inputModeData;

	// Use player controller to set the input mode
	playerController->SetInputMode(inputModeData);
}

bool UStartMenu::Initialize()
{
	bool success = Super::Initialize();
	if (!success)
		return false;

	// Add on click event for buttons
	Host->OnClicked.AddDynamic(this, &UStartMenu::HostServer);

	return true;
}

void UStartMenu::HostServer()
{
	if (menuInterface != nullptr)
	{
		menuInterface->Host();
	}
}

