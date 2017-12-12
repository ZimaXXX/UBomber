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
	void ShowEndScreen(FString Text);
	void CloseEndScreen();
	
	UFUNCTION(BlueprintImplementableEvent, Category = HUD)
	void ShowEndScreenBPEvent(const FString &Text);

	UFUNCTION(BlueprintImplementableEvent, Category = HUD)
	void CloseEndScreenBPEvent();


};
