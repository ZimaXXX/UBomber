// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Maps/MapGenerator.h"
#include "Items/Pickups/UBomberPickupBase.h"
#include "Items/Walls/UBomberWallBase.h"
#include "Items/Walls/UBomberSolidWall.h"
#include "Items/Walls/UBomberDestructableWall.h"
#include "Items/Floor/UBomberFloorBase.h"
#include "MapGeneratorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UBOMBER_API UMapGeneratorComponent : public USceneComponent
{
	GENERATED_BODY()

public:	

	DECLARE_DELEGATE(FMapReadyDelegate);
	FMapReadyDelegate OnMapReadyDelegate;
	// Sets default values for this component's properties
	UMapGeneratorComponent();

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


protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
private:
	UMapGenerator* MapGenerator;
	void SpawnProceduralMap(FMapDataStruct MapData);
};
