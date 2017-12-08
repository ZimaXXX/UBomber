// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Common/UBomberTypes.h"
#include "MapGenerator.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
namespace EMapTileMode
{
	enum Type
	{		
		EMPTY = 0,
		PLAYER_START = 1,
		WALL = 2,
		DESTRUCTABLE_WALL = 3,
		PICKUP = 4,
		DESTRUCTABLE_WALL_AND_PICKUP = 5

	};
}


UCLASS()
class UBOMBER_API UMapGenerator : public UObject
{
	GENERATED_BODY()

public:
	UMapGenerator();
	
	/**
	*/
	FMapDataStruct GenerateMap(int32 Size);
};
