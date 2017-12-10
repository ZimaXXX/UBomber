// Fill out your copyright notice in the Description page of Project Settings.

#include "UBomberGameMode.h"
#include "Core/UBomberGameState.h"
#include "Core/UBomberPlayerController.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/PlayerStartPIE.h"
#include "Core/UBomberPlayerState.h"
#include "Runtime/Engine/Public/EngineUtils.h"
#include "Core/UBomberPlayerController.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerStart.h"
#include "Engine/World.h"

static int32 DEFAULT_MAP_DIMENSION_SIZE = 9;
static float SINGLE_MAP_ELEMENT_SIZE = 100.0f;
AUBomberGameMode::AUBomberGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) 
{
	MapDimensionSize = DEFAULT_MAP_DIMENSION_SIZE;
	//bIsProceduralMapSpawned = false;

	//MapGeneratorComponent = ObjectInitializer.CreateDefaultSubobject<UMapGeneratorComponent>(this, TEXT("MapGenerator"));
	//MapGeneratorComponent->OnMapReadyDelegate.BindUObject(this, &AUBomberGameMode::OnProceduralMapReady);
	//MapGeneratorComponent->AttachTo(GetRootComponent());
}

void AUBomberGameMode::OnBombExploded(AUBomberBombBase * BombReference)
{
	UE_LOG(LogTemp, Warning, TEXT("GameMode got info about bomb exploded"));
	if (BombReference) {
		if (!BombReference->bIsInflictingChainDamage) {
			CheckIfGameEnds();
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No bomb reference!"));
	}
}

void AUBomberGameMode::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::CreatePlayer(GetWorld(), 1, true);
	//FMapDataStruct MapData = MapGenerator->GenerateMapData(7);
	//UGameplayStatics::CreatePlayer(GetWorld(), 1, true);
}

UClass* AUBomberGameMode::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	TSubclassOf<AUBomberCharacter> PawnClass = NULL;
	if (InController->IsA<AUBomberPlayerController>()) {
		AUBomberGameState* UB_GS = GetGameState<AUBomberGameState>();
		AUBomberPlayerController* UB_PC = Cast<AUBomberPlayerController>(InController);
		if (UB_PC->GetLocalPlayer()) {
			int32 PlayerControllerIndex = UB_PC->GetLocalPlayer()->GetControllerId();
			if (PlayerControllerIndex < UB_GS->PlayersPawns.Num()) {
				PawnClass = UB_GS->PlayersPawns[PlayerControllerIndex];
			}
		}
	}

	if(!PawnClass){
		PawnClass = Super::GetDefaultPawnClassForController_Implementation(InController);
	}	
	
	return PawnClass;
}

void AUBomberGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	UMapGenerator* MapGenerator = NewObject<UMapGenerator>();
	FMapDataStruct MapData = MapGenerator->GenerateMapData(MapDimensionSize);
	SpawnProceduralMap(MapData);

}

void AUBomberGameMode::SpawnProceduralMap(FMapDataStruct MapData)
{
	UE_LOG(LogTemp, Warning, TEXT("Ready to spawn map!"));


	if (FloorPlaneClass && SolidWallClass && DestructableWallClass && PickupClass) {
		int32 MapDeminsionSize = (int32)MapData.Size;
		TArray<uint8> MapTiles = MapData.MapTiles;
		//Spawn Floor
		FVector Location = FVector(0.0f, 0.0f, 0.0f);
		FRotator Rotation(0.0f, 0.0f, 0.0f);
		FActorSpawnParameters SpawnInfo;
		AUBomberFloorBase* Floor = Cast<AUBomberFloorBase>(GetWorld()->SpawnActor(FloorPlaneClass, &Location, &Rotation, SpawnInfo));

		FTransform NewTransform;
		NewTransform.SetScale3D(FVector(MapDeminsionSize, MapDeminsionSize, 1.f));
		Floor->SetActorTransform(NewTransform);

		FVector Origin;
		FVector BoxExtent;
		Floor->GetActorBounds(false, Origin, BoxExtent);
		FVector FloorLeftUpperCornerLocation = Origin - BoxExtent + FVector(SINGLE_MAP_ELEMENT_SIZE / 2, SINGLE_MAP_ELEMENT_SIZE / 2, 0);

		for (int32 i = 0; i < MapDimensionSize; i++) {
			for (int32 j = 0; j < MapDimensionSize; j++) {
				//Find Actor type to spawn
				TSubclassOf<AActor> ActorToSpawn;
				bool DestructableWallSpawnsPickup = false;
				EMapTileMode::Type CurrentTileMode = static_cast<EMapTileMode::Type>(MapTiles[MapDimensionSize * i + j]);
				switch (CurrentTileMode) {
				case EMapTileMode::EMPTY:
					break;
				case EMapTileMode::RESERVED:
					break;
				case EMapTileMode::WALL:
					ActorToSpawn = SolidWallClass;
					break;
				case EMapTileMode::DESTRUCTABLE_WALL:
					ActorToSpawn = DestructableWallClass;
					DestructableWallSpawnsPickup = false;
					break;
				case EMapTileMode::DESTRUCTABLE_WALL_AND_PICKUP:
					ActorToSpawn = DestructableWallClass;
					DestructableWallSpawnsPickup = true;
					break;
				case EMapTileMode::PLAYER_START:
					ActorToSpawn = APlayerStart::StaticClass();
					break;
				case EMapTileMode::PICKUP:
					ActorToSpawn = PickupClass;
					break;
				default:
					break;
				}
				if (ActorToSpawn) {
					FVector ActorLocation = FVector(SINGLE_MAP_ELEMENT_SIZE * i, SINGLE_MAP_ELEMENT_SIZE * j, 0);
					FRotator ActorRotation = FRotator(0.0f, 0.0f, 0.0f);
					FActorSpawnParameters SpawnParameters = FActorSpawnParameters();
					ActorLocation += FloorLeftUpperCornerLocation;
					//Spawn PlayerStart above the floor so the Player won't fall underthe map
					if (CurrentTileMode == EMapTileMode::PLAYER_START) {
						ActorLocation += FVector(0, 0, SINGLE_MAP_ELEMENT_SIZE / 2);
					}
					//Set flag for spawning destructable wall with pickup
					if (CurrentTileMode == EMapTileMode::DESTRUCTABLE_WALL_AND_PICKUP) {
						FTransform SpawnTransform(ActorRotation, ActorLocation);
						auto DefferredDestructableWallActorWithPickup = Cast<AUBomberDestructableWall>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, ActorToSpawn, SpawnTransform));
						if (DefferredDestructableWallActorWithPickup != nullptr)
						{
							DefferredDestructableWallActorWithPickup->bShouldSpawnPickupOnDestroy = true;
							AActor* SpawnedActor = UGameplayStatics::FinishSpawningActor(DefferredDestructableWallActorWithPickup, SpawnTransform);							
						}
					}	
					else {
						AActor* SpawnedActor = GetWorld()->SpawnActor(ActorToSpawn, &ActorLocation, &ActorRotation, SpawnParameters);
					}

					
				}
			}
		}
	}
}

void AUBomberGameMode::CheckIfGameEnds()
{
	TArray<AUBomberPlayerController*> AlivePlayers;
	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		APlayerController* PlayerController = *Iterator;
		AUBomberPlayerController * UB_PC = Cast<AUBomberPlayerController>(PlayerController);
		if (UB_PC)
		{
			if (IsValid(UB_PC->GetPawn())) {
				AlivePlayers.Add(UB_PC);
			}
		}
	}
	if (AlivePlayers.Num() == 0) {
		UE_LOG(LogTemp, Warning, TEXT("It's a TIE!"));
	}
	else if(AlivePlayers.Num() == 1) {
		AUBomberPlayerController * UB_PC = AlivePlayers[0];
		if (IsValid(UB_PC)) {
			if (IsValid(UB_PC->PlayerState)) {
				UE_LOG(LogTemp, Warning, TEXT("Player %s WON"), *UB_PC->PlayerState->PlayerName);
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("Player WON"));
			}
		}

	}
}

//Get random unoccupied PlayerStart that is not PlayerStartPIE
AActor* AUBomberGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
	// Choose a player start
	APlayerStart* FoundPlayerStart = nullptr;
	TArray<APlayerStart*> UnOccupiedStartPoints;
	for (TActorIterator<APlayerStart> It(GetWorld()); It; ++It)
	{
		APlayerStart* PlayerStart = *It;

		if (PlayerStart->IsA<APlayerStartPIE>())
		{
			continue;
		}
		if (PlayerStart->PlayerStartTag == NAME_None) {
			UnOccupiedStartPoints.Add(PlayerStart);
		}
	}
	if (UnOccupiedStartPoints.Num() > 0) {
		int32 RandomIndex = FMath::RandRange(0, UnOccupiedStartPoints.Num() - 1);
		FoundPlayerStart = UnOccupiedStartPoints[RandomIndex];
		FoundPlayerStart->PlayerStartTag = FName("Occupied");
	}
	return FoundPlayerStart;
}


