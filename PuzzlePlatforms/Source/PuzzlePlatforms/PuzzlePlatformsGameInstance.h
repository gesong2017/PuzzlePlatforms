// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"
#include "PuzzlePlatformsGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UPuzzlePlatformsGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()

public:
	UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer);
	
	virtual void Init();

	UFUNCTION(BlueprintCallable)
	void LoadMenu();

	UFUNCTION(Exec)
	void Host();

	UFUNCTION(Exec)
	void Join(const FString& address);

	UFUNCTION(BlueprintCallable)
	void InvokePauseMenu();

	UFUNCTION(Exec)
	void Resume();

private:
	TSubclassOf<UUserWidget> menuClass;
	TSubclassOf<UUserWidget> pauseMenuClass;
	class UStartMenu* Menu;
	class UPauseMenu* PauseMenu;
};
