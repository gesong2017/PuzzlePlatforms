// Fill out your copyright notice in the Description page of Project Settings.

#include "PauseMenu.h"

#include "Components/Button.h"
#include "Engine/Engine.h"

void UPauseMenu::Setup()
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

void UPauseMenu::Teardown()
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

	// make mouse cursor invisible
	playerController->bShowMouseCursor = false;
}

void UPauseMenu::SetMenuInterface(IMenuInterface* MenuInterface)
{
	menuInterface = MenuInterface;
}

bool UPauseMenu::Initialize()
{
	bool success = Super::Initialize();
	if (!success)
		return false;

	// Add on click event for buttons
	if (!ensure(ResumeButton != nullptr))
		return false;
	ResumeButton->OnClicked.AddDynamic(this, &UPauseMenu::ResumeGame);

	//if (!ensure(MainMenuButton != nullptr))
	//	return false;
	//MainMenuButton->OnClicked.AddDynamic(this, &UStartMenu::OpenJoinMenu);

	//if (!ensure(QuitButton != nullptr))
	//	return false;
	//QuitButton->OnClicked.AddDynamic(this, &UStartMenu::BackToMainMenu);

	return true;
}

void UPauseMenu::ResumeGame()
{
	if (menuInterface != nullptr)
	{
		menuInterface->Resume();
	}
}


