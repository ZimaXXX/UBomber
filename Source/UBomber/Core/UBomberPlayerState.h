// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Runtime/Engine/Classes/Materials/Material.h"
#include "UBomberPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class UBOMBER_API AUBomberPlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	AUBomberPlayerState();

	/**
	* Flag for indicating winner
	*/
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Default)
	uint8 WonLastGame;
	
	/**
	* Number of Victories counter
	*/
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Default)
	int32 NumberOfVictories;
};
