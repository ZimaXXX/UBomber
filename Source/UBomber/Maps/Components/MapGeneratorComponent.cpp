// Fill out your copyright notice in the Description page of Project Settings.

#include "MapGeneratorComponent.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerStart.h"
//#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

static int32 DEFAULT_MAP_DIMENSION_SIZE = 9;
static float SINGLE_MAP_ELEMENT_SIZE = 100.0f;
// Sets default values for this component's properties
UMapGeneratorComponent::UMapGeneratorComponent()
{
	MapDimensionSize = DEFAULT_MAP_DIMENSION_SIZE;
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UMapGeneratorComponent::BeginPlay()
{
	Super::BeginPlay();
	MapGenerator = NewObject<UMapGenerator>();
	FMapDataStruct MapData = MapGenerator->GenerateMapData(MapDimensionSize);
	SpawnProceduralMap(MapData);	
}


// Called every frame
void UMapGeneratorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UMapGeneratorComponent::SpawnProceduralMap(FMapDataStruct MapData)
{
	UE_LOG(LogTemp, Warning, TEXT("Ready to spawn map!"));
	
	
	if (FloorPlaneClass && SolidWallClass && DestructableWallClass && PickupClass) {
		int32 MapDeminsionSize = (int32)MapData.Size;
		TArray<uint8> MapTiles = MapData.MapTiles;
		//Spawn Floor
		FVector Location = FVector(0.0f, 0.0f, 2000.0f);
		FRotator Rotation(0.0f, 0.0f, 0.0f);
		FActorSpawnParameters SpawnInfo;
		AUBomberFloorBase* Floor = Cast<AUBomberFloorBase>(GetWorld()->SpawnActor(FloorPlaneClass, &Location, &Rotation, SpawnInfo));

		FTransform NewTransform;
		NewTransform.SetScale3D(FVector(MapDeminsionSize, MapDeminsionSize, 1.f));
		Floor->SetActorTransform(NewTransform);

		FVector Origin;
		FVector BoxExtent;
		Floor->GetActorBounds(false, Origin, BoxExtent);
		FVector FloorLeftUpperCornerLocation = Origin - BoxExtent + FVector(SINGLE_MAP_ELEMENT_SIZE/2, SINGLE_MAP_ELEMENT_SIZE/2, 0);

		for (int32 i = 0; i < MapDimensionSize; i++) {
			for (int32 j = 0; j < MapDimensionSize; j++) {
				//Find Actor type to spawn
				TSubclassOf<AActor> ActorToSpawn;
				bool DestructableWallSpawnsPickup = false;
				switch (MapTiles[MapDimensionSize * i + j]) {
				case EMapTileMode::EMPTY :
					break;
				case EMapTileMode::WALL :
					ActorToSpawn = SolidWallClass;
					break;
				case EMapTileMode::DESTRUCTABLE_WALL : 
					ActorToSpawn = DestructableWallClass;
					DestructableWallSpawnsPickup = false;
					break;
				case EMapTileMode::DESTRUCTABLE_WALL_AND_PICKUP :
					ActorToSpawn = DestructableWallClass;
					DestructableWallSpawnsPickup = true;
					break;
				case EMapTileMode::PLAYER_START :
					ActorToSpawn = APlayerStart::StaticClass();
					break;
				case EMapTileMode::PICKUP :
					ActorToSpawn = PickupClass;
					break;
				default:
					break;
				}

				FVector ActorLocation = FVector(SINGLE_MAP_ELEMENT_SIZE * i, SINGLE_MAP_ELEMENT_SIZE * j, 0);
				ActorLocation += FloorLeftUpperCornerLocation;
				FRotator ActorRotation = FRotator(0.0f, 0.0f, 0.0f);
				FActorSpawnParameters SpawnParameters = FActorSpawnParameters();
				AActor* SpawnedActor = GetWorld()->SpawnActor(ActorToSpawn, &ActorLocation, &ActorRotation, SpawnParameters);

			}
		}
	}
	OnMapReadyDelegate.ExecuteIfBound();
}

