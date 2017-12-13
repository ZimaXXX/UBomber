// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Common/UBomberTypes.h"
#include "MapGenerator.generated.h"

/**
* Map Tile indicator for Map Generator
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
		DESTRUCTABLE_WALL_AND_PICKUP = 5,
		RESERVED = 6
	};
}


UCLASS()
class UBOMBER_API UMapGenerator : public UObject
{
	GENERATED_BODY()

public:
	UMapGenerator();
	
	/**
	* Generates a struct with array of EMapTileMode values. 
	* Algorithm starts with generating SolidWalls in regular pattern. Next 4 PlayerStarts are placed in Map corners. 
	* Later DestructableWalls are randomly placed. Each DestructableWall has a chance to spawn Pickup on destrucion.
	* Currently only Square maps are supported.
	* @param Size - Size of dimensions (both Height and Width)
	* @returns FMapDataStruct containing Size and single dimension TArray of EMapTileMode
	*/
	FMapDataStruct GenerateMapData(int32 Size);
};
