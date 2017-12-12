// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Core/UBomberCharacter.h"
#include "UBomberGameState.generated.h"

/**
 * 
 */
UCLASS()
class UBOMBER_API AUBomberGameState : public AGameStateBase
{
	GENERATED_BODY()
public:

	AUBomberGameState();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Default)
	TArray<TSubclassOf<AUBomberCharacter>> PlayersPawns;

	TArray<bool> GetResultsForControllers();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Time)
	int32 CurrentGameTimeInSeconds;
};
