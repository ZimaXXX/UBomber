// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Runtime/Engine/Classes/Engine/DataTable.h"
#include "Common/UBomberTypes.h"
#include "Maps/MapGenerator.h"
#include "Items/Pickups/UBomberPickupBase.h"
#include "Items/Walls/UBomberWallBase.h"
#include "Items/Walls/UBomberSolidWall.h"
#include "Items/Walls/UBomberDestructableWall.h"
#include "Items/Floor/UBomberFloorBase.h"
#include "UBomberGameMode.generated.h"

/**
 * 
 */
UCLASS()
class UBOMBER_API AUBomberGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AUBomberGameMode(const FObjectInitializer& ObjectInitializer);
	
	//UPROPERTY(VisibleAnywhere, Category = Map)
	//UMapGeneratorComponent* MapGeneratorComponent;

	uint8 bIsProceduralMapSpawned : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Time)
		int32 GameTimeInSeconds;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Map)
		uint8 MapDimensionSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Map|Spawn")
		TSubclassOf<AUBomberFloorBase> FloorPlaneClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Map|Spawn")
		TSubclassOf<AUBomberPickupBase> PickupClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Map|Spawn")
		TSubclassOf<AUBomberSolidWall> SolidWallClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Map|Spawn")
		TSubclassOf<AUBomberDestructableWall> DestructableWallClass;

	UFUNCTION()
		void OnBombExploded(AUBomberBombBase* BombReference);

protected:
	//Overrides
	virtual void BeginPlay() override;
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

private:
	void SpawnProceduralMap(FMapDataStruct MapData);
	void CheckIfGameEnds();
	class AUBomberCameraFocusActor* UBomberCameraFocusActor;

	uint8 bTimerExpired : 1;
	int32 TickTime = 1;
	
	void GameTimerExpired();
	void GameTimerTick();
	FTimerHandle GameTimerHandle;
};
