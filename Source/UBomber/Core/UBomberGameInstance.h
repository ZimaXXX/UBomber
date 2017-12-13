// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UBomberGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UBOMBER_API UUBomberGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UUBomberGameInstance();
	
	/**
	* Sets the number of victories in the game per player controller index
	*/
	void SetVictoriesForIndex(int32 index, int32 value);

	/**
	* Returns the number of victories in the game per player controller index
	* @Return Returns number of vectories or -1 if index was not found
	*/
	int32 GetVictoriesForIndex(int32 index);

private:
	TArray<int32> ArrayOfVictoriesCount;
};
