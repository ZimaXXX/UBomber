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

	/**
	* Initial Timer time
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Time)
		int32 GameTimeInSeconds;

	/**
	* Size of squared map to be spawned
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Map)
		uint8 MapDimensionSize;

	/**
	* Class for spawning Floor
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Map|Spawn")
		TSubclassOf<AUBomberFloorBase> FloorPlaneClass;
	/**
	* Class for spawning Pickup
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Map|Spawn")
		TSubclassOf<AUBomberPickupBase> PickupClass;
	/**
	* Class for spawning SolidWall
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Map|Spawn")
		TSubclassOf<AUBomberSolidWall> SolidWallClass;
	/**
	* Class for spawning DestructableWall
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Map|Spawn")
		TSubclassOf<AUBomberDestructableWall> DestructableWallClass;
	/**
	* Called by bomb to check of game should end
	*/
	UFUNCTION()
		void OnBombExploded(AUBomberBombBase* BombReference);

protected:
	//Overrides
	virtual void BeginPlay() override;
	/**
	* Override used for picking appropriate player for controller
	*/
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;
	/**
	* Override used spawning random map
	*/
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	/**
	* Override used for disabling picking APlayerStartPIE and for disabling picking occupied PlayerStart
	*/
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

private:

	void SpawnProceduralMap(FMapDataStruct MapData);
	/**
	* Method called when bomb explodes (that is not a chain instigator) or timer runs out
	*/
	void CheckIfGameEnds();
	/**
	* Actor for managing panning camera
	*/
	class AUBomberCameraFocusActor* UBomberCameraFocusActor;
	
	//Game Timer related
	uint8 bTimerExpired : 1;
	int32 TickTime = 1;
	void GameTimerExpired();
	void GameTimerTick();
	FTimerHandle GameTimerHandle;
};
