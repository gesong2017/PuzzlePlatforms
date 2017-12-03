// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformsGameInstance.h"

#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem/StartMenu.h"
#include "MenuSystem/PauseMenu.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer)
{   
	// Find the main menu UIWideget Blueprint
	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if (!ensure(MenuBPClass.Class != nullptr))
		return;

	menuClass = MenuBPClass.Class;

	// Find the pause menu UIWideget Blueprint
	ConstructorHelpers::FClassFinder<UUserWidget> PauseMenuBPClass(TEXT("/Game/MenuSystem/WBP_PauseMenu"));
	if (!ensure(PauseMenuBPClass.Class != nullptr))
		return;

	pauseMenuClass = PauseMenuBPClass.Class;
}

void UPuzzlePlatformsGameInstance::Init()
{   
	// Debug Purpose
	UE_LOG(LogTemp, Warning, TEXT("Found Class %s"), *menuClass->GetName());
	UE_LOG(LogTemp, Warning, TEXT("Found Class %s"), *pauseMenuClass->GetName());
}

void UPuzzlePlatformsGameInstance::LoadMenu()
{   
	if (!ensure(menuClass != nullptr))
		return;
	Menu = CreateWidget<UStartMenu>(this, menuClass);
	if (!ensure(Menu != nullptr))
		return;

	// Set up the menu
	Menu->Setup();

	// Link the game instace with the interface of start menu
	Menu->SetMenuInterface(this);
}

void UPuzzlePlatformsGameInstance::Host()
{   
	// release the main menu
	if (Menu != nullptr)
	{
		Menu->Teardown();
	}

	//
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
	// release the main menu
	if (Menu != nullptr)
	{
		Menu->Teardown();
	}

	//
	UEngine* engine = GetEngine();
	if (!ensure(engine != nullptr))
		return;
	engine->AddOnScreenDebugMessage(0, 10, FColor::Green, FString::Printf(TEXT("Joining %s"), *address));

	APlayerController* playerController = GetFirstLocalPlayerController();
	if (!ensure(playerController != nullptr))
		return;

	playerController->ClientTravel(address, ETravelType::TRAVEL_Absolute);
}

void UPuzzlePlatformsGameInstance::InvokePauseMenu()
{
	if (!ensure(pauseMenuClass != nullptr))
		return;
	PauseMenu = CreateWidget<UPauseMenu>(this, pauseMenuClass);
	if (!ensure(PauseMenu != nullptr))
		return;

	// Set up the menu
	PauseMenu->Setup();

	// Link the game instace with the interface of start menu
	PauseMenu->SetMenuInterface(this);
}

void UPuzzlePlatformsGameInstance::LoadMainMenu()
{
	APlayerController* playerController = GetFirstLocalPlayerController();
	if (!ensure(playerController != nullptr))
		return;

	playerController->ClientTravel("/Game/MenuSystem/StartMenu", ETravelType::TRAVEL_Absolute);
}

