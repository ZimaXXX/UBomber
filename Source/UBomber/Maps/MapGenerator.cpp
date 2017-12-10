// Fill out your copyright notice in the Description page of Project Settings.

#include "MapGenerator.h"

static const uint8 MIN_MAP_SIZE = 5;
static const uint8 MAX_MAP_SIZE = 15;
static const float DESTRUCTABLE_WALLS_TO_EMPTY_TILES_RATIO = 0.5f;
static const float PICKUPS_TO_DESTRUCTABLE_WALLS_RATIO = 0.3f;
//static const float PICKUPS_TO_EMPTY_TILES_RATIO = 0.1f;
UMapGenerator::UMapGenerator() : Super() 
{

}

FMapDataStruct UMapGenerator::GenerateMapData(int32 Size){
	FMapDataStruct MapData;
	if (Size < MIN_MAP_SIZE || Size > MAX_MAP_SIZE)
	{
		UE_LOG(LogTemp, Warning, TEXT("Size should be in range %d to %d"), MIN_MAP_SIZE, MAX_MAP_SIZE);
		return MapData;
	}

	TArray<uint8> MapTiles;
	MapTiles.Init(0, Size*Size);

	//Prepare outer walls, inner walls and player starts
	for (int32 i = 0; i < Size; i++) {
		for (int32 j = 0; j < Size; j ++) {
			//Create outer walls
			if ((i == 0 || i == Size - 1) || (j == 0 || j == Size - 1)) {
				MapTiles[Size * i + j] = EMapTileMode::WALL;
			}
			//Create inner walls
			//Place inner walls in regular pattern and ommit setting outer walls again
			if (i > 0 && i < Size - 1 && i % 2 == 0 && j > 0 && j < Size - 1 && j % 2 == 0) {
				MapTiles[Size * i + j] = EMapTileMode::WALL;
			}
			//Place Player starts
			if ((i == 1 || i == Size - 2) && (j == 1 || j == Size - 2)) {
				MapTiles[Size * i + j] = EMapTileMode::PLAYER_START;
				//Reserve tiles in range so nothing is spawned there and player can move
				int32 ReservedRange = 1;
				for (int32 k = -ReservedRange; k <= ReservedRange; ++k) {
					if (i + k >= 0 && i + k <= Size) {
						if (MapTiles[Size*(i + k) + j] == EMapTileMode::EMPTY) {
							MapTiles[Size*(i + k) + j] = EMapTileMode::RESERVED;
						}
						
					}
					if (j + k >= 0 && j + k <= Size) {
						if (MapTiles[Size*i + j + k] == EMapTileMode::EMPTY) {
							MapTiles[Size*i + j + k] = EMapTileMode::RESERVED;
						}
					}
					
				}

			}
		}
	}

	//Get list of empty tiles
	TArray<uint8> NotOccupiedTilesIndexes;
	for (int i = 0; i < MapTiles.Num(); i++) {
		if (MapTiles[i] == 0) {
			NotOccupiedTilesIndexes.Add(i);
		}
	}

	uint8 DestructableWallsToSpawn = DESTRUCTABLE_WALLS_TO_EMPTY_TILES_RATIO * NotOccupiedTilesIndexes.Num();

	//Place random DESTRUCTABLE_WALL walls with occasional DESTRUCTABLE_WALL_AND_PICKUP
	for(int32 i = 0; i < DestructableWallsToSpawn; i++) {
		int32 RandomIndex = FMath::RandRange(0, NotOccupiedTilesIndexes.Num() - 1);
		uint8 RandomEmptyTileIndex = NotOccupiedTilesIndexes[RandomIndex];
		NotOccupiedTilesIndexes.RemoveAt(RandomIndex);
		//Check if Destructable Wall should contain hidden pickup
		float RandomFloat = FMath::RandRange(0.f, 1.f);
		if (RandomFloat <= PICKUPS_TO_DESTRUCTABLE_WALLS_RATIO) {
			MapTiles[RandomEmptyTileIndex] = EMapTileMode::DESTRUCTABLE_WALL_AND_PICKUP;
		}
		else {
			MapTiles[RandomEmptyTileIndex] = EMapTileMode::DESTRUCTABLE_WALL;
		}
	}

	MapData.Size = Size;
	MapData.MapTiles = MapTiles;

	return MapData;
}

