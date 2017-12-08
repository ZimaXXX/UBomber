// Fill out your copyright notice in the Description page of Project Settings.

#include "MapGenerator.h"

static const uint8 MIN_MAP_SIZE = 5;
static const uint8 MAX_MAP_SIZE = 9;
UMapGenerator::UMapGenerator() : Super() 
{

}

FMapDataStruct UMapGenerator::GenerateMap(int32 Size){
	FMapDataStruct MapData;
	if (Size < MIN_MAP_SIZE || Size > MAX_MAP_SIZE)
	{
		UE_LOG(LogTemp, Warning, TEXT("Size should be in range %d to %d"), MIN_MAP_SIZE, MAX_MAP_SIZE);
		return MapData;
	}

	TArray<uint8> MapTiles;
	MapTiles.Init(0, Size*Size);

	for (int i = 0; i < Size; i+= Size) {
		for (int j = 0; j < Size; j += Size) {
			//Create outer walls
			if ((i == 0 || i == Size - 1) && (j == 0 || j == Size - 1)) {
				MapTiles[i + j] = EMapTileMode::WALL;
			}
			//Create inner walls
			//Place inner walls in regular pattern and ommit setting outer walls again
			if (i > 0 && i < Size - 1 && i % 2 == 0 && j > 0 && j < Size - 1 && j % 2 == 0) {
				MapTiles[i + j] = EMapTileMode::WALL;
			}
			//Place Player starts
			if ((i == 1 || i == Size - 2) && (j == 1 || j == Size - 2)) {
				MapTiles[i + j] = EMapTileMode::PLAYER_START;
			}
			//Place random DESTRUCTABLE_WALL walls with occasional DESTRUCTABLE_WALL_AND_PICKUP
		}
	}


	return MapData;
}

