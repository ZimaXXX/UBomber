// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UBomberPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UBOMBER_API AUBomberPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	//Overrides
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
private:
	void MoveForward(float axisValue);
	void MoveRight(float axisValue);
	void PlaceBomb();
};
