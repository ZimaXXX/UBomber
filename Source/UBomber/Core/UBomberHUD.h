// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UBomberHUD.generated.h"

/**
 * 
 */
UCLASS()
class UBOMBER_API AUBomberHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	/**
	* Method for showing result of game on screen
	*/
	void ShowEndScreen(FString Text);

	/**
	* Method for hiding game result screen
	*/
	void CloseEndScreen();

protected:
	/**
	* BP event for maintaining widget logic
	*/
	UFUNCTION(BlueprintImplementableEvent, Category = HUD)
	void ShowEndScreenBPEvent(const FString &Text);

	/**
	* BP event for maintaining widget logic
	*/
	UFUNCTION(BlueprintImplementableEvent, Category = HUD)
	void CloseEndScreenBPEvent();


};
