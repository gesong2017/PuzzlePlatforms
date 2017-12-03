// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem/MenuInterface.h"
#include "PauseMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UPauseMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	void Setup();

	void Teardown();

	void SetMenuInterface(IMenuInterface* MenuInterface);

protected:
	virtual bool Initialize();
	
private:
	UPROPERTY(meta = (BindWidget))
	class UButton* ResumeButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* MainMenuButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;

	UFUNCTION()
	void ResumeGame();
	
	IMenuInterface* menuInterface;
};
