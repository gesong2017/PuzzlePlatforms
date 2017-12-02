// Fill out your copyright notice in the Description page of Project Settings.

#include "StartMenu.h"

#include "Components/Button.h"

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
	UE_LOG(LogTemp, Warning, TEXT("I'm going to host a server"));
}

