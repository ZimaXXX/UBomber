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
	TArray<int32> ArrayOfVictoriesCount;
	
	void SetVictoriesForIndex(int32 index, int32 value);
	int32 GetVictoriesForIndex(int32 index);
};
