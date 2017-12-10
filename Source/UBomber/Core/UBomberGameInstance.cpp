// Fill out your copyright notice in the Description page of Project Settings.

#include "UBomberGameInstance.h"

UUBomberGameInstance::UUBomberGameInstance() : Super()
{
	ArrayOfVictoriesCount.Init(0, 2);
}

void UUBomberGameInstance::SetVictoriesForIndex(int32 index, int32 value)
{
	if (ArrayOfVictoriesCount.Num() - 1 >= index) {
		ArrayOfVictoriesCount[index] = value;
	}
}

int32 UUBomberGameInstance::GetVictoriesForIndex(int32 index)
{
	if (ArrayOfVictoriesCount.Num() - 1 >= index) {
		return ArrayOfVictoriesCount[index];
	}
	return -1;
}
