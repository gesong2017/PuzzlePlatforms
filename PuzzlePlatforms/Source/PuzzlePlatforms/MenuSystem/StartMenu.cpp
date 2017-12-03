// Fill out your copyright notice in the Description page of Project Settings.

#include "StartMenu.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"
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

	// make mouse cursor invisible
	playerController->bShowMouseCursor = false;
}

bool UStartMenu::Initialize()
{
	bool success = Super::Initialize();
	if (!success)
		return false;

	// Add on click event for buttons
	if (!ensure(HostButton != nullptr))
		return false;
	HostButton->OnClicked.AddDynamic(this, &UStartMenu::HostServer);

	if (!ensure(JoinButton != nullptr))
		return false;
	JoinButton->OnClicked.AddDynamic(this, &UStartMenu::OpenJoinMenu);

	if (!ensure(CancelButton != nullptr))
		return false;
	CancelButton->OnClicked.AddDynamic(this, &UStartMenu::BackToMainMenu);

	if (!ensure(ConfirmButton != nullptr))
		return false;
	ConfirmButton->OnClicked.AddDynamic(this, &UStartMenu::JoinServer);

	if (!ensure(QuitButton != nullptr))
		return false;
	QuitButton->OnClicked.AddDynamic(this, &UStartMenu::QuitGame);

	return true;
}

void UStartMenu::HostServer()
{
	if (menuInterface != nullptr)
	{
		menuInterface->Host();
	}
}

void UStartMenu::OpenJoinMenu()
{   
	if (!ensure(MenuSwitcher != nullptr))
		return;

	if (!ensure(JoinMenu != nullptr))
		return;

	MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UStartMenu::BackToMainMenu()
{
	if (!ensure(MenuSwitcher != nullptr))
		return;

	if (!ensure(MainMenu != nullptr))
		return;

	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UStartMenu::JoinServer()
{
	if (menuInterface != nullptr)
	{   
		if (!ensure(IPAddressField != nullptr))
			return;
		menuInterface->Join(IPAddressField->GetText().ToString());
	}
}

void UStartMenu::QuitGame()
{
	// Get the player controller from the world
	UWorld* world = GetWorld();
	if (!ensure(world != nullptr))
		return;
	APlayerController* playerController = world->GetFirstPlayerController();
	if (!ensure(playerController != nullptr))
		return;

	// Quit Game through player controller console command function
	playerController->ConsoleCommand("quit");
}

