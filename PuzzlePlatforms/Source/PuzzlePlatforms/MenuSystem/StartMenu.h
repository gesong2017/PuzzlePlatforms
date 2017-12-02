// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem/MenuInterface.h"
#include "StartMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UStartMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetMenuInterface(IMenuInterface* MenuInterface);

	void Setup();

	void Teardown();

protected:
	virtual bool Initialize();

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* Host;

	UPROPERTY(meta = (BindWidget))
	class UButton* Join;

	UFUNCTION()
	void HostServer();

	IMenuInterface* menuInterface;
};
